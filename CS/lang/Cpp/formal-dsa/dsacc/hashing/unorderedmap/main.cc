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

    size_t hash(const key& k) const {
        return std::hash<key>{}(k) % buckets.size();
    }

    void rehash() {
        vector<list<pair<key,value>>> new_buckets(buckets.size() * 2);

        for (const auto& bucket : buckets) {
            for (const auto& pair : bucket) {
                size_t h = std::hash<key>{}(pair.first) % (buckets.size() * 2);
                new_buckets[h].emplace_back(pair.first, pair.second);
            }
        }
        buckets.swap(new_buckets);
    }

public:
    umap() : buckets(default_buckets) {}

    void insert(const key& k, const value& v) {
        if (static_cast<float>(size) / buckets.size() > load_factor) {
            rehash();
        } 

        size_t h = hash(k);        
        auto& bucket = buckets[h];

        for (auto it = bucket.begin(); it!=bucket.end(); ++it) {
            if (it->first == k) {
                it->second = v;
                return;
            }
        }
        bucket.emplace_back(k,v);
        ++size;
    }

    value* find(const key& k) {
        size_t h = hash(k);
        auto& bucket = buckets[h];

        for (auto it = bucket.begin(); it!=bucket.end(); ++it) {
            if (it->first == k) {
                return &(it->second);
            }
        }
        return nullptr;
    }

    bool empty() const {
        return size == 0;
    }

    void erase(const key& k) {
        size_t h = hash(k);
        auto& bucket = buckets[h];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == k) {
                bucket.erase(it);
                --size;
                return;
            }
        }
    }

    value& operator[](const key& k) {
        size_t h = hash(k);
        auto& bucket = buckets[h];
        for (auto it = bucket.begin(); it!=bucket.end(); ++it) {
            if (it->first == k) return it->second;
        }

        buckets[h].emplace_back(k, value());
        ++size;
        return buckets[h].back().second;
    }

    void print() const {
        for (const auto& bucket : buckets) {
            for (const auto& pair : bucket) {
                cout << pair.first << "->" << pair.second << endl;
            }
        }
    }
};

int main(int argc, char** argv) {

    umap<int,int> m;
    m.insert(10,20);
    m.insert(5,10);
    m[1] = 10;
    m[1] = 25;

    

    cout << endl << endl;
    m.print();

    

    return 0;
}
