/*


Given two sparse vectors, compute their dot product.

Implement class SparseVector:

SparseVector(nums) Initializes the object with the vector nums
dotProduct(vec) Compute the dot product between the instance of SparseVector and vec

Sparse - [1,0,0,0,3,0,0,4] - 1D
        [0,0,0,4,0,3,0,0] - 1D
n = 8 

check if both elements are non-zero, only then do the muliplication and summation operation. Otherwise skip.

SparseVector(nums)
-> no storing without zeros
-> map -> (index ->val) - if its non zero
-> lengthOfVector - 

dotProduct (nums2):
  SparseVector nums1;

  nums1.length == num2.lendth ->  -1

  dot_val = 0;
  for(auto& pair : nums1)) {
    nums2.find(pair.first) != nums_2
    dot_val += <>gdgf
  }

*/

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

// N - array length, M - nonzero elements 
// Space complexity - O(M)
// Time complexity - 
class SparseVector{
  protected:
    map<int, int> mElements;
    int mLength;

  public:
    SparseVector(const vector<int>& nums) {
      for(int index = 0 ; index < nums.size() ; index ++) {
        if(nums[index] != 0) {
          mElements.insert(make_pair(index, nums[index]));
        }
      }
      mLength = nums.size();
    }

    int length() {
      return mLength;
    }

    int getValue(int index) {
      auto it = this->mElements.find(index);
      if (it != this->mElements.end()) {
        return it->second;
      } else return 0;
    }

    int dotProduct(SparseVector& vec2) {
      assert (vec2.length() == this->length());
      if (vec2.length() != this->length()) {
        return -1;
      }
      
      int dotPValue = 0;
      for(auto& pp : this->mElements) { //O(M)
        int index = pp.first;
        int val = vec2.getValue(index); //O(1)
        if (val != 0) {
          dotPValue += (val * pp.second); //O(M)
        }
      }
      return dotPValue;
    }
};


// To execute C++, please define "int main()"
int main() {
  SparseVector vec1(vector<int>{1,0,0,0,3,4,0,4});
  SparseVector vec2(vector<int>{0,0,0,1,3,3,0});

  int dotValue = vec1.dotProduct(vec2);

  std::cout << "Dot Value : " << dotValue << std::endl;
}
