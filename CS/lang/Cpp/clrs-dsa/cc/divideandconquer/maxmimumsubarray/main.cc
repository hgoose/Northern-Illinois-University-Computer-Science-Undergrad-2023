#include <iostream>
#include <limits>
#include <vector>
#include <tuple>
#include <numeric>
using std::cout;
using std::vector;
using std::endl;
using std::tuple;

constexpr int ninf = std::numeric_limits<int>::min();

typedef vector<int>& V;
typedef tuple<int, int, int> pack;
pack fmcs(V A, int low, int med, int high) {     
    int leftsum = ninf;
    int sum = 0;
    int maxleft = 0;

    for (int i=med; i>=0; --i) {
        sum+=A[i];
        if (sum > leftsum) {
            leftsum = sum;
            maxleft = i;
        }
    }

    int rightsum = ninf;
    sum = 0;
    int maxright = 0;
    for (int j=med+1; j<=high; ++j) {
       sum+=A[j]; 
       if (sum > rightsum) {
           rightsum=sum;
           maxright=j;
       }
    }

    return {maxleft, maxright, leftsum+rightsum};
}

pack fms(V A, int low, int high) {
    if (low == high) {
        return {low, high, A[low]};
    } else {
        int mid = (low + high) / 2;
        pack lowpack, highpack, crosspack;

        lowpack = fms(A, low, mid);
        highpack = fms(A, mid+1, high);
        crosspack = fmcs(A, low, mid, high);

        if (std::get<2>(lowpack) >= std::get<2>(highpack) && std::get<2>(lowpack) >= std::get<2>(crosspack)) {
            return lowpack;
        } else if (std::get<2>(highpack) >= std::get<2>(lowpack) && std::get<2>(highpack) >= std::get<2>(crosspack)) {
            return highpack;
        } else return crosspack;
    }
}

int main(int argc, char** argv) {

    vector<int> A{1,3,-4,8,-2,6,-12,7};

    auto [low,high,sum]  = fms(A, 0, A.size()-1);

    for (const auto& item : A) {
        cout << item << " ";
    }
    cout << endl;

    cout << "Low: " << low << endl 
        <<  "High: " << high << endl
        << "Sum: " << sum << endl;

    return 0;
}
