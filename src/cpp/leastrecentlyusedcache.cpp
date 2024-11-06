/*
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.

key,val - int,int
get O(1) -> unordered_map<int,int> -> hashmap O(1)
put O(1) -> hashmap (1)

L members -> the one with least recently used key needs to be evicted.

Heap - not a efficient structure
<data_structure> top element -> least_recently_used -> pop -> add the element - O(logN)

stack -> LIFO ->    a,b,c,d(Key) -> stack (keys) -> a,b,c,d => d least recently used => remove (d), use to remove from the hashmap -> O(1)

get O(1) ->  search for the key to be updated -> O(N) => 


key -> val   
key -> timestamp. 

key -> val

# 
key -> 

unordered_map -> key1, list::iterator it > 
list -> (key1, value1),   -> 

O(1)
put() -> if no key exists, 
          -> check if elementsexceed, remove from the bottom of the list. O(1)
        ->add to map
        -> add to top of list

      -> if key exists, remove from list (using the iterator) - O(1)
        -> add the key, new_value -> top of the list -

get() -> if key exists
        -> get the current iterator from map
        -> using iterator, get value
        -> remove this remove from list,
        -> add the element to top of the list
        -> update the map value with updated pointer 

      -> if no key, return -1

new elements -> add to the top of the list 

*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <utility>
#include <cassert>

using namespace std;

typedef list<pair<int,int>>::iterator ListIterator; // stores key, val

class LRUCache{
  protected:
    unordered_map<int, ListIterator> mHashmap;  // stores key and iterator
    list<pair<int,int>> values; 
    int maxLen;

    // TODO: return the value which got updated
    ListIterator _update(ListIterator& l_it, int key, int newValue) {
      // update map and list
      this->values.erase(l_it); // O(1)
      this->values.push_front(make_pair(key,newValue)); // most recent item to top of the values list and  
      return this->values.begin();
    }

  public:

    LRUCache(int maxLen) : maxLen(maxLen) {}
    ~LRUCache() {}

    // 
    int get(int key) { // O(1)
      auto it = mHashmap.find(key); // O(1)
      if (it == mHashmap.end()) return -1;

      // get the value iterator
      ListIterator l_it = it->second;

      int value = (*l_it).second;
      it->second = this->_update(l_it, key, value); //update the map with new iterator
      return value;
    }

    void put(int key, int value) {
      auto it = mHashmap.find(key);
      if (it == mHashmap.end()) {
        if (values.size() >= this->maxLen) {
          // purge
          auto lri = this->values.back();
          this->values.pop_back();
          auto it = mHashmap.find(lri.first);

          // remove from map
          mHashmap.erase(it);
          assert (this->values.size() == maxLen-1);
          assert (this->mHashmap.size() == maxLen-1);
        }
        this->values.push_front(make_pair(key,value));
        this->mHashmap.insert(make_pair(key, this->values.begin()));

        assert (this->values.size() <= maxLen);
        assert (this->mHashmap.size() <= maxLen);

      } else{
        ListIterator l_it = it->second;

        // update map and list
        it->second = this->_update(l_it, key, value);
      }
    }
};

// To execute C++, please define "int main()"
int main() {

  LRUCache lcache(2);
  std::cout << lcache.get(0) << std::endl;
  lcache.put(0,1);
  std::cout << lcache.get(0) << std::endl;
  lcache.put(1,2);
  std::cout << lcache.get(0) << std::endl;
  lcache.put(2,3);
  std::cout << lcache.get(2) << std::endl;

  lcache.put(3,4);
  lcache.put(4,5);
  lcache.put(6,7);
  std::cout << lcache.get(4) << std::endl;

  lcache.put(3,4);
  std::cout << lcache.get(3) << std::endl;
}
