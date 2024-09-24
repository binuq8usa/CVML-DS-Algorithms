/*
Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b

eg: 
arr = [1,3,6,7,9,10]

output - [a1,a2,a3,...a_k] - k elements
constraint - a1 < =a2 <= a3 <= ...a_k
|a - x | < |b - x| - abs(a-x, bx) pr dif is same a < b 
lambda x : (|a - x| - |b - x|) => key   

sort - in the second step (with use that a < b constraint)

k closest integers => set a max heap => top element will always give us the element with the largest difference with the heap storing the smallest elements. so, an element smaller than the heap max will be inserted and the max removed. 
Algorithm
1. Iterate through each element. 
2. Compare the element x with every element in arr.
3. Put this in a min_heap -> heap key => |a-x|.
      If heapCount is max, we check if top heap max element is smaller that current. If so, pop_heap, add in the smallest element. 
      If top heap max element is smaller than current, we move on.
4. End of iteration, we take the heap, and keep removing the element, and add to a list. We can use double linked list or a stack where we push , and then pop will be the integer with the least diff value with x
5. 

Test case
arr = [1,3,6,7,9,10]
k = 3, x = 5
k = 4, x = 4

arr = [1,3,6,7,9,10]

diff = [-4,-2,1,2,4, 5] =>     3,6,7 =? (pivot_index - k/2, pivot_index + k/2 - once diff > 0)
diff = [-3, 1,2,]


result_1 = [6, 7, 3, 9, 1, 10] - after heap operation
diff_1 = [1, 2, 2, 4, 5] => 



sort - sort the array in log 
heap_sort(comparison)

or NlogN sort.

or pop the last element - O(N) in a stack

result = iterate through stack - 


N log K

since its sorted

get the diff vector 
diff = [4,2,1,2,4,5]

iterate through 2 points - sliding window of k elements 
case 1 : first element and element to compare has the smallest difference -> any other difference is going to be k elements from the pivot
case 2 : element in the middle. 

1. Find the pivot index where the diff vector starts to increase. (num - x)
2. Any k elements before pivot is the smallest.
3. Create a sliding window.
  ---> populate a vector. Add element if diff <= 0 => diff <= 0
  ---> 


*/

#include <array>
#include <cerrno>
#include <cstddef>
#include <iostream>
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>
#include <list>
#include <string_view>

using namespace std;

struct CompareByX {
  int x;
  CompareByX(int x) : x(x) {}
  bool operator()(int a, int b) {
    int diff_a = abs(a-x);
    int diff_b = abs(b-x);

    return (diff_a < diff_b) ||  ( diff_a == diff_b && a < b);
  }
};

void printArray(string_view text, const vector<int>& arr) {
  cout << text << " : " ;
  for(auto& num : arr) {
    cout << num << " ";
  }
  cout << "\n" << endl;
}

vector<int> findKClosestElements(const vector<int>& nums, int k, int x) {
  vector<int> result;
  CompareByX comp(x); // x = 5
  
  // iterate over the numbers and push the heap
  
  // Time complexity = N log K, space complexity - O(K)
  for (auto& num: nums) { // O(N) => O(K)
    result.push_back(num); // 1 // 3 // 6 // 7. => 7, 3,6, 10
    // Log(K)
    push_heap(result.begin(), result.end(), comp); // 1 (4), 3(2), 6(1) // 7(2) =>  9(4), 7(2) , 3(2), 6(1) => 10(5), 7(2) , 3(2), 6(1) 
    printArray("Heap In", result);
    if (result.size() > k) {
      pop_heap(result.begin(), result.end(), comp); // 7(2) , 3(2), 6(1) 
      printArray("Heap after pop before removal", result);
      result.pop_back();
      printArray("Heap after pop", result);
    } 
  }
  if (!std::is_heap(result.begin(), result.end())) {
    std::make_heap(result.begin(), result.end());
 
    sort_heap(result.begin(), result.end());
//   printArray("Heap : ", result);

//   list<int> sortedResult;
//   for(int i = 0 ; i < k ; i ++) {
//     pop_heap(result.begin(), result.end(), comp); //3(2), 6(1). 7(2)
//     cout << "result : " << *(result.rbegin()) << endl;
//     sortedResult.push_front(*result.rbegin()); // the max in the front //     6  3 7
//     result.pop_back();
//   }

//   return vector<int>(result.begin(), result.end());
    return result;
}

// To execute C++, please define "int main()"
int main() {
  vector<int> arr{1,3,6,7,9,10};
  int k = 3, x = 5;
  auto result = findKClosestElements(arr, k, x);
  printArray("Result", result);
}
