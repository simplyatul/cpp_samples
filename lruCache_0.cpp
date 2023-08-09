/*
 * run: g++ lruCache_0.cpp
 * Implement fixed size LRU Cache. Supports following APIs 
 * put(key, value)
 *  - puts/overrides key in cache
 *  - if cache is full then evicts least recently used key
 *  - and put this new key
 * get(key)
 *  - returns value or -1 if key is not present
 * 
 * Take key and value as integers for simplicity
 * If key is touched either in put or get, consider key is used
 */
#include <iostream>
#include <unordered_map>
#include <list>
#include <cstdint>
#include <utility>

using namespace std;

constexpr int DEF_CACHE_CAP = 10;

struct value {
    int k_;
    int v_;
    list<int>::iterator it_; /*key ref in lurList_*/
    value(int k, int v, list<int>::iterator i) {
        k_ = k;
        v_ = v;
        it_ = i;
    }
};

class LruCache {
private:
    int capacity_=10;
    list<int> lruList_;
    unordered_map<int /*key*/, value /*value*/> cache_;

public:
    LruCache(){}
    LruCache(const uint32_t cap): capacity_(cap), lruList_(cap)  {}

    void put(const int &k, const int &v) {
        // key found
        const auto it = cache_.find(k);
        if(it != cache_.end()) {
            // update the value
            it->second.v_ = v;
            // ToDo: remove the key ref from lruList
            // ToDo: put the key in front of the list
            return;
        }
        // key not found
        if(cache_.size() >= capacity_) {
            // capacity is full
            // evict the LRU key
            auto lruKey = lruList_.front();
            lruList_.erase(lruList_.begin());
            cache_.erase(lruKey);
        }
        lruList_.push_back(k);
        value tempv(k, v, lruList_.begin());
        cache_.insert(pair<int, value>(k, tempv));

              
        // Following works too
        /* 
        cache_.insert(pair<int, value>(k, 
                value(k ,v, lruList_.end())));
        */

    }

    int get(const int& k) {
        const auto it = cache_.find(k);
        if(it != cache_.end()) {
            return it->second.v_;
        }
        return -1;
    }

    int getCapacity() { return capacity_;}

};

int main() {
    LruCache c;
    cout << c.getCapacity() << endl;
 
    return 0;
}