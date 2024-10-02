/* Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.


(0,0) -> (n-1, n-1)

neighbors  (i,j) - (i-1,j) (i+1,j), (i, j-1), (i, j+1), (i+1,j+1), (i+1,j-1), (i-1, j-1), (i-1),(j+1)

startings- all ones?? 

BFS
0, 0, 1, 1
1, 0, 0, 1
1, 1, 0, 1
1, 1, 0, 0

=> (m-1, n-1) => -1


DFS - O(N^2)
0, 0, 1, 1
1, 0, 0, 1,
1, 1, 0, 1
1, 1, 0, 0

dp[i,j] = 

dp[m-1][n-1] = 0
dp[m-2][n-2] =  



[0, 0, 0, 0]
[1, 1, 1, 1]

*/

#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#include <set>

using namespace std;

typedef pair<int,int> Coords;
typedef vector<vector<int>> Grid2D;
typedef queue<pair<Coords, int>> Queue; // storre Coords, leve


pair<int,int> getSize(const Grid2D& grid) {
  return make_pair(grid.size(), grid[0].size());
}

// to check boundary conditions and its value
bool checkValidity(const Grid2D& grid, const Coords& coords) {
  auto [M,N] = getSize(grid);
  auto [i,j] = coords;
  
  if (i < 0 || i > M-1) return false;
  if (j < 0 || j > N-1) return false;
  if (grid[i][j] == 1) return false;

  return true;
}

vector<Coords> findNeigbhors(const Grid2D& grid, const Coords& coords) {
  auto [i,j] = coords;

  vector<Coords> nCoords;
  
  // (i-1,j) (i+1,j), (i, j-1), (i, j+1), (i+1,j+1), (i+1,j-1), (i-1, j-1), (i-1),(j+1)
  if (checkValidity(grid, make_pair(i-1,j))) nCoords.push_back(make_pair(i-1,j));
  if (checkValidity(grid, make_pair(i+1,j))) nCoords.push_back(make_pair(i+1,j));
  if (checkValidity(grid, make_pair(i,j-1))) nCoords.push_back(make_pair(i,j-1));
  if (checkValidity(grid, make_pair(i,j+1))) nCoords.push_back(make_pair(i,j+1));
  if (checkValidity(grid, make_pair(i+1,j+1))) nCoords.push_back(make_pair(i+1,j+1));
  if (checkValidity(grid, make_pair(i+1,j-1))) nCoords.push_back(make_pair(i+1,j-1));
  if (checkValidity(grid, make_pair(i-1,j-1))) nCoords.push_back(make_pair(i-1,j-1));
  if (checkValidity(grid, make_pair(i-1,j+1))) nCoords.push_back(make_pair(i-1,j+1));


  

  return nCoords;
}

// O(N^2)
int bfsSearch(const Grid2D& grid) {
  auto [M,N] = getSize(grid);
  if (grid[0][0] == 1) return -1;
  if (grid[M-1][N-1] == 1) return -1;

  Queue qu;
  qu.push(make_pair(make_pair(0,0),1));
  set<Coords> visited; 
  visited.insert(make_pair(0,0));

  Coords endCoords = make_pair(M-1, N-1);

  int sDist = -1;
  while(!qu.empty()) {
    auto [currCoords, currLevel] = qu.front();
    qu.pop();
    std::cout << " Curr coords : " << currCoords.first << " , " << currCoords.second << " Level : " << currLevel << std::endl;
    
    if (currCoords == endCoords) {
      sDist = currLevel;
      break;
    }
    
    for(auto& nCoords : findNeigbhors(grid, currCoords)) {
      // if not found
      std::cout << " N coords : " << nCoords.first << " , " << nCoords.second;
      if (visited.find(nCoords) == visited.end()) {
        std::cout << " Not visited N coords : " << nCoords.first << " , " << nCoords.second << std::endl;
         qu.push(make_pair(nCoords,currLevel+1));
         visited.insert(nCoords);
      }
    }
  }
  return sDist;
}

