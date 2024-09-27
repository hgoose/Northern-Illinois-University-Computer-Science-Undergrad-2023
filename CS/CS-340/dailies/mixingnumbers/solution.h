#include <iterator>
#include <vector>
#include <utility>
using std::vector;
using std::distance;

template <typename FORWARDIT, typename T>
void swap_iter_onvalue(FORWARDIT it1, FORWARDIT it2) {
    T tmp = *it1;
    *it1 = *it2;
    *it2 = tmp;
}

template <typename ForwardIterator>
void mixNumbers(ForwardIterator begin, ForwardIterator end){

    int size = distance(begin, end);

    vector<std::pair<int,int>> c;

    // Pair<element, index>
    int tmpidx = 0;
    for (auto it = begin; it!=end; ++it, ++tmpidx) {
        c.push_back(std::make_pair(*it, tmpidx));
    }

    // { {0,4} , {1,2} };

    auto it = begin;
    // int count = 0;
    int j=0;
    for (;j<size; ++j) {
        it = begin;

        int val = c[j].first;

        if (val < 0) {
            int curr_pos = c[j].second;
            int adjusted_pos = curr_pos + val;

            for (int k=0; k<adjusted_pos; ++k)  {
                ++it;
            }
            val=-val;
        } else {
            for (int k=0; k<c[j].second; ++k) {
                ++it;
            }
        }


        auto curr = it;
        vector<int>::iterator next = curr;

        int forward=0;
        for (int i=0; i<val; ++i,++curr, ++forward) {
            int pos = std::distance(begin, curr);
            if (pos >= size-1) break;

            if ((curr + 1) != end){
                next = curr + 1;
                swap_iter_onvalue<std::vector<int>::iterator, std::decay_t<decltype(*begin)>>(curr, next);

                if ((j + 1) < size) {
                    int next_forward = forward+1;
                    ++(c[j].second);
                    --(c[next_forward].second);
                }
            }

        }
    }




}
