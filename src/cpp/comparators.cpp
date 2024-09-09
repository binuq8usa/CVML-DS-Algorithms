/*
Tutorial on comparators

https://www.geeksforgeeks.org/comparator-in-cpp/

*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <string_view>

using namespace std;

bool compare(pair<int,int> a, pair<int,int> b) {
  return a.first < b.first;
}

void print(std::string_view text, vector<pair<int,int>> elements) {
  std::cout << text << ": ";
  for(const auto& element : elements) {
    std::cout << "(" <<element.first << "," << element.second << ") ";
  } 
  std::cout << "\n";
}

int main(int argc, char** argv) {
  std::vector<std::pair<int,int>> elements = {
    {1,2},
    {2,2},
    {3,4},
    {6,2},
    {4,10}
  };

  print("Original Text", elements);

  std::sort(elements.begin(), elements.end(), compare);
  print("After sorting", elements);

  // make a max heap
  std::make_heap(elements.begin(), elements.end(), compare);
  print("Max Heap", elements);

  // lambda compare function to get minimum heap
  auto compare2 = [&] (pair<int,int> a, pair<int,int> b) {
    return a.first > b.first;
  };
  std::make_heap(elements.begin(), elements.end(), compare2);
  print("Min Heap", elements);
}