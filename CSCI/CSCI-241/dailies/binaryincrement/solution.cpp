void binary_increment(int a[], int len) {
    int carry = 1; 
    for (int i = len - 1; i >= 0 && carry; --i) {
        if (a[i] == 1) {
            a[i] = 0; 
        } else {
            a[i] = 1;
            carry = 0; 
        }
    }
    
    if (carry == 1) {
        for (int i = len - 1; i >= 0; --i) {
            a[i] = a[i-1];
        }
        a[0] = 1; 
    }
}
