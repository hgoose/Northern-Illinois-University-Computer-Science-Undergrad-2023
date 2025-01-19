void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

bool windback(int a[], int b[], int len, int num_steps) {

    if (len < 1 || num_steps < 0) return false;

    int start = 0, remainder = 0;
    if (num_steps > len) {
        remainder = num_steps - len;
    } else {
        start = len - num_steps;
    }

    int k=0;
    for (int i=start; i<len; ++i,++k) {
        b[k] = a[i];
    }

    for (int i=0; i<start; ++i, ++k) {
        b[k] = a[i];
    }

    if (remainder) {
        windback(a,b,len,remainder);
    }

    return true;

}

