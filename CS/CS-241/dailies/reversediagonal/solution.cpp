void swap(int& a, int& b) {
    a = a+b;
    b = a-b;
    a = a-b;
}

void reverse_diagonal(int arr[][4]) {

    int n = 4;

        for (int i=0, j=n-1, k=0; k <= n/2; ++i, --j, k+=2) {
            swap(arr[i][i], arr[j][j]);
            swap(arr[j][i], arr[i][j]);
        }
}

