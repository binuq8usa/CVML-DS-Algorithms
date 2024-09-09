/*

You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index 0, or the step with index 1.

Return the minimum cost to reach the top of the floor.

*/
/*

nums = [10,15,2,20,30]

#cost of ith step

# step with index 0 or step with index 1

# min cost to reach ith step

0th step , min_cost[0] = cost[0]
1st step, min_cost[1] = cost[1]
2nd step, min_cost[2] = min(cost[0], cost[1]) + cost[2]
....
nth step , min_cost[n] = min( min_cost[n-1], min_cost[n-2]) + cost[n]

0 .... n-1
n-1 to 0
n-1 = 5

n = 5
dp[5] =0
i = n-1 to 0
dp[n-1] = cost[n-1] + min(dp[n-2], dp[n-3])
dp[i] = cost[i] + min(dp[i-1], dp[i - 2])

dp[4] = cost[4] + min(dp[3],d[2])

dp[n-1] = 0 // min cost to reach top from n is zero because we are already at the top
dp[n-2] = cost[n-2] + min(dp[

dp[n] = 0
dp[ith] = cost[i] 

dp[4] = cost[4]
dp[3] = cost[3] + cost[4]
dp[2] = cost[2] + min(dp[3], dp[4])
dp[1] = cost[1] + min(dp[2], dp[3))

dp[i] = cost[i] + min(dp[i+1], dp[i+2])

dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-1])

base case - dp[0] = dp[1] = 0

*/


#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unordered_map<int, int> Cache;

int minimumCost(const vector<int>& nums, Cache& cache, int index) {

// basic reccur
// dp[i] # cost needed to reach ith stair from 0 or 1 without considering the current cost
// dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2])
// index 5
// 
  std::cout << "index : " << index << std::endl;
  if (index == 0 or index == 1) {
    cache.insert(make_pair(index,0));
    return 0;
  }

  // index = 5
  if (cache.find(index-1) == cache.end()) {
    int val = minimumCost(nums, cache , index-1);
    cache.insert(make_pair(index-1, val));
  }

  if (cache.find(index-2) == cache.end()) {
    int val = minimumCost(nums, cache , index-2);
    cache.insert(make_pair(index-2, val));
  }

  return min(cache[index-1] + nums[index-1], cache[index-2] + nums[index-2]);
}

int computeMinCost(const vector<int>& nums){
  Cache cache;
  return minimumCost(nums, cache, nums.size());
}

// To execute C++, please define "int main()"
int main() {
  vector<int> nums{1,100,1,1,1,100,1,1,100,1};
  int minCost = computeMinCost(nums);
  std::cout << "Minimum Cost : " << minCost << std::endl;
}
