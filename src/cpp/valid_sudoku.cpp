/*

Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.


*/

/*

Eg: 0 -> not entered
{2,4,6,0,0,0,0,0,7},
{1,2,3,0,4,6,0,0,0},
{7,8,9,0,0,0,0,0,0},
{0,0,1,0,0,0,0,0,7},
{0,0,4,0,0,0,0,0,7},
{0,0,7,0,4,6,0,0,0},
{7,8,8,0,0,0,0,0,0},
{1,2,2,0,0,0,0,0,0},
{7,8,5,0,0,0,0,0,0}

//Option - brute force
// single element - set across the block, horizontal, vertical - O(N2)  

// Option - divide and conquer
// Divide into 3 x 3 blocks - get a set, as I terate across the block elements, check if it present already. 
// For each block, validate -> <check 3rd rule> - 
// Combine results from each block - compare 3 blocks at one - row wise - (0,0) (0,1) , (0,2) -> 2nd block rows, 3rd block rows
// repeat in column fashion - find common elements between 3 lists at a time. 
*/

#include <iostream>
#include <type_traits>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

typedef vector<vector<int>> Array2D;
const int kBlockSize = 3;

bool ValidateBlock(const Array2D& grid_block) {
  set<int> valueSeen;
  bool isValid = true;
  for(auto& row : grid_block) {
    for(auto& val : row) {
      if (val == 0) continue; // skip
      if (valueSeen.find(val) == valueSeen.end()) valueSeen.insert(val);
      else {
        isValid = false;
        break;
      }
    }
  }
  return isValid;
}

bool ValidateRows(const Array2D& grid) {
  bool isValid = true;
  for(auto& row : grid) {
    set<int> valueSeenPerRow;
    for(auto& val : row) {
      if (val == 0) continue; // skip
      if (valueSeenPerRow.find(val) == valueSeenPerRow.end()) valueSeenPerRow.insert(val);
      else {
        std::cout << "Curr val : " << val;
        isValid = false;
        break;
      }
    }
  }
  return isValid;
}

// NEED OPTIMAL WAY TO ITERATE THROUGH COLS
// https://stackoverflow.com/questions/74224485/is-it-possible-to-iterate-through-a-vector-of-vectors-columnwise
bool ValidateCols(const Array2D& grid) {
  bool isValid = true;
  int rows = grid.size();
  int cols = grid[0].size();
  assert( rows >= 1 and cols >= 1);

  for(int j = 0 ; j < cols; j++) {
    set<int> valueSeenPerCol;
    for(int i = 0; i < rows; i++) {
      int val = grid[i][j];
      if (val == 0) continue; // skip
      if (valueSeenPerCol.find(val) == valueSeenPerCol.end()) valueSeenPerCol.insert(val);
      else {
        isValid = false;
        break;
      }
    }
  }

  return isValid;
}

// NEED BETTER WAY TO DIVIDE THROUGH BLOCKS 
bool ValidateBlockWise(const Array2D& grid, int block_size = kBlockSize) {
  bool isValid = true;
  int rows = grid.size();
  int cols = grid[0].size();
  assert( rows >= 1 and cols >= 1);
  for(int block_i = 0 ;  block_i < rows ; block_i+= block_size) {
    for(int block_j = 0 ; block_j < cols; block_j+= block_size) {
      Array2D block;
      for(int i = block_i; i < block_i + block_size; i++) {
        vector<int> row;
        for(int j = block_j; j < block_j + block_size; j++) {
          row.push_back(grid[i][j]);
        }
        block.push_back(row);
      }
      if (!ValidateBlock(block)) {
        std::cout << "Block_i : " << block_i << " Block_j" << block_j << std::endl;
        isValid = false;
        break;
      }
    }
  }
  return isValid;
}

bool isValidSudoku(const Array2D& grid) {
  if ( !ValidateRows(grid)) {
    std::cout << "Rows invalid" << std::endl;
    return false;
  } else {
    std::cout << " Passed Row CHeck" << std::endl;
  }
  if ( !ValidateCols(grid)) {
    std::cout << "Cols invalid" << std::endl;
    return false;
  } else {
    std::cout << "Passed Col check" << std::endl;
  }
  if ( !ValidateBlockWise(grid)) {
    return false;
  } else {
    std::cout << "Passed Block check" << std::endl;
  }
  return true;
}

// To execute C++, please define "int main()"
int main() {
  Array2D arr{
{5,4,6,0,0,0,0,0,7},
{1,2,3,0,4,6,0,0,0},
{7,8,9,0,0,0,0,0,0},
{0,0,1,0,0,0,0,0,8},
{0,0,4,0,0,0,0,0,9},
{0,0,7,0,1,3,0,0,0},
{4,6,5,0,0,0,0,0,0},
{3,1,2,0,0,0,0,0,0},
{9,7,8,0,0,0,0,0,0}
  };
  bool validCheck = isValidSudoku(arr);
  std::cout << "Valid check :" << validCheck << endl;
}
