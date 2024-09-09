/*

You are given two 0-indexed integer arrays nums and multipliers of size n and m respectively, where n >= m.

You begin with a score of 0. You want to perform exactly m operations. On the ith operation (0-indexed) you will:

Choose one integer x from either the start or the end of the array nums.
Add multipliers[i] * x to your score.
Note that multipliers[0] corresponds to the first operation, multipliers[1] to the second operation, and so on.
Remove x from nums.
Return the maximum score after performing m operations.


*/

/*
a = [1,2,3,4,5,6]

multiplier = [2,6,5,4]

exactly only m (or 4 operations)
1. Take 2, select either 1 or 6, multiply it and save the result - dp
2. state variable - ith - multiplier, left_index (left pointer) or right_index (right pointer) - increments after doing the operation
3. 3rd operation, 2 nums were picked from left, 1 was picked from right. right_index (right_pointer) = size(a) - 1 - (i - left)
4. dp(4,left_index) = 0 => base case 
5. dp 
6. max_score(i, left_index) = max(multiplier(i) * nums[left_index] + max_score(i+1, left_index+1), multiplier(i) * nums[right_index] + max_score(i+1, left_index)
7. 0 to m-1
7. max_score(m, left_index) = 0 (no operations left) - base case

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

// holds key as the mutliplier index, value as the pair of left_index, and max score 
typedef std::vector<int>::iterator VecIt;
typedef std::vector<std::vector<int>> Cache;
int dp_max_score(int mIndex, int leftIndex, Cache& cache, const vector<int>& nums, const vector<int>& multiplier) {
  
  // base case = 0
  if (mIndex == multiplier.size()) {
    return 0;
  }

  int rightIndex = nums.size() - 1 - (mIndex - leftIndex);

  if (cache[mIndex][leftIndex] == 0) {
    cache[mIndex][leftIndex] = max( multiplier[mIndex] * nums[leftIndex] + dp_max_score(mIndex+1,leftIndex+1, cache, nums, multiplier) ,
    multiplier[mIndex] * nums[rightIndex] + dp_max_score(mIndex+1, leftIndex, cache, nums, multiplier));
  }

  return cache[mIndex][leftIndex];
}

int findMaxScore(vector<int>& nums, vector<int>& multiplier) {

  Cache cache(multiplier.size(), std::vector<int>(nums.size(),0));
  return dp_max_score(0, 0, cache, nums, multiplier);
}

// To execute C++, please define "int main()"
int main() {
  vector<int> nums{-5,-3,-3,-2,7,1};
  vector<int> multipliers{-10,-5,3,4,6};

  int maxScore = findMaxScore(nums, multipliers);

  std::cout << "Max Score : " << maxScore << std::endl;

}
