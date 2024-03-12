#include <cstring>

char* replace_copy(char* destination, const char* source, char old_char, char new_char) {
    for (int i = 0; source[i] != '\0'; ++i) {
        if (source[i] == old_char) {
            destination[i] = new_char;
        } else {
            destination[i] = source[i];
        }
    }
    
    int len = strlen(source);
    destination[len] = '\0';
    
    return destination;
}
