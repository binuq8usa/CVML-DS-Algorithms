"""
There are N balls with the numbers on them in a bag (each ball has unique number).  k balls are randomly drawn out of this bag and their numbers written down (each ball could be drawn once). How would we write a program that can simulate the same operation?

We have the following function to generate randomness: 
random() produces a float between [0, 1] randomly
randInt(lo, hi) produces an integer between [lo, hi] randomly

# index from 1 to N
# k balls are drawn , each ball drawn once
N C k = N! / (K! (N-k)!) 

output - list of indexex

random()
randIn(lo, hi) - >[lo, hi]

N balls - [ ]



"""

from typing import List

# Assumption - distinct 
# 1 to N balls - 5, 7, 9 ... -- 10 balls 
# only for distinct
# List of Nums - [distinct, non repeating] - 1 to N and N balls
def selectBall(input_nums: List[int]):  # 1, 3 to N.  -5, 9, ...
    # random, randInt
    
    val = None
    # while True:
    #     selectedIndex = randInt(0, len(inputs_nums)). 
    #     val = inputs_nums[selectedIndex]
    #     if val not in input_nums:
    #         break
    # 
    selectedIndex = randInt(0, len(inputs_nums)) # O(1)

    return inputs_nums[selectedIndex], selectedIndex #2   # 4

# Time complexity O(K) - space complexity - O(K) 
def drawKBalls(input_nums : List[int], k : int) -> List[int]:
    # k < N
    output_nums = [] 
    N = len(input_nums)
    #input_set = set(input_nums)

    # O(NK)
    while input_nums: # O(K)
        num_seen = len(output_nums) 
        if num_seen > N:
            break
        ball_val, selectedIndex = selectBall(input_nums[0:N-num_seen]) # O(1).
        output_nums.append(ball_val) # O(1)

        temp = input_nums[-1]
        input_nums[selectedIndex] = temp
        input_nums[-1] = ball_val

        if ( len(output_nums) == k) break; 

    return output_nums

"""
Given list of floats, we want to calculate some moving average of these lists

size_of_window = k
List[int], k

[K, k]

"""

def mean(input_nums : List[int]): # O(K)
    m_num = 0.0
    for num in input_nums: 
        m_num += num
    return m_num/len(input_nums)


def movingAverage(input_nums: List[int], int k) -> List[int]:
    if len(input_nums) <= k:
        return mean(input_nums)
    
    output_nums = []
    
    # O(N-K) - time complexity ; space complexity - O(N-K)
    # O( (N-k).K)
    for idx in range(0, len(input_nums)-k): # 5 -   0, 1, 2 ,3. => 2, 3, 4, 5    =>  0, 1,2, 3, 4
        idx_end = idx + k
        output_nums.append(mean(input_nums[idx:idx_end])) # O(K)
    
    return output_nums


# We can ptimize by subtract mean from previous element, add the next element. *k - 
