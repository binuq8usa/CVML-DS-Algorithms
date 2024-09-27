/*

You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle). You can move up, down, left, or right from and to an empty cell in one step.

Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.

*/
/*

m x n grid
(0,0) - find the shortest path to (m-1,n-1) - some nodes that will be blocked in its neighbors
1 - 
k tries to do. 
k=2
(0,0) -> (1,0) = 0,(0,1) = 1 , 
(0,1) =0 k=1, 

(1,0);k=2, layer= => 
(0,1);k=1, layer= => 

(m-1,n-1), layer => number of steps

(i,j) -> (i-1,j), (i+1,j), (i,j-1), (i,j+1) => (ii,jj)
validity - (i-1 >= 0) && (i+1 < M) && j-1 >= 0 && j+1 < N && 
(ii >=0 and ii < M && jj >=0 && jj < N))

valid if grid[ii][jj] = 0 or (grid[ii][jj] == 1 && K >= 1)


*/

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <queue>
#include <tuple>

using namespace std;

typedef vector<vector<int>> Grid2D;
typedef pair<int,int> Coords;
typedef tuple<Coords, int> State;
typedef queue<pair<int, State>> Queue; // store layer  and State -containing Coords and k

vector<Coords> findValidNeighbors(const Grid2D& grid, Coords node) {
  int i = node.first;
  int j = node.second;
  int M = grid.size();
  int N = grid[0].size();

  vector<Coords> neighbors;
  if (i-1 >= 0) neighbors.push_back(make_pair(i-1,j));
  if (i+1 < M)  neighbors.push_back(make_pair(i+1,j));
  if (j-1 >= 0) neighbors.push_back(make_pair(i,j-1));
  if (j+1 < N) neighbors.push_back(make_pair(i,j+1));

  return neighbors;
} 

int findShortestPath(const Grid2D& grid, int K) {
  Coords startNode = make_pair(0,0);
  set<State> alreadyVisited;
  int M = grid.size();
  int N = grid[0].size();

  // if we had sufficient K to eliminate all obstables
  // it will be the manhattan distance
  if (K >= (M+N-2)) return M+N-2;

  Queue qu;
  State state = make_tuple(startNode, K);
  qu.push(make_pair(0, state));
  alreadyVisited.insert(state);

  int sDist = -1;
  while(!qu.empty()) {
    auto [layer, currState] = qu.front();
    auto [currNode, nK] = currState;
    qu.pop();
    if (currNode == make_pair(M-1, N-1)) {
      sDist = layer;
      break;
    }
    
    // find neighbors
    for(auto& nNode : findValidNeighbors(grid, currNode)) {
      int gridVal = grid[nNode.first][nNode.second];
      int newK = (gridVal == 1) ? nK-1: nK;
      State newState = make_tuple(nNode, newK);
      if(newK >= 0 && alreadyVisited.find(newState) == alreadyVisited.end()) {
        // to add to qu, check if its zero or 1 
        alreadyVisited.insert(newState);
        qu.push(make_pair(layer+1, newState));
      }
    }
  }

  return sDist;
}

/*
k=0
x1 x1
x1 x2
x2 x3
x3 x4
x4 x5
1  x6
x8  x7
x9  1
x10  1
x11  1
  0
1  0
1  0
0  0

*/

// To execute C++, please define "int main()"
int main() {
  // Grid2D grid{{0,0,0},{1,1,0},{0,0,0},{0,1,1},{0,0,0}};
  Grid2D grid{{0,0},{1,0},{1,0},{1,0},{1,0},{1,0},{0,0},{0,1},{0,1},{0,1},{0,0},{1,0},{1,0},{0,0}};
  int k = 4;

  int sDist = findShortestPath(grid, k);
  std::cout << "SDist : " << sDist << std::endl;
}
