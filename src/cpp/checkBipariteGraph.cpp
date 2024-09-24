/*

We want to split a group of n people (labeled from 1 to n) into two groups of any size. Each person may dislike some other people, and they should not go into the same group.

Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the person labeled ai does not like the person labeled bi, return true if it is possible to split everyone into two groups in this way.
RED          BLUE
1 ----------> 2



5 ----------> 6

1-----------> 7

8<------------7




1. Check if graph is bipartite
2. 2 - color probelm
  parent node - 1 color - white, 
  child -node - 1 color - black
  BFS search algo to code it up
3. Create the graph, and add the edges
  1.  Adjacency lists and nodes
  2.  nodes are integers or 'string'. 
  3.  How many people are we dealing ? 100 or 1000
4. Have a color Enum  - White or Black
5. BFS Graph Traversal
  -> alreadyVisited Map - node_val -> color
6. BFS
  -> Start with node
  -> check if it was visited -> check parent color, and check the neibhors and see if those were visited

Whats the default color? 
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <utility>
#include <queue>

using namespace std;

enum class NodeColor{
  RED = 0,
  BLUE = 0
};

typedef unordered_map<int, list<int>> AdjacencyList;
typedef unordered_map<int, NodeColor> NodeTraversal;
typedef pair<int,int> Edge;



class Graph{
  size_t mNodes;
  AdjacencyList mAdjLists;

  bool _bfsTraverse(NodeTraversal& alreadyVisited, const size_t& startNode) {
    alreadyVisited.insert(make_pair(startNode, NodeColor::RED));
    queue<size_t> qu;
    qu.push(startNode);

    while (!qu.empty()) {
      size_t currNode = qu.front();
      qu.pop();
      NodeColor currColor = alreadyVisited[currNode];

      for(int node = 0; node < )
    }


  }

  public:
    Graph(size_t nodes) : mNodes(nodes) {
      for(size_t node = 0; node < mNodes; node++) {
        mAdjLists.insert(make_pair(node, list<int>()));
      }
    }

    void addEdge(const Edge& edge) {
      if (mAdjLists.find(edge.first) != mAdjLists.end()) {
        mAdjLists[edge.first].push_back(edge.second);
      } else {
        std::cerr << "Node : " << edge.first << "Not present" << std::endl; 
      }
    }

    /*
    Check if graph is bipartite

    */
    bool isBipartite() {
      NodeTraversal alreadyVisited;
      bool flag = true;

      for(int node = 0; node < mNodes ; node++) {
        if (alreadyVisited.find(node) == alreadyVisited.end()) {
          if( ! _bfsTraverse(alreadyVisited, node) ) {
            flag = false;
            break;
          }
        }

      }
    return flag;
    }
};


// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const char* const& word : words) {
    cout << word;
  }
  return 0;
}
