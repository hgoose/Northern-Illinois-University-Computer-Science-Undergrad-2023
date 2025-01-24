#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <utility>
using std::cout;
using std::pair;
using std::string;
using std::vector;
using std::endl;
using std::list;

template<typename key, typename value>
class umap {
private:
    static const size_t default_buckets = 16;
    static constexpr float load_factor = 0.75f;

    vector<list<pair<key, value>>> buckets;
    size_t size = 0;

    void hash(key k) {
        return std::hash<key>{}(k) % buckets.size();
    }

    void rehash() {

    }

public:

    umap() : buckets(default_buckets) {}

};

int main(int argc, char** argv) {

    

    return 0;
}
