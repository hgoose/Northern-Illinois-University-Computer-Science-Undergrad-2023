#include <cmath>

int minimum(int array[], int n) {
    return array[0];
}
int maximum(int array[], int n) {
    return array[n-1];
}
int range(int array[], int n) {
    return array[n-1] - array[0];
}
double average(int array[], int n) {
    int sum = 0;

    for (int i=0; i<n; ++i) {
        sum+=array[i];
    }
    return static_cast<double>(sum) / n;
}

double median(int array[], int n) {

    int p = 0;
    if (n % 2 == 0) {
        p = (n/2) - 1;
        return static_cast<double>(array[p] + array[p+1]) / 2;
    } else {
        p = ((n+1)/2) -1;
        return array[p];
    }
}

double stddev(int array[], int n) {

    double variance_sum=0;
    double variance = 0;
    double stddev = 0;
    double avg = 0.0f; 

    avg = average(array, n);

    for (int i=0; i<n; ++i) {
        variance_sum  += (array[i] - avg) * (array[i] - avg);
    }
    
    variance = variance_sum / n;

    stddev = sqrt(variance);

    return stddev;




}

