## to do topological sorting using DFS
from typing import List, Deque, Dict
from collections import deque, OrderedDict

class DirectedGraph:
    def __init__(self, num_vertices):
        self.num_vertices = num_vertices
        self.adjacency_list : List[List[int]] = [ [] for _ in range(0, self.num_vertices) ]
        self.set_explored_nodes = set()
        self.node_ordering_stack : Deque = deque()

    def add_edge(self,ui: int, vi: int):
        self.adjacency_list[ui].append(vi)

    def check_cycle(self, ordering) -> bool:
        # to check cycle, while iterating throught the graph, we check if the topological position
        # of parent must be less than topological position of the child. If not, there is a cycle.

        # Node value -> position
        position : Dict = OrderedDict.fromkeys([i for i in range(0, self.num_vertices)], 0)

        # ordering - in topological order with highest number at beginning
        ordering = ordering[::-1] # reverse the order
        for index, node in enumerate(ordering):
            position[node] = index

        print(f'Ordering : {ordering}')
        print(f'Position : {position}')

        cycle_detected = False
        for node in range(0,self.num_vertices):
            if not self.adjacency_list[node]:
                continue
            if any([ position[node] > position[n_node] for n_node in self.adjacency_list[node] ]):
                cycle_detected = True
                break

        return cycle_detected

    def dfs(self, node):
        stack : Deque = deque()
        stack.append(node)
        self.set_explored_nodes.add(node)

        while bool(stack):
            curr_node = stack[-1]
            if curr_node not in self.set_explored_nodes:
                self.set_explored_nodes.add(curr_node)

            # check if any neighhors are visited or any nodes
            if not self.adjacency_list[curr_node] or all([n_node in self.set_explored_nodes \
                                                          for n_node in self.adjacency_list[curr_node]]):
                # check if its a sink node - no outgoing edges
                if curr_node not in self.node_ordering_stack:
                    self.node_ordering_stack.append(curr_node)
                print(f'Stack : {stack}')
                print(f'Explored_node : {self.set_explored_nodes}')
                print(f'node ordering : {self.node_ordering_stack}')
                stack.pop()

            for n_node in self.adjacency_list[curr_node]:
                if n_node not in self.set_explored_nodes:
                    stack.append(n_node)

    def topological_sort(self, in_reverse = False) -> List[int]:
        """
        Returns list of nodes containing the order in ascending order
        In Reverse false means ordering is returned from 1 to n with n being the sink node
        In reverse True means ordering is retured from n to 1 with n being the sink node
        n refers to the highest priority to take
        
        """
        if not self.adjacency_list:
            return []
        self.current_label = self.num_vertices -1
        for node in range(0, self.num_vertices):
            if node not in self.set_explored_nodes:
                self.dfs(node) # if cycle detected reset  
        # return list of labels in order
        ordering = list(self.node_ordering_stack)[::-1] if not in_reverse else list(self.node_ordering_stack) 
        print(f'Ordering before cycle check: {ordering}')
        return ordering if not self.check_cycle(ordering) else []

def get_topological_ordering(V, edges, in_reverse = False):
    graph : DirectedGraph = DirectedGraph(num_vertices=V)
    for ui,vi in edges:
        graph.add_edge(ui,vi)
    
    return graph.topological_sort(in_reverse=in_reverse)

def test_case_1():
    V = 4
    # Edges
    edges = [[0, 1], [1, 2], [3, 1], [3, 2]]
    print(get_topological_ordering(V, edges))

def test_case_2():
    numCourses = 2
    prerequisites = [[1,0]]
    print(get_topological_ordering(V=numCourses, edges=prerequisites, in_reverse=True))


def test_case_3():
    numCourses = 4
    prerequisites = [[1,0],[2,0],[3,1],[3,2]]
    print(get_topological_ordering(V=numCourses, edges=prerequisites, in_reverse=True))

def test_case_4():
    numCourses = 2
    prerequisites = [[1,0],[0,1]]
    print(get_topological_ordering(V=numCourses, edges=prerequisites, in_reverse=True))

def test_case_5():
    numCourses = 3
    prerequisites = [[0,2],[1,2],[2,0]]
    print(get_topological_ordering(V=numCourses, edges=prerequisites, in_reverse=True))

def test_case_6():
    numCourses = 7
    prerequisites = [[1,0],[0,3],[0,2],[3,2],[2,5],[4,5],[5,6],[2,4]]
    print(get_topological_ordering(V=numCourses, edges=prerequisites, in_reverse=True))

def test_case_7():
    numCourses = 8
    prerequisites = [[1,0],[2,6],[1,7],[6,4],[7,0],[0,5]]
    print(get_topological_ordering(V=numCourses, edges=prerequisites, in_reverse=True))

# test_case_1()
# test_case_2()
# test_case_3()
test_case_4()
test_case_5()
test_case_6()
test_case_7()