int last_index_of(const char* s, char c) {

    int i=0;
    int idx =-1;
    for (auto it = s; *it!='\0'; ++it, ++i) {
        if (*it == c) {
            idx = i;
        }
    }
    return idx;


}

