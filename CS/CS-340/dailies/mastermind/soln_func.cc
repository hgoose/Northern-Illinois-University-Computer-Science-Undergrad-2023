#include <string>
#include <algorithm>
using std::string;
using std::sort;

int mm_score(string k, string g, int &b, int &w) {

    b = 0, w = 0;

    string nosamespot_key = "", nosamespot_guess = "";

    if (k.size() != g.size()) {
        return 0;
    }

    // Get the black points
    string::iterator g_it = g.begin();
    for (string::iterator k_it = k.begin(); k_it!=k.end(); ++k_it, ++ g_it) {
        if (*k_it == *g_it) {
            ++b;
        } else {
            nosamespot_key+=*k_it;
            nosamespot_guess+=*g_it;
        }
    }

    sort(nosamespot_key.begin(), nosamespot_key.end());
    sort(nosamespot_guess.begin(), nosamespot_guess.end());

    g_it = nosamespot_guess.begin();
    for (string::iterator k_it = nosamespot_key.begin(); k_it!=nosamespot_key.end(); ++k_it, ++ g_it) {
        if (*k_it == *g_it) {
            ++w;
        } 
    }

    return 1;
}
