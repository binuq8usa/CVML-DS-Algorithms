
/* !!! This question took 60 mins to complete !!!
You are given the root of a binary tree containing digits from 0 to 9 only.

Each root-to-leaf path in the tree represents a number.

For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
Return the total sum of all root-to-leaf numbers. 

A leaf node is a node with no children.

    1.  => recursion = 0
  2   3.  => recursion_

    1
  2

  12

1*10 + 2 

  12 + 13 = 25 => 2 + 10 * 1 + 3 + 10*1


    1
  2   3
        5

1 => rec_level = 0

2rec_level = 1

3rec_level = 0

4rec_level = 0

  12 + 135 = 147. = 10* 1 +2 + 10^2 + 3 * 10 + 5 * 10^0

Algoritmn
recursion_levels = 3
1. Level order traversal, recursion_leve = 0 
2. if node is not leaf
  Recursve on node->left, 
  
  sum += 10^(depth) * node->val + traverse(node->left, depth = depth+1)
  sum += 10 * node->val + traverse(node->right, depth = depth + 1)
  sum = 0.0
  if node is leaf, 
    depth = 0
  f(recursion_level) = 0
    return (node->val, 0);


Algorihtm
1. total_sum = 0
2. if node is not present:
    total_sum = 0
3. if node is leaf:
      total_sum += node->val + acc_sum
4/ if node->left is present
      recursve(node->left, acc_sum = 10 * node->val)
   if node->right is present,
      recursse(node->right, acc_sum = 10 * node->val)
*/

#include <iostream>
using namespace std;

struct Node{
  Node* left;
  Node* right;
  int val;
};
/*
    1
  2  3
 4 5 7 8 O(logN)
 
        1
      2
    3
  4
5

 O(N) 
 O(N)
  [log2(N)]
*/
// O( Log2(N-1) + 1
void traverseNode(const Node* node, const int accSum, int& totalSum) {
  int currVal = node->val + accSum; // 10 + 3 = 13 // 130 +5 O(1)
  if (node->left ==null && node->right == null) { 
    totalSum += currVal; //2 + 10 = 12
    return; 
  } 
  currVal *= 10;
  if (node->left != null) { // 
    traverseNode(node->left, currVal, totalSum); 
  } 
  if (node->right != null) {
    traverseNode(node->right, currVal, totalSum);
  }
}

int computeSum(Node* root) {
  int totalSum = 0;
  if (root == null) return 0;
  int accSum = 0;
  traverseNode(root, accSum, totalSum); // 1 
  return totalSum;
}
    
// To execute C++, please define "int main()"
int main() {

}


/*
https://leetcode.com/problems/find-k-closest-elements/
Given a sorted integer array arr, 
two integers k and x, return the k closest integers to x in the array. 
The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 

Example 1:
Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]

Example 2:
Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]

*/