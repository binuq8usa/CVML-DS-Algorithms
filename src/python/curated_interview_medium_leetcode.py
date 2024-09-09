def Question1():
    # Given a string s, find the length of the longest substring without repeating characters.
    """
    https://leetcode.com/explore/interview/card/top-interview-questions-medium/103/array-and-strings/779/
    """
    #
    from typing import List
    def lengthOfLongestSubstring(query_string: str) -> int:
        len_longest_substring = 0
        list_of_sub_str_chars : List[str] = []

        # loop
        for idx, ch in enumerate(query_string):
            if ch in list_of_sub_str_chars:
                idx2 = list_of_sub_str_chars.index(ch)

                print(f'set : {list_of_sub_str_chars}, Longest so far : {len_longest_substring}')
                # list_of_sub_str_chars = []
                list_of_sub_str_chars = list_of_sub_str_chars[idx2+1:]
                print(f'set after removing: {list_of_sub_str_chars} ')
            list_of_sub_str_chars.append(ch)
            len_longest_substring = max(len(list_of_sub_str_chars),len_longest_substring)

        print(f'set : {list_of_sub_str_chars}, Longest so far : {len_longest_substring}')

        return len_longest_substring

    def test_case(query_string):
        #query_string = "abcdabcd"

        print(f'Len of Substring : {lengthOfLongestSubstring(query_string=query_string)}')

    test_case("abcdabcd")
    test_case("abcdaabca")
    test_case("")
    test_case("abcdaabca")
    test_case("aabcccdefg")
    test_case("aabcbacc")
    test_case("dvdf")
    test_case(" ")

def Question2():
    """
https://leetcode.com/explore/interview/card/top-interview-questions-medium/107/linked-list/785/

"""


    from typing import Optional, Deque
    from collections import deque

    class ListNode:
        def __init__(self, x):
            self.val = x
            self.next: Optional[ListNode] = None

    def get_reverse_stack(head : ListNode) -> Deque[ListNode]:
        stack : Deque[ListNode] = deque()
        temp : Optional[ListNode] = head
        while temp:
            stack.append(temp)
            temp = temp.next

        return stack

    def getIntersectionNode(headA : ListNode, headB : ListNode) -> Optional[ListNode]:
        # iterate through the list and push it to stack
        
        stackB : Deque[ListNode] = deque()

        # iterate throuhg list
        stackA : Deque[ListNode] = get_reverse_stack(headA) # O(m)
        stackB : Deque[ListNode] = get_reverse_stack(headB) # O(n)

        # storage O(m+n)
        commonNode : Optional[ListNode] = None
        while bool(stackA) and bool(stackB):
            if id(stackA[-1]) != id(stackB[-1]):
                break
            
            assert stackA[-1].val == stackB[-1].val

            commonNode = stackA.pop()
            stackB.pop()

        return commonNode

def Question3():
    from typing import List, Tuple, Set

    class Solution:
        def __init__(self) -> None:
            self.set_of_explored : Set[Tuple[int,int]]= set()
        
        def check_validity(self, grid, valid_point : Tuple[int,int]):
            n_x, n_y = valid_point
            num_rows = len(grid)
            num_cols = len(grid[0])
            # TODO: had made a mistake here - in indexing
            return 0 <= n_x < num_cols and 0<= n_y < num_rows and grid[n_y][n_x] == "1"

        def find_valid_neigbhors(self, grid, coords):
            x,y = coords
            neighor_list = []
            for coords in [(x-1,y), (x+1, y), (x, y-1), (x, y+1)]:
                n_x, n_y = coords
                if self.check_validity(grid, (n_x,n_y)):
                    neighor_list.append((n_x,n_y))

            return neighor_list

        def dfs(self, grid : List[List[str]], start_coords : Tuple[int,int]) -> bool:
            self.set_of_explored.add(start_coords)
            for n_x,n_y in self.find_valid_neigbhors(grid, start_coords):
                if (n_x,n_y) not in self.set_of_explored:
                    self.dfs(grid, (n_x, n_y))
            return True

        def provide_land_indices(self, grid : List[List[str]]):
        for row_index, row in enumerate(grid):
            for col_index, value in enumerate(row):
                if value == "1":
                    yield (col_index, row_index) # storing x,y

        def numIslands(self, grid : List[List[str]]) -> int:
            num_islands = 0
            for coords in self.provide_land_indices(grid):
                if coords not in self.set_of_explored:
                    num_islands += self.dfs(grid= grid, start_coords=coords) 
            return num_islands


    def test_case(grid):
        sol : Solution = Solution()
        num_islands = sol.numIslands(grid)
        print(f'Number of islands : {num_islands}')

    grid = [
    ["1","1","1","1","0"],
    ["1","1","0","1","0"],
    ["1","1","0","0","0"],
    ["0","0","0","0","0"]
        ]
    test_case(grid)
    grid = [
    ["1","1","0","0","0"],
    ["1","1","0","0","0"],
    ["0","0","1","0","0"],
    ["0","0","0","1","1"]
    ]
    test_case(grid)
    test_case([["1","0","1"]])

