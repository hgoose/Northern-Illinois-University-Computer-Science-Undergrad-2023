/********************************************************************
CSCI 480 - Assignment 5 - Spring 26

Programmer: Nate Warner
Section: 1
TA: Hannah
Date Due: 04/12/26 

Purpose: Implement readers-writers problem with pthreads and sempaphores
*********************************************************************/

#include <iostream>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>

static int cleanup();

// Global space
namespace G {
    static constexpr size_t INIT_LEN{23};
    static char str[INIT_LEN]{"Leslie Lamport is cool"};

    // Semaphores
    static sem_t rw_sem{}, rc_sem{};
    static int read_count{};

    // Current length of string
    static int str_len{INIT_LEN-1};

    static int thread_count{};
};

void* writer(void* param) {
    while (G::str_len > 0) {
        // Wait on rw lock
        if (sem_wait(&G::rw_sem) != 0) {
            perror("sem_wait");
            return NULL;
        }

        printf("Writing\n");

        // Chop off last character
        --G::str_len;

        // Release rw lock
        if (sem_post(&G::rw_sem) != 0) {
            perror("sem_post");
            return NULL;
        }

        sleep(1);
    }

    return NULL;
}

void* reader(void* param) {
    while (G::str_len > 0) {
        // Wait on read count sem
        if (sem_wait(&G::rc_sem) != 0) {
            perror("sem_wait rc_sem");
            return NULL;
        }

        // Read count sem aquired
        ++G::read_count;

        printf("read count: %d\n", G::read_count);

        // First reader, wait for writer to finish
        if (G::read_count == 1) {
            if (sem_wait(&G::rw_sem) != 0) {
                perror("sem_wait rw_sem");
                return NULL;
            }
        }

        // RW sem acquired, allow other readers to read
        if (sem_post(&G::rc_sem) != 0) {
            perror("sem_post rc_sem");
            return NULL;
        }

        // Output string
        printf("%.*s\n", G::str_len, G::str);
        fflush(stdout);

        // Wait on read count sem to change read_count value
        if (sem_wait(&G::rc_sem) != 0) {
            perror("sem_wait rc_sem");
            return NULL;
        }

        // Change read_count value (dec)c sprintf
        --G::read_count;

        // All readers finished, release rw_sem
        if (G::read_count == 0) {
            if (sem_post(&G::rw_sem) != 0) {
                perror("sem_post rw_sem");
                return NULL;
            }
        }

        // Release read_count sem
        if (sem_post(&G::rc_sem) != 0) {
            perror("sem_post rc_sem");
            return NULL;
        }

        sleep(1);
    }

    return NULL;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: <r (readers)> <w (writers)>\n"; 
        return EXIT_FAILURE;
    }

    // Get arguments
    int k_readers, k_writers;
    try {
        k_readers = std::stoi(argv[1]);
        k_writers = std::stoi(argv[2]);
    } catch (std::exception& e) {
        std::cerr << "Address the issue in the supplied input\n";
        return EXIT_FAILURE;
    }

    // Initialize semaphores
    if (sem_init(&G::rw_sem, 0, 1) != 0) {
        perror("sem_init rw_sem");
        return EXIT_FAILURE;
    }

    if (sem_init(&G::rc_sem, 0, 1) != 0) {
        perror("sem_init rc_sem");
        sem_destroy(&G::rw_sem);
        return EXIT_FAILURE;
    }

    // Start creating threads
    pthread_t* threads = new pthread_t[k_readers + k_writers];

    // Create readers
    for (int i{}; i < k_readers; ++i) {
        pthread_t th;
        int rc;
        if ((rc = pthread_create(&th, NULL, &reader, NULL)) != 0) {
            errno = rc;
            perror("pthread_create");
        }
        threads[G::thread_count++] = th; 
    }

    // Create writers
    for (int i{}; i < k_writers; ++i) {
        pthread_t th;
        int rc;
        if ((rc = pthread_create(&th, NULL, &writer, NULL)) != 0) {
            errno = rc;
            perror("pthread_create");
        }
        threads[G::thread_count++] = th; 
    }

    // Join all threads
    for (int k = 0; k < k_readers + k_writers; ++k) {
        int rc;
        if ((rc = pthread_join(threads[k], NULL)) != 0) {
            errno = rc;
            perror("pthread_join");
        }
    }

    if (cleanup() == -1) {
        return EXIT_FAILURE;
    }

    delete[] threads;

    return EXIT_SUCCESS;
}

// Destroys the semaphores and maybe errors
int cleanup() {
    int sde1 = sem_destroy(&G::rw_sem);
    int sde2 = sem_destroy(&G::rc_sem);
    if (sde1 != 0 || sde2 != 0) {
        perror("sem_destroy");
        return -1;
    }

    return 0;
}
