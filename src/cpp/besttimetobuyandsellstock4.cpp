/*

You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).


State variables

answer : maximumProfit(0, k, holdingStock=0)??

ith day - D days
number of transactions remaining ; tr 0 <= tr<= k
holdingStock = True (yes) or False(no)

maximumProfit(i, tr, holdingStock) = ??

profitIfHoldingStock(i,tr, holdingStock = 1) = prices[i] + maximumProfit(i+1, tr-1, holdingStock = 0) =>buying
profitIfNotHoldingStock(i,tr,holdingStock = 0) = -prices[i] + maximumProfit(i+1, tr-1, holdingStock = 1)
holdStock(i,tr,holdingStock) = dp(i+1, tr, holdingStock)


maximumProfit(i, tr, holdingStock=0) = max( dp(i+1,tr, holdingStock) , prices[i] + maximumProfit(i+1, tr-1, holdingStock=1) ) 
maximumProfit(i, tr, holdingStock=1) = max( dp(i+1,tr, holdingStock) , -prices[i] + maximumProfit(i+1, tr-1, holdingStock=0) )  


maximumProfit(i, 0, holdingStock=0/1) = 0
maximumProfit(D-1,tr, holdingStock=0) = 0 

pIndex : tr remaining key 
tr remaining key -> List of pairs (pair.first = holdingStock, pair.second = val)

maximumProfit(0, k, holdingStock=0)

*/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <list>

using namespace std;

typedef unordered_map<int, unordered_map<int, list<pair<bool,int>> >> Cache;

pair<bool,int> SearchInCache(int pIndex, int trRemain, bool holdingStock, const Cache& cache) {
  auto it_pIndex = cache.find(pIndex);
  bool found = false;
  int val = -1;
  if (it_pIndex != cache.end()) {
    // check for transation
    auto it_r = it_pIndex->second.find(trRemain);
    std::cout << "Debug" << std::endl;

    if (it_r != it_pIndex->second.end()) {
    // check if list is present
      auto pair_list = it_r->second;
      std::cout << "Debug2" << std::endl;
      for(auto& pp : pair_list) {
        std::cout << "Debug3" << std::endl;
        if (pp.first == holdingStock) {
          found = true;
          val = pp.second;
       }
      }
    }
  }
  return make_pair(found,val);
}

void AddToCache(int pIndex, int trRemain, bool holdingStock, Cache& cache, int val) {
  // add the first key to cache if not present
  auto it_pIndex = cache.find(pIndex);
  if (it_pIndex == cache.end()) {
    cache[pIndex] = unordered_map<int, list<pair<bool,int>>>();
  }

  // add the second key to the cache
  auto it_r = cache[pIndex].find(trRemain);
  if (it_r == cache[pIndex].end()) {
    cache[pIndex][trRemain] = list<pair<bool,int>>();
  }

  // add the holding stock flag and value
  cache[pIndex][trRemain].push_back(make_pair(holdingStock, val));
}

int maxProfit(const vector<int>& prices, const int numTransactions, int pIndex, int trRemain, bool holdingStock, Cache& cache)  {
  // base cases
  if (trRemain == 0 || pIndex == prices.size()) return 0;

  // return cache value if found
  auto f_it = SearchInCache(pIndex, trRemain, holdingStock, cache);
  if (f_it.first) {
    std::cout << "Value found for p index :  " << pIndex << ": Val = " << f_it.second << std::endl;
    return f_it.second;
  }

  std::cout << "No Value found for p index :  " << pIndex << std::endl;

  // TODO: Make change : Transactions are made only on selling, not buying!!!!
  int cost = 0.0;
  if (holdingStock) {
    cost = prices[pIndex] + maxProfit(prices, numTransactions, pIndex+1, trRemain-1, !holdingStock, cache);
  } else {
    cost = -1 * prices[pIndex] + maxProfit(prices, numTransactions, pIndex+1, trRemain, !holdingStock, cache);
  }

  int val = max(cost, maxProfit(prices, numTransactions, pIndex+1, trRemain, holdingStock, cache));

  // add value to cache
  std::cout << "Before Added Value found for p index :  " << pIndex << ": Val = " << val << std::endl;
  AddToCache(pIndex, trRemain, holdingStock, cache, val);
  std::cout << "Added Value found for p index :  " << pIndex << ": Val = " << val << std::endl;
  return val;
}

int getMaximumProfit(const vector<int>& prices, int numTransactions) {
  Cache cache;
  return maxProfit(prices, numTransactions, 0, numTransactions, false, cache);
}

void test_case(const vector<int>& prices, int numTransactions) {
  int cost = getMaximumProfit(prices, numTransactions);
  std::cout << "Maximum profit : " << cost << std::endl;
}

// To execute C++, please define "int main()"
int main() {
  test_case(vector<int>{3,2,6,5,0,3},2);
}
