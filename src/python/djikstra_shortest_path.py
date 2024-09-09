"""
Djistra's algorithm

Maintain two sets
First set- nodes that follow the tree path.Maybe linked list would be an appropriate container
Second set - Heap of the list where the minimum element is extracted. Heap can be list of tuples 
with first element as the weight used as key to get minimal value. 

How to update the weights? 

"""
from typing import List, Tuple
from heapq import heapify, heappop, heappush, heappushpop

class Graph:
    def __init__(self, num_vertices : int) :
        self.num_vertices = num_vertices
        self.adjacent_list = [ [] for _ in range(0, self.num_vertices) ]
    
    def add_edge(self, src_node : int, dest_node : int, weight: int):
        if weight < 0:
            print('invalid edge with negative weight')
        assert 0 <= src_node <= self.num_vertices-1
        assert 0 <= dest_node <= self.num_vertices-1
        self.adjacent_list[src_node].append((dest_node, weight))
        self.adjacent_list[dest_node].append((src_node, weight))

    def shortest_path(self, src_node : int):
        """
        Djisktra's algorithm
        """
        # computing the shortest distance from s to other vertices
        s_dist : List[int] = [float('inf') for _ in range(0, self.num_vertices)]
        s_dist[src_node] = 0

        # we need to maintain two sets. One thats explored, and one thats not explored.
        # maybe create a heap for the s_dist
        unexplored_nodes : List[Tuple[int,int]] = []
        node_path_set = set()

        # use this heap where a computed value is pushed to the heap
        heappush(unexplored_nodes, (0, src_node)) # add the src node

        while bool(unexplored_nodes):
            # pop the heap to get the node with minimum distance to s
            node_dist, node = heappop(unexplored_nodes)
            if node not in node_path_set:
                node_path_set.add(node)
            else: # node was already removed which are lower value
                continue

            # wont unnecssary run these iterations
            # recomputing the distance of the node neighhors after node got removed from heap
            for n_node, weight in self.adjacent_list[node]:
                # this is the first round where n_node can be reached from other nodes
                # if there is a shortest distance to n_node through node 
                if s_dist[n_node] > s_dist[node] + weight:
                    s_dist[n_node] = s_dist[node] + weight
                    # would add duplicate entry with n_node if there was a smaller node distance
                    heappush(unexplored_nodes, (s_dist[n_node], n_node))
        
        return s_dist, node_path_set

if __name__=="__main__":
    num_vertices = 9
    g = Graph(num_vertices)

    # making above shown graph
    g.add_edge(0, 1, 4)
    g.add_edge(0, 7, 8)
    g.add_edge(1, 2, 8)
    g.add_edge(1, 7, 11)
    g.add_edge(2, 3, 7)
    g.add_edge(2, 8, 2)
    g.add_edge(2, 5, 4)
    g.add_edge(3, 4, 9)
    g.add_edge(3, 5, 14)
    g.add_edge(4, 5, 10)
    g.add_edge(5, 6, 2)
    g.add_edge(6, 7, 1)
    g.add_edge(6, 8, 6)
    g.add_edge(7, 8, 7)
    print(g.shortest_path(0))



