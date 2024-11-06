/*
You are given an m x n integer array grid where grid[i][j] could be:

1 representing the starting square. There is exactly one starting square.
2 representing the ending square. There is exactly one ending square.
0 representing empty squares we can walk over.
-1 representing obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.


1  0  0  0
0  0  0  0
0  0  2 -1

startIndex
EndIndex 

dfs
VisitedSet

// O(N^2)
EmptyIndicesSet 


*/

#include <cmath>
#include <cstdio>
#include <variant>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
#include <set>

using namespace std;

typedef vector<vector<int>> Grid2D;
typedef pair<int,int> Coords;

tuple<int,int> getSize(const Grid2D& grid) {
    if (grid.size() > 0) {
        return make_tuple(grid.size(), grid[0].size());
    } else {
        return make_tuple(-1,-1);
    }
}

// returns startIndex, endIndex, number of empty slots
tuple<Coords, Coords, int> getMetaData(const Grid2D& grid) {
    auto [gRows, gCols] = getSize(grid);        
    int numEmptySpaces = 0;
    Coords startIndex = make_pair(-1,-1);
    Coords endIndex = startIndex;
    for (int row = 0; row < gRows ; row++) {
        for (int col = 0; col < gCols ; col++) {
            if (grid[row][col] == 0) numEmptySpaces++;
            else if (grid[row][col] == 1) startIndex = make_pair(row,col);
            else if (grid[row][col] == 2) endIndex = make_pair(row,col);
        }
    }
    return make_tuple(startIndex, endIndex, numEmptySpaces);
}

bool isValid(const Coords& index, const Grid2D& grid) {
    auto [gRows, gCols] = getSize(grid);
    auto [i,j] = index;
    return (i >= 0 && i < gRows && j >= 0 && j < gCols && grid[i][j] != -1);
}

vector<Coords> getNeigbhors(const Grid2D& grid, const Coords& index){
    auto [i,j] = index;
    vector<Coords> pNeighbors{{i-1,j},{i+1,j},{i,j-1},{i,j+1}};
    
    vector<Coords> neighbors;
    for (auto& nCoords : pNeighbors) {
        if (isValid(nCoords,grid)) neighbors.push_back(nCoords);        
    }
    
    return neighbors;
}


int dfs(const Grid2D& grid, const Coords& index, const Coords& endIndex, set<Coords>& visited, int numEmptySpaces) {
    visited.insert(index);
    
    if (index == endIndex) {
        visited.erase(index);
        return (numEmptySpaces == 0); 
    }
    
    int numPaths = 0;
    for(auto& nCoords : getNeigbhors(grid, index)) {
        if (visited.find(nCoords) == visited.end()) {
            numPaths += dfs(grid, nCoords, endIndex, visited, numEmptySpaces-1);
        } // if not found
    }
    
    // backtracking ,
    visited.erase(index);
    return numPaths;
}

int findUniquePaths(const Grid2D& grid) {        
    auto [gRows, gCols] = getSize(grid);
    if (gRows == -1) return 0;
    
    auto [startIndex, endIndex, numEmptySpaces] = getMetaData(grid);
    
    set<Coords> visited;
    
    // +1 to offset of startIndex
    return dfs(grid, startIndex, endIndex, visited, numEmptySpaces+1);
}

int main() {

    // Grid2D grid{
    //     {1,0,0,0},
    //     {0,0,0,0},
    //     {0,0,0,2}
    //     };
    
    Grid2D grid{
        {0,1},
        {2,0},
        };
    

    int numPaths = findUniquePaths(grid);
    std::cout << "Find unoique paths : " << numPaths << std::endl;
    
}
