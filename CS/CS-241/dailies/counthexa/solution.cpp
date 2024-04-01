int count_hex_a(int n) {

    if (n < 0) return -1;

    int ret = 0;
    for (int i=n; i>0; i/=16) {
        if (i % 16 == 10) {
            ++ret;
        }
    }

    return ret;

}

