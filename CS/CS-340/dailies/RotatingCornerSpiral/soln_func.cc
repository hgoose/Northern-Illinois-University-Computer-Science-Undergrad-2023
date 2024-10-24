#include <vector>
#include <functional>
using std::vector;
using std::function;

vector<int> RotatingCornerSpiral(vector<vector<int>> &m) {

    // Check if the matrix is square
    for (int i=0; i<(int) m.size(); ++i) {
        if ((int) m[i].size() != (int) m.size())  {
            return {};
        }
    }

    // Result vector
    vector<int> r;

    // M is non existent
    if ((int)m.size() == 0) return r;

    // M is a scalar
    if ((int)m.size() == 1 && (int)m[0].size() == 1) {
        r.push_back(m[0][0]);
        return r;
    }

    // M is 2\times 2
    if ((int)m.size() == 2 && (int)m[0].size() == 2) {
        for (int i=0; i<2; ++i) {
            r.push_back(m[0][i]);
        }
        for (int i=1; i>=0; --i) {
            r.push_back(m[1][i]);
        }
        return r;
    }

    // M is at least 3\times 3
    std::function<void(int,int,int,int)> r_rotate = [&](int rlb, int rrb, int ctb, int cbb) -> void {
        // Base case 1: Subvector is size one \times one (scalar)
        if ((rrb - rlb == 1) && (cbb - ctb == 1)) {
            r.push_back(m[rlb][ctb]);
            return;
        }

        // Base case 2: Subvector is size 2\times 2
        if ((rrb - rlb == 2) && (cbb - ctb == 2)) {
            for (int i=rlb; i<rrb; ++i)  {
                r.push_back(m[rlb][i]);
            }

            for (int i=rrb-1; i>=rlb; --i)  {
                r.push_back(m[cbb-1][i]);
            }
            return;
        }

        // Else, get the sequence of the outer layer and recurse to the inner.
        
        int count = 0;
        int rstart = rlb, rend = rrb-1;
        int cstart = ctb, cend = cbb-1;
        while (count < (rrb-rlb-1) ) {
            r.push_back(m[rstart][cstart]);
            r.push_back(m[cstart][rend]);
            r.push_back(m[rend][cend]);
            r.push_back(m[cend][rstart]);

            cstart+=1;
            cend-=1;

            ++count;
        }
        r_rotate(rlb+1,rrb-1,ctb+1,cbb-1);

    };
    r_rotate(0, (int)m.size(), 0, (int)m[0].size());

    return r;
}
