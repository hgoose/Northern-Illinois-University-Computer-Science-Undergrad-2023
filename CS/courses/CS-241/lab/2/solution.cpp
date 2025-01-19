void shell_sort(int array[], int n) {

    int gap_array[] = {701,301,132,57,23,10,4,1};

    for (const auto& gap : gap_array)   {

        for (int j = gap; j<n; ++j) {

            int temp = array[j];

            int k;
            for ( k=j; k>=gap && array[k-gap] > temp; k-=gap) {

                array[k] = array[k-gap];

            }
            array[k] = temp;
        }
    }
}
