// Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

/*
{
{'1','1','1','0','0','1','1','1'}
{'1','1','1','0','0','1','1','1'}
{'0','0','0','0','0','0','0','0'}
{'0','0','0','1','1','1','1','0'}
{'0','0','0','1','1','1','1','0'}
{'0','0','0','1','1','1','1','0'}
{'1','1','0','0','0','0','0','0'}
{'0','0','0','0','0','0','1','1'}
}
Answer : 5

Algo : 
1.DFS
2.Keep Explored 
3. ITerate throught he node
4. set the node as explored, recursive dfs.

*/

#include <vector>
#include <iostream>
#include <set>
#include <utility>

using namespace std;

void print_set(set<pair<int,int>> explored) {
  for (auto& indices : explored){
    std::cout << "Indices : " << indices.first << "," << indices.second << std::endl; 
  }
}

bool check_validity(const std::pair<int, int>& indices, int rows, int cols) {
  return (indices.first >= 0 && indices.first < rows && indices.second >= 0 && indices.second < cols);
}

// 4 connected
std::vector<std::pair<int,int>> find_neigbhors(const vector<vector<char>>& grid, const std::pair<int,int>& indices) {
  int i = indices.first;
  int j = indices.second;
  int rows = grid.size();
  int cols = grid[0].size();

  std::vector<std::pair<int,int>> neigbhors;
  
  if (check_validity(std::make_pair(i+1,j),rows,cols) && grid[i+1][j] == '1') neigbhors.push_back(std::make_pair(i+1,j));
  if (check_validity(std::make_pair(i-1,j),rows,cols) && grid[i-1][j] == '1') neigbhors.push_back(std::make_pair(i-1,j));
  if (check_validity(std::make_pair(i,j+1),rows,cols) && grid[i][j+1] == '1') neigbhors.push_back(std::make_pair(i,j+1));
  if (check_validity(std::make_pair(i,j-1),rows,cols) && grid[i][j-1] == '1') neigbhors.push_back(std::make_pair(i,j-1));

  return neigbhors;
}

bool dfs(const vector<vector<char>>& grid, const std::pair<int,int> indices, std::set<std::pair<int,int>>& explored) {
  // add the explored
  explored.insert(indices);
  std::cout << "Indices : " << indices.first << "," << indices.second << std::endl; 
  std::cout << "Size set : " << explored.size() << std::endl;
  //print_set(explored);
  auto neighbors = find_neigbhors(grid, indices);
  for(auto& n_indices : neighbors) {
    if (explored.find(n_indices) == explored.end()) {
      dfs(grid, n_indices, explored);  
    }
  }
  return true;
}

int get_num_islands(const vector<vector<char>>& grid) {
    std::set<std::pair<int,int>> explored;
    int num_islands = 0;
    for(int i = 0; i < grid.size(); i++) {
      for(int j = 0 ; j < grid[i].size(); j++){
        auto indices = std::make_pair(i,j);
        // if not explored
        if(explored.find(indices) == explored.end() && grid[i][j]=='1') {
          num_islands += int(dfs(grid, indices, explored));
          std::cout << "Number of islands :" << num_islands << std::endl;
        }
      }
    }
    return num_islands;
}


int main() {
  // auto words = {'Hello', 'World', "\n"};
  // for (const char* const& word : words){
  //   cout << word;
  // }
  vector<vector<char>> grid{
    {'1','1','1','0','0','1','1','1'},
    {'1','1','1','0','0','1','1','1'},
    {'0','0','0','0','0','0','0','0'},
    {'0','0','0','1','1','1','1','0'},
    {'0','0','0','1','1','1','1','0'},
    {'0','0','0','1','1','1','1','0'},
    {'1','1','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','1','1'}
    };
  
  int num_islands = get_num_islands(grid);

  std::cout << "Num of islands : " << num_islands << std::endl;
}