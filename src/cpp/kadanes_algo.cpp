/*
Given an integer array nums, find the 
subarray
 with the largest sum, and return its sum.

arr = [-2,1,-3,4,-1,2,1,-5,4]

*/


#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int computeLargestSum(const vector<int>& arr) {
    int lSum = numeric_limits<int>::min();
    int currentVal =arr[0];
    for(auto it = arr.begin()+1; it!= arr.end() ; it++) {
        currentVal = max((*it), (*it) + currentVal); 
        lSum = max(lSum, currentVal);
    }   
    return lSum; 
}

// To execute C++, please define "int main()"
int main() {
  std::vector<int> arr{-2,1,-3,4,-1,2,1,-5,4};
  int lSum = computeLargestSum(arr);
  std::cout << "LSum : " << lSum << std::endl;
}
