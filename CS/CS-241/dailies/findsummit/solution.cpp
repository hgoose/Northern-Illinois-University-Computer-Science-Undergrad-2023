int find_summit(int a[], int len) {


    for (int i=0; i<len-1; ++i) {
        if (a[i] > a[i+1]) {
            return a[i];
        }
    }


    return (len == 1 ? a[0] : a[len-1]);


}
