/*
Given an m x n integers matrix, return the length of the longest increasing path in matrix.

--> longest increasing path - 1 2 3

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

1 2 3 -> 1 2 3 6 9 = 5
4 5 6 -> 2 3 6 9
9 8 7 -> 2 5 8

0 1 9
4 1 3
13 3 4

0 22 3 4.  => 0,2. => 1,7  => 1,3,4,5,6,7
2 0. 99 1
1. 24. 3. 3 
 7  6   5   4
0 -> 4 -> 13

no negative numbers
- A node should not visited twice
- does it start from (0,0)

9 9 4 
6 6 8
2 1 1

starting position -> higest number --> need to start with the lowest number

Algorthm
1. get indieces in increasing order of the value
2. (0,0,) (0,1) ..... (2,2) -> N2 (log N2)
3. 1 -> 2 or 4 => 1, 4 5,6,9 => 1, 4, 7, 8 ,9 => selecting a path should be integer should be greater than the current value seen. 
  => smallest of the largest value
  1 -> 2-> 3 -> 6 -> 9 
  => ends with if no neighor or no visited neigbhor

4. Repeated scans - do no visit neighbors thats already part of an earlier path
5. Do DFS till all nodes are seen.

4. DFS but with search node 
5. for eahc scan you will retain the longest sequence


1

*/


#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <cassert>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> Grid2D;
typedef pair<int,int> Coords;

vector<Coords> getValidNeighbors(const Grid2D& grid, const Coords& searchIndices) {
  vector<Coords> neighbors;
  int m = grid.size();
  int n = grid[0].size();

  // up
  if (searchIndices.first-1 >= 0) neighbors.push_back(make_pair(searchIndices.first-1, searchIndices.second));

  // down
  if (searchIndices.first+1 < m) neighbors.push_back(make_pair(searchIndices.first+1, searchIndices.second));

  // left
  if (searchIndices.second-1 >= 0) neighbors.push_back(make_pair(searchIndices.first, searchIndices.second-1));

  if (searchIndices.second+1 < n) neighbors.push_back(make_pair(searchIndices.first, searchIndices.second+1));

  return neighbors;
}

int dfs(const Grid2D& grid, const Coords& searchIndices, Grid2D& cache) {
  if (cache[searchIndices.first][searchIndices.second] > 0) return cache[searchIndices.first][searchIndices.second];

  // for each neighbor
  for (auto& indices : getValidNeighbors(grid,searchIndices)) {
    int parentVal = grid[searchIndices.first][searchIndices.second];
    int nVal = grid[indices.first][indices.second];
    if (nVal > parentVal) {
      cache[searchIndices.first][searchIndices.second] = max(cache[searchIndices.first][searchIndices.second], dfs(grid,indices,cache));
    }
  }
  return ++cache[searchIndices.first][searchIndices.second];
}

int findLongestLength(const Grid2D& grid) {
  int m = grid.size();
  int n = grid[0].size();

  // create cache
  Grid2D cache(vector<vector<int>>(m, vector<int>(n,0)));

  int lenLargestSeq = 0.0;
  for(int row = 0 ; row < m ; row++) {
    for(int col = 0 ; col < n ;  col++) {
      lenLargestSeq = max(lenLargestSeq, dfs(grid, make_pair(row,col), cache));
    }
  }
  return lenLargestSeq;
}

// To execute C++, please define "int main()"
int main() {
  // Grid2D grid{
  // {9,9,4},
  // {6,6,8},
  // {2,1,1}
  // };

  Grid2D grid{
    {1}
  };

  int ans = findLongestLength(grid);

  std::cout << "Longest Length : " << ans << std::endl;
}
