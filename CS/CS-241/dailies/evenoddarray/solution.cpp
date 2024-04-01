void even_odd(int a[], int b[], int len) {

    if (len == 1) {
        b[0] = a[0];
        return;
    } else if (len == 0 || len < 0) {
        return;
    }


    if (a[0] % 2 != 0) {
        for (int i=0; i<len; i+=2) {
            if (i+1 < len) {
                if ((a[i] % 2 != 0) && (a[i+1] % 2 == 0)) {
                    b[i] = a[i+1];
                    b[i+1] = a[i];
                } else {
                    b[i] = a[i];
                    b[i+1] = a[i+1];
                }
            }
        }
    } else {
        b[0] = a[0];
        for (int i=1; i<len; i+=2) {
            if (i+1 < len) {
                if ((a[i] % 2 == 0) && (a[i+1] % 2 != 0)) {
                    b[i] = a[i+1];
                    b[i+1] = a[i];
                } else {
                    b[i] = a[i];
                    b[i+1] = a[i+1];
                }
            } else {
                b[i] = a[i];
            }
        }
    }
}

