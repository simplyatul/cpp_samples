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
    int capacity_=DEF_CACHE_CAP;
    list<int> lruList_; // key at the front is LRU key. One can do other way round as well
    unordered_map<int /*key*/, value /*value*/> cache_;

public:
    LruCache(){}
    LruCache(const uint32_t cap): capacity_(cap)  {}

    void put(const int &k, const int &v) {
        cout << "Putting key: "  << k << endl;
        // key found
        const auto it = cache_.find(k);
        if(it != cache_.end()) {
            // key found. Update the value
            it->second.v_ = v;
            // remove the key ref from lruList
            lruList_.erase(it->second.it_);
            // put the key at end of the list
            lruList_.push_back(k);
            it->second.it_ = std::prev(lruList_.end());
            return;
        }
        // key not found
        if(cache_.size() >= capacity_) {
            // capacity is full. Evict the LRU key
            auto lruKey = lruList_.front();
            lruList_.erase(lruList_.begin());
            cache_.erase(lruKey);
        }
        lruList_.push_back(k);
        value tempv(k, v, std::prev(lruList_.end()));
        cache_.insert(pair<int, value>(k, tempv));
              
        // Following works too
        /* 
        cache_.insert(pair<int, value>(k, 
                value(k ,v, lruList_.end())));
        */
       return;
    }

    int get(const int& k) {
        cout << "Getting key: "  << k << endl;
        const auto it = cache_.find(k);
        if(it != cache_.end()) {
            // key found
            lruList_.erase(it->second.it_);
            // put the key at end of the list
            lruList_.push_back(k);
            it->second.it_ = std::prev(lruList_.end());

            return it->second.v_;
        }
        return -1;
    }

    int getCapacity() { return capacity_;}

    void print()
    {
        static int k = 1;
        cout << "********" << k << " Start ********\n";
        for (const auto x: lruList_)
            cout << x << ' ';
        std::cout << '\n';

        for(const auto n: cache_) 
            cout << n.second.k_ << ' ';
        std::cout << '\n';

        for(const auto n: cache_) 
            cout << *(n.second.it_) << ' ';
        std::cout << '\n';
        cout << "********" << k << " End ********\n";
        k++;
    }


};

int main() {
    LruCache c(3);
    cout << "Capacity: " << c.getCapacity() << endl;
    c.put(1, 10);
    c.put(2, 20);
    c.put(3, 30);
    //cout << "After inserting keys 1, 2, 3" << endl;
    c.print();

    c.put(4, 40);
    c.print();

    c.get(3);
    c.print();

    c.put(5, 50);
    c.print();

    c.put(4, 400);
    c.print();
    return 0;
}