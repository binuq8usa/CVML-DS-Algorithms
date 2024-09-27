/*

Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.


row - 9 numbers - see if they repeat
col - 9 numbers - see if they repeat

O(N^2) operations + O(n^2) operations + 3 x 3 (divide frid into 3 x 3 bocks
- from each block, extract 9 lements, check repeatability) + O(N^2)


O(n^2) operations

row - 9 

15 mins over. 

Eg:
{1,0,0,2,0,0,4,0,0},
{2,0,0,3,0,0,5,0,0},
{3,0,0,4,0,0,6,0,0},
{4,0,0,5,0,0,7,0,0},
{5,0,0,6,0,0,8,0,0},
{6,0,0,7,0,0,9,0,0},
{7,0,0,8,0,0,1,0,0},
{8,0,0,9,0,0,2,0,0},
{9,0,0,1,0,0,3,0,0}




Better solution from leetcode


class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<char> rows[9];
        unordered_set<char> cols[9];
        unordered_set<char> boxes[9];

        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] == '.') {
                    continue;
                }

                char value = board[r][c];
                int boxIndex = (r / 3) * 3 + (c / 3);

                if (rows[r].count(value) || cols[c].count(value) || boxes[boxIndex].count(value)) {
                    return false;
                }

                rows[r].insert(value);
                cols[c].insert(value);
                boxes[boxIndex].insert(value);
            }
        }

        return true;        
    }
};

*/

#include <cstddef>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <cassert>

using namespace std;

typedef vector<vector<int>> Array2D;

// N=9
// O(N)
bool isRepeating(const vector<int>& nums){
  set<int> alreadySeen;
  bool isValid= true;
  for(auto& num: nums) {
    if (num == 0) continue;
    if (alreadySeen.find(num) != alreadySeen.end()) {
      isValid = false;
      break;
    }
    alreadySeen.insert(num);
  }
  return isValid;
}

// O(N)
bool checkEveryRow(const Array2D& grid){
  bool isValid = true;
  for (auto &row : grid ){ //O(N)
    if(!isRepeating(row)) { // O(N)
      isValid = false;
      break;
    }
  }
  return isValid;
}

// O(N2)
bool checkEveryCol(const Array2D& grid){
  int m = grid.size();
  int n = grid[0].size();
  bool isValid = true;
  for (int j = 0 ; j < n ; j++) {
    vector<int> col;
    for (int i = 0 ; i < m ; i++) {
      col.emplace_back(grid[i][j]);
    }
    if (!isRepeating(col)) { 
      isValid = false;
      break;
    }
  } 
  return isValid;
}

// O(N^2) - 
bool checkBlocks(const Array2D& grid) {
  size_t rows = grid.size();
  size_t cols = grid[0].size();
  int blockSize = sqrt(rows); // 3
  bool isValid = true;

  for (size_t i = 0 ; i < rows; i = i + blockSize) {
    for (size_t j = 0 ; j < cols ; j = j + blockSize) {
      vector<int> nums;
      for(size_t blockRow = i; blockRow < i+blockSize; blockRow++) {
        for(size_t blockCol = j; blockCol < j + blockSize; blockCol++) {
          nums.push_back(grid[blockRow][blockCol]);
        }
      }
      if (!isRepeating(nums)) {
        isValid = false;
        break;
      }
    }
    if (!isValid) break;
  }
  return isValid;
}

// 3 O(N2) ; space complexity - O(N)
bool validSudoku(const Array2D& grid) {
  assert (grid.size() == grid[0].size());
  if (!checkEveryRow(grid)) return false;
  std::cout << "Row Cleared" << std::endl;
  if (!checkEveryCol(grid)) return false;
  std::cout << "Col Cleared" << std::endl;
  if (!checkBlocks(grid)) return false;
  std::cout << "Block Cleared " << std::endl;
  return true;
}

// To execute C++, please define "int main()"
int main() {
  Array2D puzzle{ 
{1,0,0,2,0,0,4,0,0},
{2,0,0,3,0,0,5,0,0},
{3,0,0,4,0,0,6,0,0},
{4,0,0,5,0,0,7,0,0},
{5,0,0,6,0,0,8,0,0},
{6,0,0,2,0,0,9,0,0},
{7,0,0,8,0,0,1,0,0},
{8,0,0,9,0,0,2,0,0},
{9,0,0,1,0,0,3,0,0}
};
bool valid = validSudoku(puzzle);
std::cout << "Is Valid : " << valid << std::endl;

}