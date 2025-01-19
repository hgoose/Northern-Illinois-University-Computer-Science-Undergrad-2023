void rotate_matrix(int dest[][8], int src[][8]) {
    int n = 8;

    for (int i=0; i<n; ++i) {
        for (int j=n-1, row=0; j>=0; --j, ++row) {
            dest[i][row] = src[j][i];
        }
    }

}

