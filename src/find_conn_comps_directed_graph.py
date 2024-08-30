# Impplement Kosaraju's algorithm to find the strongly connected components
from sys import _current_frames
from typing import List, Deque, Tuple
from collections import deque

AdjacencyList = List[List[int]]

class Graph:
    def __init__(self, adjacency_list) -> None:
        self.adjaceny_list : AdjacencyList = adjacency_list
        self.current_leader_node = None
        self.leader_nodes : List = [None for i in range(0, len(self.adjaceny_list))] 
        self.finishing_time : List[Tuple] = [ (i,i+1) for i in range(0, len(self.adjaceny_list)) ]
        self.is_explored : List[bool] = [False for i in range(0, len(self.adjaceny_list))]

    def reverse_graph(self) -> AdjacencyList:
        rev_adj_list = [ [] for i in range(len(self.adjaceny_list)) ]
        for node, neighors in enumerate(self.adjaceny_list):
            for n_node in neighors:
                rev_adj_list[n_node].append(node)
        return rev_adj_list

    def dfs(self, node, adjacency_list):
        # use the finishing time
        stack : Deque = deque()
        stack.append(node)
        fin_time = 0

        while bool(stack):
            curr_node = stack[-1]

            # if there are no neighnhor nodes or all are explored
            if not adjacency_list[curr_node] or all( [ self.is_explored[n_node] for n_node in adjacency_list [curr_node] ] ):
                fin_time += 1
                self.finishing_time[curr_node] = (curr_node, fin_time)
                stack.pop()
                continue

            # iterate through neigbhors
            for n_node in adjacency_list[curr_node]:
                if not self.is_explored[n_node]:
                    self.is_explored[n_node] = True
                    self.leader_nodes[n_node] = node # set the leader node for the neighbhor
                    stack.append(n_node)
            


    def traverse_graph(self, adjacency_list):

        node_ordering = sorted(self.finishing_time, reverse=True, key= lambda x : x[1])
        print(node_ordering)
        for node, node_priority in node_ordering:
            if not self.is_explored[node]:
                self.is_explored[node] = True
                self.leader_nodes[node] = node # setting the leader node
                self.dfs(node, adjacency_list)
        
        print(f'Finishing time : {self.finishing_time}')

    def find_sccs(self):
        """
        graph -> adjacency list -> containing single entry containing neighor

        #1. reverse the adjaceny list
        #2. Use DFS to compute the ordering on reversed adjaceny list
        #3. Use the new ordering to compute DFS to get components 

        """ 

        rev_adj_list = self.reverse_graph()

        # loop one on dfs of  - to update finishing time
        self.traverse_graph(rev_adj_list)

        # reset explored
        self.is_explored = [False for i in range(0, len(self.adjaceny_list))]

        # loop two on dfs to get leader node    
        self.traverse_graph(self.adjaceny_list)

        return set(self.leader_nodes)


def test_rev_graph():
    adj_list = [[2,3],
    [0],
    [1],[4],[]
    ]

    graph : Graph = Graph(adjacency_list=adj_list)
    
    rev_adj_list = graph.reverse_graph()

    print(rev_adj_list) 

def test_algo():
    adj_list = [[2,3],
    [0],
    [1],[4],[]
    ]

    graph : Graph = Graph(adjacency_list=adj_list)
    print(graph.find_sccs())

test_algo()
