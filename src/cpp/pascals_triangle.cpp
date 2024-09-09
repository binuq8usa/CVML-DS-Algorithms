/*1 
1 1
1 2 1
1 3 3 1
1 4 6 4 1

f(rowIndex, colIndex) = f(rowIndex-1, colIndex-1) + f(rowIndex-1, colIndex)

rowIndex =0 f(rowIndex, colIndex) or f(0,0) = 1
rowIndex = 1 f(rowIndex, colIndex) = 1 1
or rowIndex == colIndex

*/


#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <string_view>

using namespace std;

typedef std::unordered_map<string, int> Cache;

template <typename T>
void print(string_view text, vector<T> element) {
  std::cout << text << ": ";
  for(const auto& e : element) {
    std::cout << e << " ";
  }
  std::cout << "\n";
}

vector<int> getPascalVector(int rowIndex, Cache& cache) {
  if (rowIndex == 0) return vector<int>(1,1);
  if (rowIndex == 1) return vector<int>(2,1);
  vector<int> element;
  element.push_back(1);
  for (int colIndex = 1; colIndex < rowIndex; colIndex++) {
    string key1 = std::to_string(rowIndex-1) + ',' + std::to_string(colIndex-1);
    string key2 = std::to_string(rowIndex-1) + ',' + std::to_string(colIndex);
    if (cache.find(key1) == cache.end()) {
      int val1 = getPascalVector(rowIndex-1, cache)[colIndex-1];
      cache.insert(make_pair(key1,val1)); 
    }
    if (cache.find(key2) == cache.end()) {
      int val2 = getPascalVector(rowIndex-1, cache)[colIndex];
      cache.insert(make_pair(key2, val2));
    }

    element.push_back(cache[key1] + cache[key2]); 
  }
  element.push_back(1);
  return element;
}

// To execute C++, please define "int main()"
int main() {
  Cache cache;
  for(int rowIndex = 0; rowIndex < 20; rowIndex++) {
    auto entry = getPascalVector(rowIndex, cache);
    print("Row",entry);
  }

}