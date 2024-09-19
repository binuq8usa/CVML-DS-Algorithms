/*

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Single transaction 

*/

/*

only 1 transaction?? 
p = [1, 5 , 7 , 2 , 3, 3, 6]

1 7 = max profit = 7

If I purchase a stock, I find a higher price on the next day, accumulate profit-, keep moving to the next element, its greater, update the profit. 
1, 5 -> 4 => 

p = [1,2,3,4,5,6,7]
start_ptr = 1 max profit 2, 3, max profit.
p = [1,2,3,1,7] => [1, ...] = max_profit_2 => compare the starting element with the current element. if the current element is the same as the starting element, we dont't updat eht eprofit, we continue untill it reaches 7

p = [3,4,5,1] => compare the max_profit = 2. reset the start pointer.m
p = [3,4,5,1,7] => updating the max profit

p = [5,3,4,1] => 3 => max profitl

p = [5,4,3,2]=> profit, each time , we are updating the start pointer




choosing a single day to buy a stock , antoerh day to sell the stock. We can hold the stock. 

Pseudo Algorithm
1. set currlement = first element. 
2. Iterate
3. Compare ith element with curr element
  1. if ith element >= curr element, update max_profit = max(max_profit, (ith_element - curr element))
  2. if ith element < curr element, curr element = ith element; 

*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <string_view>
#include <cassert>

using namespace std;

void printVector(const string_view& text, const std::vector<int>& vec) {
  std::cout << text << " : ";
  for (auto& value : vec) {
    std::cout << value << " ";
  }
  std::cout << "\n" << std::endl;
}


int findMaxProfit(const vector<int>& profits) {
  auto it = profits.cbegin();
  int maxProfit = 0;
  // O(N)
  for (auto it_i = profits.cbegin(); it_i != profits.cend(); it_i++) {
    if (*(it_i) >= (*it)) maxProfit = max( *(it_i) - *(it), maxProfit);
    else it = it_i;
  }
  return maxProfit;
}

void test_case(const std::vector<int>& profits, int trueProfit) {
  int maxProfit = findMaxProfit(profits);
  printVector("Vec", profits);
  std::cout << "Max Profit : " << maxProfit << std::endl;
  assert(maxProfit == trueProfit);
}

int main(int argc, char** argv) {
  std::vector<int> profits{1,2,3,4,5,6,7};
  test_case(profits, 6);
  
  profits = std::vector<int>{1,2,3,1,7};
  test_case(profits,6);
  profits = std::vector<int>{3,4,5,1};
  test_case(profits,2);
  profits = std::vector<int>{5,4,3,2};
  test_case(profits,0);
}

// Linear time O(N) - O(logN)
