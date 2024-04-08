#include <string>

using std::string;

bool ends_with(const char* src, const char* suffix) {

    bool ret = 1;
    size_t len_suffix = ((string) suffix).size(), 
           len_src = ((string) src).size();

    if (len_suffix > len_src) return 0; 


    for (size_t i=len_src-1, j=len_suffix-1; i>=len_suffix; --i, --j) {
        if (src[i] != suffix[j]) {
            ret = 0;
        }
    }

    return ret;
}

