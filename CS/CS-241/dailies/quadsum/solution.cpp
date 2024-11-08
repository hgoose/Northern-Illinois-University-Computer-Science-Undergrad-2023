
bool quad_sum_is_n(int a[], int len, int n) {

    // Quad type looping

    int sum;
    for (int i=0; i<len-3; ++i) {
        for (int j=i+1; j<len; ++j) {
            for (int k=j+1; k<len; ++k) {
                sum = a[i] + a[j] + a[k];
                for (int l = k+1; l<len; ++l) {
                    if ((sum + a[l]) == n) {
                        return true;
                    }
                }
            }
        }
    }
    return false;

}

