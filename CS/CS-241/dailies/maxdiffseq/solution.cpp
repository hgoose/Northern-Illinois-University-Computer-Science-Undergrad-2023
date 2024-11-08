int max_diff_seq(int a[], int len) {

    // Edge case
    if (len <= 1) return -1;

    // Assume first check is the max difference
    int assumption = a[1] - a[0];

    // Check the remaining differences
    for (int j=0; j<len; ++j) {
        for (int k=j+1; k<len; ++k) {
            if (a[k] -a[j] > assumption) {
                assumption = a[k] - a[j];
            }
        }
    }

    return assumption;







}

