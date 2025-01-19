#include <cctype>

int length(const char* src) {
    int n = 0;

    for (auto it = src; *it != '\0'; ++it, ++n);

    return n;
}

int space_start(const char* src) {

    int space_beg = 0;
    int n = length(src);
    
    for (int i=0; i<n; ++i) {
        if (isspace(src[i])) {
            ++space_beg;
            continue;
        }
        break;
    }
    return space_beg;
}

int space_last(const char* src) {

    int space_end = 0;
    int n = length(src);

    for (int i=n-1; i>=0; --i) {
        if (isspace(src[i])) {
            ++space_end;
            continue;
        }
        break;
    }

    return space_end;
}

char* trim(char* dest, const char* src) {

    int space_beg = space_start(src);
    int space_end = space_last(src);
    int n = length(src);

    int idx = 0;
    for (int i=space_beg; i<n-space_end; ++i) {
        dest[idx++] = src[i];
    }
    dest[idx] = '\0';
    
    return dest;
}
