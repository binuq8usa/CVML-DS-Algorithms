/*

Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.

// if two intervals overlap -> two meeting rooms - 
// if two intervals do not overlap -> one meeting room


// interval - one meeting room
// - max number of meeting rooms = N
//  - [1, 5]. [2, 6]. [9, 12] -> 2 meetings have overlap - 2 meeting rooms, 
// [1,3] [2,4], [3, 5],[4,6].  => [1,4], [3,5] => [1,5], [4,6] => [1,6]
            -> [1,3][2,4] -> 2 rooms
            -> [3,5][4,6] -> 
            
            ->  4 overlaps - 4 meeting rooms.   -> [1, 6] -> 4 - 1  = 3
//  [1,3] [2,4], [3, 5],[4,6], [9,11],[10,13] -> 6 meeting rooms -> [1,6], [9,11] (non-overlapping intervals) => max - non_overlapping = min overlaps

// [0,30], [5,10], [15,20]

// [0,  30]  - 1 room
// [5, 10] - 2 rooms
// [15, 20] - 2


// sort them in 

[1,  3] --   1  
  [2,  4] -- 2 
     3,  5. 
       4, 6


[1,3].  [2,4].   [3,5].  [4,6]

[1,3] 
    [2,4]
        [3,5]
            [4,6]

N = 1
N = N+1

minEndTimeSeen 
if currStartTime >= minEndTimeSeen => N = N. # a session has finished
else if currStartTime < minEndTimeSeen => N = N+ 1
[1, 3] => N = 1
  [2  4] => N = N + 1 = 2
    [3,5] => N = N. => remove [end times from  ]
      [4, 6] => N => remove end Times
      
Algorithm
1. Sort the array based on [starting time]
2. THrough iteration, maintain a min heap for ending time.
3. Increment room count ; N = 1
3. Iterate through sorted list
    -> if first element or heap empty, => N = N; add end time to minHeap
    -> Check if startTime < MinHeap Element => N = N + 1; add curr end time to the heap => if any conference room frees up
    -> 
     
    
O(N Log N) + O(N) + O(LogN)
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cassert>

using namespace std;

typedef pair<int, int> Interval;

void printVector(const vector<int>& vec) {
    std::cout << "[ ";
    for(auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
}

int getMinimumRooms(vector<Interval>& intervals) {
    // sort the intervals
    sort(intervals.begin(), intervals.end(), [](Interval a, Interval b) {
       return a.first < b.first; 
    });
    
    // push all the end times into a heap
    vector<int> endTimesHeap;
    
    int minRooms = 0;
    for(auto& interval : intervals) {
        assert (interval.first < interval.second);
        if (endTimesHeap.size() == 0) {
            minRooms += 1;
            endTimesHeap.push_back(interval.second);
            push_heap(endTimesHeap.begin(), endTimesHeap.end(), std::greater<int>()); // 5
            continue;
        }
        int minEndTime = endTimesHeap[0]; // 9
        if (interval.first < minEndTime) { //8 < 9
            minRooms += 1;
        } else { // if not minEndTime interval is completed. Remove it from heap
            pop_heap(endTimesHeap.begin(), endTimesHeap.end(), std::greater<int>()); 
            endTimesHeap.pop_back();
        }
        endTimesHeap.push_back(interval.second); // 9
        push_heap(endTimesHeap.begin(), endTimesHeap.end(), std::greater<int>());
        printVector(endTimesHeap);
    }
    
    return minRooms;
}


int main() {
    vector<Interval> intervals{
      {1,5},{8,9},{8,9}
    };

    int val = getMinimumRooms(intervals);
    std::cout << "Val : " << val << std::endl;    
}
