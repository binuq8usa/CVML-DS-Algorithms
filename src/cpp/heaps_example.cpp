/*
Heaps in C++ tutorial

make_heap by default is a max heap

*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string_view>
#include <functional>

using namespace std;

void print(std::string_view text, const std::vector<int>& v = {}) {
  std::cout << text << ": ";
  for(const auto& e : v) 
    std::cout << e << ' ';
  std::cout << "\n";
}

// To execute C++, please define "int main()"
int main() {
  std::vector<int> elements = {20, 30, 40, 25, 15};

  // make the heap
  make_heap(elements.begin(), elements.end());

  // print
  print("Max Heap" , elements);

  // make the min heap
  make_heap(elements.begin(), elements.end(), std::greater<>{});
  print("Min Heap", elements);

  // push an element and bubble up the element
  elements.push_back(10);
  push_heap(elements.begin(), elements.end(), std::greater<>{});

  print("New min heap", elements);

  // check if its a heap
  bool isHeap = is_heap(elements.begin(), elements.end(), std::greater<>{});
  std::cout << "is heap " << isHeap << std::endl;
  // sort heap
  sort_heap(elements.begin(), elements.end(), std::greater<>{});
  print("Sorted heap", elements);
}
