#include <cstdlib>
#include <list>


int last_int_standing(size_t n, size_t step) {

    std::list<int> M;

    for (size_t i=1; i<=n; ++i) {
        M.push_back(i);
    }

    std::list<int>::iterator it = std::begin(M);

    int ef = (step >= n ? step % n : step);

    std::advance(it,ef);

    while (M.size() > 1) {
        it = M.erase(it);

        if (it == std::end(M)) {
            it = std::begin(M);
        }

        for (size_t i=0; i<(step-1); ++i) {
            ++it;

            if (it == std::end(M)) {
                it = std::begin(M);
            }
        }
    }

    return M.front();
}

