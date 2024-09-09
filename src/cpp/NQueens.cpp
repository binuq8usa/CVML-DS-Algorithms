/*
Placing N queens in N x N grid. 

*/

#include <iostream>
#include <vector>
#include <cassert>
#include <string_view>
using namespace std;

typedef vector<vector<int>> Array2D;

void print(string_view text, const Array2D& grid) {
  std::cout << text << ":\n";
  for(auto& row : grid) {
    for(auto& val : row) {
      std::cout << val << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

bool IsSafe(const Array2D& grid, int row, int col, int N) {
  // check if the elements in the same column have 1
  for(int i = 0; i < row; i++) {
    if (grid[i][col] == 1) {
      return false;
    }
  }
  for(int i = row, j = col; i>=0 && j >= 0; i--,j--) {
    if (grid[i][j] == 1) return false;
  }
  for(int i = row, j = col; i>= 0 && j < N ; i--, j++) {
    if (grid[i][j] == 1) return false;
  }
  return true;
}

int PlaceNQueens(Array2D& grid, int row, int N) {
  assert(grid.size() == N and grid[0].size() == N);
  // std::cout << "Row number : " << row << endl;
  if (row == N) {
    print("Solution", grid);
    return 1;
  }

  // iterate across columns
  int solutions = 0;
  for(int col = 0; col < N; col++) {
    // check if this location is valid and not crossed by existing queens placed
    // std::cout << "Row number : " << row << endl;
    // std::cout << "Col : " << col << std::endl;
    if (IsSafe(grid, row, col, N)) {
      // set the grid to queen 
      grid[row][col] = 1;
      // print("Intermediate", grid);

      // move onto to the next row
      // if (PlaceNQueens(grid, row+1, N )) return true;
      solutions += (PlaceNQueens(grid, row+1, N ));

      grid[row][col] = 0; // set it to zero to backtrack
    }
    // } else {
    //   std::cout << "Not stage at " << row << "," << col << std::endl;
    // }
  }
  return solutions;
} 

// To execute C++, please define "int main()"
int main() {
  int N = 4;
  Array2D grid(N,vector<int>(N,0));
  int num_solutions = 0; 
  num_solutions = PlaceNQueens(grid, 0, N);
  // else std::cout << "Not valid" << std::endl;
  // for(int row = 0; row < N ; row++) {
  //   if(PlaceNQueens(grid, row, N)) {
  //     print("NQueens", grid);
  //     num_solutions++;
  //   }
  //   // initialize the grid
  //   grid = Array2D(N,vector<int>(N,0));
  // }
  std::cout << "Number of solutions : " << num_solutions << std::endl;
}
