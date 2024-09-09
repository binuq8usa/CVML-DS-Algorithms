# set of nodes -> check if it strongly connected and if connected, find the connected components
# set of reachable destinations from a specific base station
# and its all one-way routes, how would go ahead and find the areas that are not reachable.
# Base stations as nodes, and areas to be covered as additonal nodes. If it can be reached between area A and area B, then there is an edge. 
# Reachability constraint between station A and station B is if its distance is less than 10 miles. 

# How to check if the areas are interconnected and its all one-way. And we are assuming one car to be servicing a specific set of areas. How many cars should be deployed? 

# whats the shortest route between area A and area B or between two sets of areas?

# create a graph containing the nodes
from collections import defaultdict, OrderedDict
from typing import Dict, List, Tuple

class Graph:
    def __init__(self, num_nodes = 0) -> None:
        self.num_nodes : int = num_nodes
        self.list_of_nodes : List[str] = [] # ordering
        self.adjacency_list : Dict[str, List[Tuple[str,int]]] = defaultdict(list)
        self.finishing_time : Dict[str, int] = OrderedDict()
        self.node_label : Dict[str, int] = OrderedDict()
        self.fin_time = -1
        self.current_node_label = None

    # @property
    # def num_nodes(self):
    #     return self.__num_nodes

    # @property
    # def list_of_nodes(self):
    #     return self.__list_of_nodes
    
    # @num_nodes.setter # graph.num_nodes = x
    # def num_nodes(self, num_nodes):
    #     self.__num_nodes = num_nodes
    
    def add_edge(self, node_u: str, node_v : str, weight: int = None):
        weight = weight if weight is not None else 1
        self.adjacency_list[node_u].append((node_v, weight))
    
    def populate_graph(self, edges : List[Tuple[str, str, int]]):
        for node_u, node_v, weight in edges:
            self.add_edge(node_u, node_v, weight)
            self.list_of_nodes.append(node_u)
            self.list_of_nodes.append(node_v)
        self.list_of_nodes = sorted(list(set(self.list_of_nodes)))
        print(f'List of nodes : {self.list_of_nodes}')
        self.num_nodes = len(self.list_of_nodes)
        self.finishing_time = OrderedDict.fromkeys(self.list_of_nodes,-1)
        self.node_label = OrderedDict.fromkeys(self.list_of_nodes, -1)
        self.fin_time = 0

    def reverse_graph(self, adjacency_list) -> Dict[str, List[Tuple[str,int]]]:
        rev_adjacency_list : Dict[str,List[Tuple[str,int]]] = defaultdict(list)
        for node_u, list_nodes_v in adjacency_list.items():
            for node_v, weight in list_nodes_v:
                rev_adjacency_list[node_v].append((node_u, weight))
        return rev_adjacency_list

    def dfs(self, node, node_label, set_of_nodes_explored, adjacency_list):
        set_of_nodes_explored.add(node)
        self.node_label[node] = self.current_node_label

        for ne_node,_ in adjacency_list[node]:
            if ne_node not in set_of_nodes_explored:
                set_of_nodes_explored = self.dfs(ne_node, node_label, set_of_nodes_explored, adjacency_list)
        
        self.finishing_time[node] = self.fin_time
        self.fin_time += 1
        return set_of_nodes_explored

    def traverse_graph(self, adjacency_list):
        set_of_nodes_explored = set()
        
        for idx, node in enumerate(self.list_of_nodes):
            self.current_node_label = idx 
            if node not in set_of_nodes_explored:
                set_of_nodes_explored = self.dfs(node, idx, set_of_nodes_explored, adjacency_list)

    def get_conn_comps(self):
        # korajus algorithm

        # Reverse the adjaceny list
        rev_adjacency_list = self.reverse_graph(self.adjacency_list)
        print(f'rev adj list : {rev_adjacency_list}')

        # computing finishing time using dfs
        # if return false, then its not strongly connected.
        self.traverse_graph(rev_adjacency_list)

        # update the order of the list_of_nodes based on finishing time
        print(f'Finishing time : {self.finishing_time}')
        self.list_of_nodes = sorted(self.list_of_nodes, key=self.finishing_time.__getitem__,reverse=True)
        print(f'Sorted list : {self.list_of_nodes}')

        # through ordering of finishing time, run dfs on original list 
        # put in the leader node
        self.current_node_label = None
        self.node_label = OrderedDict.fromkeys(self.list_of_nodes,-1)

        self.traverse_graph(self.adjacency_list)

        return self.node_label
    
    

    def get_shortest_path_from_node(self, source_node):
        assert source_node in self.list_of_nodes
        """
        get shortest path

        keep two sets
        one explored -> keeps track of those nodes that have minimum distance already computed
        other unexplored -> keeps track of nodes whose minimum distance have not been computed

        for every edge from explored -> unexplored, we compute the distance of unexplored node
        from source node s as L(v) = L(s) + weight_{vs}. Multiple edges from explored set (containing s)
        can v . L(v) = min(forall s' in explored(L(s) + weight{vs}) if there is an edge between s' and v)

        And then across for v in unexplored set, we select minimum v' and add the v' to the explored set. 
        Since there is minimum computation, we can use a heap data structure to store the unexplored.

        As we iterate across crossing edges, we keep adding the node and associated computed minium distance to node s to the heap


        """
        from typing import Set 
        node_path_list : List[str] = []
        is_explored : Dict[str, bool] = OrderedDict.fromkeys(self.list_of_nodes,False)

        s_dist : Dict[str,int] = OrderedDict.fromkeys(self.list_of_nodes,float('inf'))
        s_dist[source_node] = 0
        unexplored_node_heap : List[Tuple[int, str]] = []
        from heapq import heapify, heappush, heappop
        
        heappush(unexplored_node_heap,(s_dist[source_node],source_node))

        while bool(unexplored_node_heap):
            # get the minium node
            L_dist, curr_node = heappop(unexplored_node_heap)
            if is_explored[curr_node]:
                continue
            node_path_list.append(curr_node)
            is_explored[curr_node] = True
            
            for n_node, weight in self.adjacency_list[curr_node]:
                updated_val = L_dist + weight
                if s_dist[n_node] > updated_val:
                    s_dist[n_node] = updated_val
                    heappush(unexplored_node_heap, (s_dist[n_node],n_node))
        
        return s_dist, node_path_list

def test_algo_2():
    edges= [
        ('1','2',1),
        ('2','3',1),
        ('3','4',1),
        ('4','1',1),
        ('2', '4',1),
        ('4','5',1),
        ('3','6',1),
        ('6','7',1),
        ('7','5',1),
        ('5','6',1)
    ]
    graph : Graph = Graph()
    graph.populate_graph(edges=edges)
    print(graph.get_conn_comps())

    print(graph.get_shortest_path_from_node('5'))

def test_algo_3():
    edges = [
    ('0', '1', 4),
    ('0', '7', 8),
    ('1', '2', 8),
    ('1', '7', 11),
    ('2', '3', 7),
    ('2', '8', 2),
    ('2', '5', 4),
    ('3', '4', 9),
    ('3', '5', 14),
    ('4', '5', 10),
    ('5', '6', 2),
    ('6', '7', 1),
    ('6', '8', 6),
    ('7', '8', 7)
    ]
    graph : Graph = Graph()
    graph.populate_graph(edges=edges)
    print(graph.get_shortest_path_from_node('0'))
        

test_algo_3()