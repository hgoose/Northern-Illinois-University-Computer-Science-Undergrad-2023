int index_of(const char* s, char c) {

    int idx = 0;
    for (auto i = s; *i != '\0'; ++i, ++idx) {
        if (c == *i) {
            return idx;
        }
    }
    return -1;

}

