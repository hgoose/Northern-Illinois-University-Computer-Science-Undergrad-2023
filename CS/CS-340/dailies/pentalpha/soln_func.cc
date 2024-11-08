#include <utility>
#include <map>
using std::pair;
using std::map;

using ushort = unsigned short;

template<typename T>
struct types {
    using star_map = map<T, pair<T, T>>;

};

bool pentalpha(int place_order[]) {
    // Transitions
    types<ushort>::star_map smap = {{0, {5,6}}, 
        {1,{3,7}}, 
        {2, {4,8}},
        {3, {1,9}},
        {4, {2,7}},
        {5, {0,9}},
        {6, {0,8}},
        {7, {1,4}},
        {8, {2,6}},
        {9, {3,5}},
    };

    ushort curr = place_order[0];

    int count=1;
    while (count < 10) {
        auto curr_it = smap.find(curr);
        if (curr_it != smap.end()) {
            pair<ushort, ushort> curr_pair = curr_it->second;
            curr = curr_pair.first;

            for (int i=0; i<(int) count; ++i) {
                if (curr == place_order[i]) {
                    curr = curr_pair.second;
                    break;
                }
            }
        }
        place_order[count++] = curr;
    } 

    return true;
}
