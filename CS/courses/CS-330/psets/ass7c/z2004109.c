#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_SIZE 100
#define MAX_WORDS 10000

typedef struct {
    size_t length;
    size_t count;
} WordStat;

// Function to remove punctuation from a word
void removePunctuation(char* word) {
    char* src = word, *dst = word;
    while (*src) {
        if (!ispunct((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

// Function to find or add a word length in the stats array
void addWordLength(WordStat* stats, size_t length, size_t* uniqueLengths) {
    for (size_t i = 0; i < *uniqueLengths; i++) {
        if (stats[i].length == length) {
            stats[i].count++;
            return;
        }
    }
    stats[*uniqueLengths].length = length;
    stats[*uniqueLengths].count = 1;
    (*uniqueLengths)++;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Incorrect number of arguments\nUsage: %s <input file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: File could not be opened\n");
        return EXIT_FAILURE;
    }

    WordStat stats[MAX_WORDS] = {0};
    size_t uniqueLengths = 0;
    size_t totalWords = 0;
    char word[MAX_WORD_SIZE];
    char buffer[MAX_WORD_SIZE];

    while (fscanf(file, "%s", buffer) != EOF) {
        if (buffer[0] == '#') {
            // Skip the rest of the line if it starts with '#'
            fgets(buffer, sizeof(buffer), file);
            continue;
        }
        removePunctuation(buffer);
        size_t length = strlen(buffer);
        if (length > 0) {
            addWordLength(stats, length, &uniqueLengths);
            totalWords++;
        }
    }
    fclose(file);

    // Find the most common and longest word sizes
    size_t mostCommonSize = 0, mostCommonCount = 0, longestWordSize = 0, longestWordCount = 0;
    for (size_t i = 0; i < uniqueLengths; i++) {
        if (stats[i].count > mostCommonCount) {
            mostCommonSize = stats[i].length;
            mostCommonCount = stats[i].count;
        }
        if (stats[i].length > longestWordSize) {
            longestWordSize = stats[i].length;
            longestWordCount = stats[i].count;
        }
    }

    printf("%s contains %zu words\n", argv[1], totalWords);
    printf("Words of size %zu occur the most: %zu times\n", mostCommonSize, mostCommonCount);
    printf("The longest words have %zu letters and occur %zu times\n", longestWordSize, longestWordCount);

    return EXIT_SUCCESS;
}