int main(int argc, char** argv) {

Grid2D grid{
  {0,0,0},
  {1,1,0},
  {1,1,0}
};

int sDist = bfsSearch(grid);
std::cout << "bfs Search : " << sDist << std::endl;

}
/* Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
The length of a clear path is the number of visited cells of this path.


(0,0) -> (n-1, n-1)

neighbors  (i,j) - (i-1,j) (i+1,j), (i, j-1), (i, j+1), (i+1,j+1), (i+1,j-1), (i-1, j-1), (i-1),(j+1)

startings- all ones?? 

BFS
0, 0, 1, 1
1, 0, 0, 1
1, 1, 0, 1
1, 1, 0, 0

=> (m-1, n-1) => -1


DFS - O(N^2)
0, 0, 1, 1
1, 0, 0, 1,
1, 1, 0, 1
1, 1, 0, 0

dp[i,j] = 

dp[m-1][n-1] = 0
dp[m-2][n-2] =  



[0, 0, 0, 0]
[1, 1, 1, 1]

*/

#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#include <set>

using namespace std;

typedef pair<int,int> Coords;
typedef vector<vector<int>> Grid2D;
typedef queue<pair<Coords, int>> Queue; // storre Coords, leve


pair<int,int> getSize(const Grid2D& grid) {
  return make_pair(grid.size(), grid[0].size());
}

// to check boundary conditions and its value
bool checkValidity(const Grid2D& grid, const Coords& coords) {
  auto [M,N] = getSize(grid);
  auto [i,j] = coords;
  
  if (i < 0 || i > M-1) return false;
  if (j < 0 || j > N-1) return false;
  if (grid[i][j] == 1) return false;

  return true;
}

vector<Coords> findNeigbhors(const Grid2D& grid, const Coords& coords) {
  auto [i,j] = coords;

  vector<Coords> nCoords;
  
  // (i-1,j) (i+1,j), (i, j-1), (i, j+1), (i+1,j+1), (i+1,j-1), (i-1, j-1), (i-1),(j+1)
  if (checkValidity(grid, make_pair(i-1,j))) nCoords.push_back(make_pair(i-1,j));
  if (checkValidity(grid, make_pair(i+1,j))) nCoords.push_back(make_pair(i+1,j));
  if (checkValidity(grid, make_pair(i,j-1))) nCoords.push_back(make_pair(i,j-1));
  if (checkValidity(grid, make_pair(i,j+1))) nCoords.push_back(make_pair(i,j+1));
  if (checkValidity(grid, make_pair(i+1,j+1))) nCoords.push_back(make_pair(i+1,j+1));
  if (checkValidity(grid, make_pair(i+1,j-1))) nCoords.push_back(make_pair(i+1,j-1));
  if (checkValidity(grid, make_pair(i-1,j-1))) nCoords.push_back(make_pair(i-1,j-1));
  if (checkValidity(grid, make_pair(i-1,j+1))) nCoords.push_back(make_pair(i-1,j+1));


  

  return nCoords;
}

// O(N^2)
int bfsSearch(const Grid2D& grid) {
  auto [M,N] = getSize(grid);
  if (grid[0][0] == 1) return -1;
  if (grid[M-1][N-1] == 1) return -1;

  Queue qu;
  qu.push(make_pair(make_pair(0,0),1));
  set<Coords> visited; 
  visited.insert(make_pair(0,0));

  Coords endCoords = make_pair(M-1, N-1);

  int sDist = -1;
  while(!qu.empty()) {
    auto [currCoords, currLevel] = qu.front();
    qu.pop();
    std::cout << " Curr coords : " << currCoords.first << " , " << currCoords.second << " Level : " << currLevel << std::endl;
    
    if (currCoords == endCoords) {
      sDist = currLevel;
      break;
    }
    
    for(auto& nCoords : findNeigbhors(grid, currCoords)) {
      // if not found
      std::cout << " N coords : " << nCoords.first << " , " << nCoords.second;
      if (visited.find(nCoords) == visited.end()) {
        std::cout << " Not visited N coords : " << nCoords.first << " , " << nCoords.second << std::endl;
         qu.push(make_pair(nCoords,currLevel+1));
         visited.insert(nCoords);
      }
    }
  }
  return sDist;
}

int main(int argc, char** argv) {

Grid2D grid{
  {0,0,0},
  {1,1,0},
  {1,1,0}
};

int sDist = bfsSearch(grid);
std::cout << "bfs Search : " << sDist << std::endl;

}
