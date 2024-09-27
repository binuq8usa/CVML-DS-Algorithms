/*


Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e., from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right

root = 
       1    -level 0 - row
    2.   3.  - level 1 -row
  4.  56.  7

4. 2 [1,5,6] 3 7

preorder(node->left, depth+1)


(4,depth+2), (2,depth+1), (5,depth+2),(1, depth+0),(6, depth+2), (3, depth+1), (7, depth+2)


level order traversal - BFS search
vector of vectors.   -               1 - level
                                [2,  ,   3] - level 1 - 2 ^1
                              [4,, [5,6],,7]

    1  - level0.  2^0
  2   3. - level1. 2^1 = 2.  2 +1
4.  56. 7 - level2 2^2 = 4   4 + 2 

1, (row,col) - (0,0)
2, (1,-1) ,  3, (1,1)
4,  (2,-2) , 5(2,0),6(2, 0), 7(2,1)

Algorithm
1. Do BFS, and embed coordinates in a queue, keep track of the most -negative element
2. Pop each element from queue, add the -(-negative  = min coords - 0)
3. Add to list if column is same value, if different, then start another list.


2 1 3

inorder traversal

4 , 2 ,5,1,6, 3, 7

*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <map>
using namespace std;

struct TreeNode{
  TreeNode* left; 
  TreeNode* right;
  int val;

  TreeNode(int val, TreeNode* left, TreeNode* right) : val(val), left(left), right(right) {}
  TreeNode(int val) : val(val), left(NULL), right(NULL) {}
};

vector<vector<int>> verticalTraversal(TreeNode* root) {
  if (root == NULL) return vector<vector<int>>();
  queue<tuple<int, TreeNode*>> qu; // to hold node val, col
  int col = 0;
  qu.push(make_tuple(col, root));
  map<int, vector<int>> traversals;

  while(!qu.empty()) {
    auto tt = qu.front();
    qu.pop();
    auto [newCol, node] = tt;

    // add to heap
    if(traversals.find(newCol) == traversals.end()) {
      traversals.insert(make_pair(newCol, vector<int>(1,node->val)));
    } else{
      traversals[newCol].push_back(node->val);
    }

    if (node->left) {
      qu.push(make_tuple(newCol-1, node->left));
    } 

    if (node->right) {
      qu.push(make_tuple(newCol+1, node->right));
    }
  }
  
  std::vector<vector<int>> ttrs;
  for(auto it = traversals.begin(); it != traversals.end() ; it++) {
    ttrs.push_back(it->second);
  }

  return ttrs;
}

// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const char* const& word : words) {
    cout << word;
  }
  return 0;
}
