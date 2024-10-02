/*
In this problem setup, an SMS can only be received/transmitted by a service
tower from/to a phone or another service tower located in its vicinity (left,
right, up, and down). For example:

There is a field of size `rows` x `cols` and it is initially empty. The
connectivity infrastructure team (CIT) is building service towers so that people
can communicate without crossing the field. They build these towers at a rate of
1 per day.

(M, N)
         cols
        +--------+
        |  +     |
        |     +++|
   rows |  ++++  |
        |+++     |
        |      + |
        +--------+


We are unaware of how and where the CIT is building these towers, but we must
let them know when the left side is connected to the right side so that they
stop building towers that are unnecessary.

To simulate the passage of a day and get a new tower, use CIT.NextTower() which
returns an integer point object (r, c) where 0 <= r < rows and 0 <= c < cols.


Example:

CIT.NextTower() returns one per call in {(2, 1), (0, 2), (4, 1), (3, 2), ...}.
The numbers on the grid show what day a tower was built.


grid - M X N
CIT.NextTower() -> 

        +--------+
        |   +    |
        |        |
   rows |   +++++|
        |++++    |
        |        |
        +--------+
Left col -> right clo 
point = row, col => col ===0 or col == N-1
connecticity_of_point = top, left, bottom, right

Single point - > connected
DFS

while (1) {
new_point = CIT.NextTower();

Your_function()

}


*/

#include <iostream>
#include <type_traits>
#include <vector>
#include <set> 
#include <utility>

using namespace std;

typedef vector<vector<int>> Grid2D;
typedef pair<int,int> Coords;
typedef pair<bool,bool> Criteria;

vector<Coords> findValidNeighbors(const Grid2D& grid, const Coords& startCoords) {
  vector<Coords> neighbors;

  // startCoords[i][j] 

}
// first bool - is col == 0, second bool. col == N-1
pair<bool,bool>  dfsSearch(const Grid2D& grid, set<Coords>& alreadyVisited, Coords startCoords) {
  
  alreadyVisited.insert(startCoords);
  int N = grid[0].size();
  Criteria found = make_pair(false, false);
  if (startCoords.second == 0) found.first = true;
  if (startCoords.second == N-1) found.second = true;

  // find neighbors 

  for(auto& nCoords : findValidNeighbors(grid, startCoords)) {
    if (alreadyVisited.find(nCoords) == alreadyVisited.end()) {
      auto ct = dfsSearch(grid, alreadyVisited, nCoords); 
      found.first = found.first || ct.first;
      found.second = found.second || ct.second;
  }

  return found;

}

// grid - already populated piunts froi CIT,NextTower()
bool checkForConnection(const Grid2D& grid) {
  set<Coords> alreadyVisited;
  int M = grid.size();
  int N = grid[0].size();

  bool isThereConnection = false;
  for(int i = 0 ; i < M; i++) {
    for (int j = 0 ; j < N; j++) {
      Coords cr = make_pair(i,j);
      // 
      if (alreadyVisited.find(cr) == alreadyVisited.end()) {
        Criteria ct = dfsSearch(grid, alreadyVisited, cr);
        isThereConnection = isThereConnection || (ct.first && ct.second);
        if (isThereConnection) {
          return true;
        }
      }
    }
  }
  return isThereConnection;
}

int main(int argc, char** argv) {


}
