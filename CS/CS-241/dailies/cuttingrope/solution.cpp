int cutting_rope(int a[], int n, int sum) {

    // Find maximum element
    int max = a[0];
    for (int i=1; i<n; ++i) {
        if (a[i] > max) {
            max = a[i];
        }
    }


    // Logic:
    // The amount of possible cuts we can make is equal to the highest element,
    // we just make a cut at each possible distance, find out how much length we have, 
    // then check to see if thats the amount we need. If it is, we return the cut number (iteration of the outer loop).
    // If we reach the end of the outer loop with no return, we know the cut is not possible and we can return -1

    int length; 
    for (int i=0; i<max; ++i) {
        length = 0;
        for (int j=0; j<n; ++j) {
            if (a[j] > i) {
                length += (a[j]-i);
            }
        }

        if (length == sum) {
            return i;
        }
    }
    return -1;


    


}

