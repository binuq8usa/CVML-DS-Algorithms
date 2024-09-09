/*

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
*/

/*

nums = [1,3,4,8,10,2,4]

constraint - cannot rob two adjacent houses. Not two adjacent numbers

[1,4,10,4]
[3,8,2]

state - dp(i) = max(dp(i-1), nums[i] + dp(i-2))



top-down approach with memoization

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
using namespace std;

typedef unordered_map<int, int> Cache;

int findMax(const vector<int>& nums, Cache& cache, int index) {
  if (index == 0) {
    cache.insert(make_pair(index,nums[index]));
    std::cout << "Index : " << index << " Val : " << nums[index] << std::endl;
    return nums[index];
  }

  if (cache.find(index-1) == cache.end()) {
    int val = findMax(nums, cache, index-1);
    std::cout << "Index : " << index << " Val : " << val << std::endl;
    cache.insert(make_pair(index-1, val));
  }

  if (index == 1) {
    std::cout << "Index : " << index << " Val : " << nums[index] << std::endl;
    std::cout << "Cache Index : " << index-1 << " Val : " << cache[index-1] << std::endl;
  
    return max(cache[index-1], nums[index]);
  }

  if (cache.find(index-2) == cache.end()) {
    int val = findMax(nums, cache, index-2);
    std::cout << "Index : " << index << " Val : " << val << std::endl;
    cache.insert(make_pair(index-2, val));
  }

  return max(cache[index-1], cache[index-2] + nums[index]);
}

// To execute C++, please define "int main()"
int main() {
  vector<int> nums{2,7,9,3,1};
  Cache cache;
  int maxVal = findMax(nums, cache, nums.size()-1); 

  std::cout << "Max Val : " << maxVal << std::endl;
}
