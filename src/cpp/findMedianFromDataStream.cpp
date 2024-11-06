/* Find the median for numbers from a data stream
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.

1 ->
2 , 1,2
3. 1,2,3
 1, 2 3, 8
 1,2,3,8 , 4 -> O(N Log N) 

 1,2,3.  4,8
 1,2,3.   4,8,10
 1,2,3,       4,8,10,5

 6 , 1. => 1 , 6
 6,1,5.  =>  1,5.  6
 6,1,5,4. =>. 1,4,     5,6
 two partitions - (either sorted form ) - two heaps
 left heap - max element 
 right heap - min element

 median = left + right/2 if leftheapsize == rightheapsize
 leftheapsize > rightheapsize => median = lefttop
 median = righttop

 (leftheapsize - rightheapsize) <= 1
  => balance heap - move from the largest heap to the next heap
*/

#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

class MedianFinder{
public:
  vector<int> bottomHeap; // max heap - containing the lower half of elements seen
  vector<int> topHeap; // min heap - containing the upper half f element seen

  void pushToBottomHeap(int val) {
      bottomHeap.push_back(val);
      push_heap(bottomHeap.begin(), bottomHeap.end());      
  } 

  void pushToTopHeap(int val) {
      topHeap.push_back(val);
      push_heap(topHeap.begin(), topHeap.end(), greater<int>());      
  } 

  int popFromBottomHeap() {
    pop_heap(bottomHeap.begin(), bottomHeap.end());
    int val = bottomHeap.back();
    bottomHeap.pop_back();
    return val;
  }

  int popFromTopHeap() {
    pop_heap(topHeap.begin(), topHeap.end(), greater<int>());
    int val = topHeap.back();
    topHeap.pop_back();
    return val;
  }

  void addNum(int val) {
    // by default, add to bottom heap
    if (bottomHeap.size() ==0 and topHeap.size() == 0) {
      pushToBottomHeap(val);
    }
    if (bottomHeap[0] >= val) {
      pushToBottomHeap(val);
    } else{
      pushToTopHeap(val);
    }

    // balance the heap
    balance();
  } 

  float findMedian() {
    if (bottomHeap.size() == topHeap.size()) {
      return (static_cast<float>(bottomHeap.front()) + static_cast<float>(topHeap.front())) / 2;
    }
    else if (bottomHeap.size() > topHeap.size()) {
      return static_cast<float>(bottomHeap.front());
    } else {
      return static_cast<float>(topHeap.front());
    }
  }


  void balance() {
    int diff = abs(int(bottomHeap.size()) - int(topHeap.size()));
    if (diff > 1) { // need to balance the heap
      if (bottomHeap.size() > topHeap.size()) {
        int val = popFromBottomHeap();
        pushToTopHeap(val);
      } else{
        int val = popFromTopHeap();
        pushToBottomHeap(val);
      }
    }
  }

}; 

// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const char* const& word : words) {
    cout << word;
  }
  return 0;
}
