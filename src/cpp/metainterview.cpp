// Your previous Plain Text content is preserved below:

// Welcome to Meta!

// This is just a simple shared plaintext pad, with no execution capabilities.

// When you know what language you would like to use for your interview,
// simply choose it from the dropdown in the left bar.

// Enjoy your interview!


/**
design an efficient algorithm to do dot product of two sparse vectors

dot product
vec(a)
vec(b) 

numbers are floating point

vectors 

*/



#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class SparseVector{
public:
  int length;
  //map<int,float> elements; // (index, val)

  // non-zero values, non-zero index
  vector<int> indices; // indices are in sorted order. 
  vector<int> values; // 

  SparseVector(vector<float>& refNum) {

  }

  // Run Time O(N)
  bool dotProduct(const SparseVector& num, float*& dotVal) {
    dotVal = 0;
    // for(auto& pp : elements) { // L =non zero O(L)
    //   int index = pp.first;
    //   if (num[index] != 0) {
    //     dotVal += num[index] * pp.second;
    //   }
    // }
    if (this->length != num.length) {
      return false;
    }
    for(auto& refPP : this->elements) { // O(L)
      int refIndex = refPP.first;
      // 
      if (num.elements.find(refIndex) != num.elements.end()) { //O(1) 
        dotVal += refPP.second * num.elements[refIndex];
      }

      return true;
    }

    return dotVal;
  }

  bool dotProduct2(const SparseVector& num, float*& dotVal) {
    dotVal = 0;
    // for(auto& pp : elements) { // L =non zero O(L)
    //   int index = pp.first;
    //   if (num[index] != 0) {
    //     dotVal += num[index] * pp.second;
    //   }
    // }
    if (this->length != num.length) {
      return false;
    }

    int prevJ = 0;
    for(int i = 0; i < this->indices.size(); i++) { // 2 // 4 //O(N)
      int refIndex = this>indices[i];
      for(int j = prevJ; j < nums.indices.size(); j++) { // 3 //4 
        int index = nums.indices[j];
        if (refIndex == index) {
          dotVal += this->values[refIndex] * num.values[index];
          prevJ=j;
          break;
        } else if (index > refIndex) {
          prevJ = j - 1;
          break;
        }
      }
    }
  }
}
// 

// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const char* const& word : words) {
    cout << word;
  }
  return 0;
}


/***
suppose you have a vector of non-negative integers, and I want to return whether there is a consecutive subvector from the input vector, such that its sum is equal to a predefined number.
// any order
// [3, 7, 2, 5,1].  => 6.  => True/False 

// 3,   3 < pore : 3 + 6,  7    2 

*/


// O(N) 
bool isSubvector(const vector<int>& nums, int target) {
  if(nums.size() == 0) {
    return false;
  }
  int accSum = -1; // 3 //7 
  for (int i = 0; i < nums.size(); i++) {
    if (accSum == -1) {
      accSum = nums[i];  //3 //7 // => 2. //5
    }
    else {
      accSum += nums[i]; //10  //7.  //6
    }
    if (accSum == target) return true;
    else if (accSum > target) {
      accSum = -1; 
      continue;
    } 
  }
  return false;
}