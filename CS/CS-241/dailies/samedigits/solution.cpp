#include <algorithm>
#include <string>

bool same_digits(int a, int b) {


    std::string a_str = std::to_string(a), 
                b_str = std::to_string(b);
    

    std::sort(a_str.begin(), a_str.end(), [] (char c1, char c2) -> bool {
            return c1 < c2;
    });

    std::sort(b_str.begin(), b_str.end(), [] (char c1, char c2) -> bool {
            return c1 < c2;
    });

    return !a_str.compare(b_str);

}

