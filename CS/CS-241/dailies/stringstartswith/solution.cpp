#include <cstring>

bool starts_with(const char* s, const char* prefix) {

    size_t len = strlen(prefix);
    bool ret = 1;
    for (size_t i=0; i<len; ++i) {
        if (s[i] != prefix[i]) {
            ret = 0;
        }
    }

    return ret;
}

