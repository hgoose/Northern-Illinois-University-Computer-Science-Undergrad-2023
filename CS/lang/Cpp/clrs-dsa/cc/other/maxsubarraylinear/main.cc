#include <iostream>
#include <vector>
#include <tuple>
using std::cout;
using std::vector;
using std::endl;
using std::tuple;

typedef vector<int>& V;
typedef tuple<int,int,int> pack;

pack fms(V A, int start, int end) {
    int low, high, sum, currsum;
    low = 0, high = 0, sum = 0, currsum=0;
    int prev_low;

    for (int i=0; i<end; ++i) {
        sum+=A[i];
        if (sum > currsum) {
            currsum = sum;
            high = i;
        }
        if (sum <= 0) {
            prev_low = low;
            low = i + 1;
            sum = 0;
        }
    }

    return {(low > high ? prev_low : low) ,high, currsum};
}

int main(int argc, char** argv) {

    vector<int> v{1,-3,2,3,-4};
    // vector<int> v{1,3,-4,8,-2,6,-12,7};

    for (const auto& item : v) {
        cout << item << " ";
    }
    cout << endl;

    auto [low,high,sum] = fms(v,0,v.size());
    cout << "Low: " << low << endl << "High: " << high << endl << "Sum: " << sum << endl;



    return 0;
}
