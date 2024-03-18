#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000

char* removePunct(const char* str) {
    char* res = (char*)malloc(MAX_SIZE * sizeof(char));
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!ispunct(str[i])) {
            res[index++] = str[i];
        }
    }
    res[index] = '\0';
    return res;
}

typedef struct {
    size_t first;
    size_t second;
} Pair;

Pair getMost(size_t* M, int size) {
    Pair* V = (Pair*)malloc(size * sizeof(Pair));
    for (int i = 0; i < size; i++) {
        V[i].first = i;
        V[i].second = M[i];
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (V[j].second > V[j + 1].second) {
                Pair temp = V[j];
                V[j] = V[j + 1];
                V[j + 1] = temp;
            }
        }
    }
    Pair most = V[size - 1];
    free(V);
    return most;
}

int main(int argc, const char* argv[]) {
    size_t words[MAX_SIZE] = {0};
    char* word_list[MAX_SIZE];
    size_t count = 0;
    if (argc <= 1) {
        fprintf(stderr, "Error: Too few arguments\nUsage ./z2004109 <input file>\n");
        exit(EXIT_FAILURE);
    } else if (argc > 2) {
        fprintf(stderr, "Error: Expected only one argument\nUsage ./z2004109 <input file>\n");
        exit(EXIT_FAILURE);
    }
    FILE* input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error: Argument passed was not readable\nUsage ./z2004109 <input file>\n");
        exit(EXIT_FAILURE);
    }
    char line[MAX_SIZE];
    while (fgets(line, MAX_SIZE, input)) {
        if (line[0] == '#') {
            continue;
        }
        char* token = strtok(line, " ");
        while (token != NULL) {
            char* cleaned_word = removePunct(token);
            size_t len = strlen(cleaned_word);
            words[len]++;
            word_list[count] = cleaned_word;
            count++;
            token = strtok(NULL, " ");
        }
    }
    fclose(input);
    Pair most = getMost(words, MAX_SIZE);
    Pair longest = {0, 0};
    for (int i = 0; i < MAX_SIZE; i++) {
        if (words[i] > 0) {
            longest.first = i;
            longest.second = words[i];
        }
    }
    printf("%s contains %zu words\n", argv[1], count);
    printf("Words of size %zu occur the most: %zu times\n", most.first, most.second);
    printf("The longest words have %zu Letters and occur %zu times\n", longest.first, longest.second);
    for (int i = 0; i < count; i++) {
        if (strlen(word_list[i]) == longest.first) {
            printf("%*s\n", 9 + longest.first, word_list[i]);
        }
    }
    for (int i = 0; i < count; i++) {
        free(word_list[i]);
    }
    return EXIT_SUCCESS;
}


