/*

Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.

eg: [0,2],[1,2],[3,4] => [0,2] [3,4]
eg : [0,3], [1,2] , [4,6],[5,8] => [0,3] , [4,8]


#approach 1
[start_1, end_1] -> O(NLogN).  ; c >= a
[a, b], [c, d]  ->  c < b  for  c > a  => overlap => [a, max(b,d)]   
[0,5], [2,3] -> [0,5] => 
[0,5], [0,2]

[0,3], [4,6],  -> merge every consecutive intervals -> O(N) -> 

[4,6] [5,7]. -> 

O(NlogN) + O(N) = O(N log N)  

*/

#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

typedef pair<int,int> Interval;

bool checkOverlap(Interval a, Interval b) {
    assert (a.first <= b.first);
    return b.first <= a.second;
}

// O(N Log N)
// Space complextity - O(N)
vector<Interval> mergeIntervals(vector<Interval> intervals) {
    // sort - O(N Log N)
    sort(intervals.begin(), intervals.end(), [] (Interval a, Interval b) {
        return a.first < b.first;
    });
    
    vector<Interval> outputIntervals; // O(N)
    for(int i = 0 ; i < intervals.size(); i++) {
        if (i ==0) {
            outputIntervals.push_back(intervals[i]);
            continue;
        }
        // compare th last entry of output intervals with current
        assert (outputIntervals.size() > 0);
        
        auto currIntervalIt = outputIntervals.rbegin();
        assert (currIntervalIt->first <= intervals[i].first);
        
        // check overlap
        if (checkOverlap((*currIntervalIt), intervals[i])) {
            // modify current interval
            currIntervalIt->second = max(intervals[i].second, currIntervalIt->second);
        } else {
            outputIntervals.push_back(intervals[i]);
        }
    }
    return outputIntervals;
}

void printIntervals(const std::string_view& text, const vector<Interval>& intervals) {
    std::cout << text << " : ";
    for(auto & interval : intervals) {
        std::cout << "[" << interval.first << "," << interval.second << "]" << std::endl;
    }
}

void test_case(vector<Interval>& intervals) {
    vector<Interval> outputIntervals = mergeIntervals(intervals);
    printIntervals("Input", intervals);
    printIntervals("Merged", outputIntervals);
}

int main(int argc, char** argv) {
    vector<Interval> intervals {
        {1,2},{0,3},{4,8},{5,6},{20,24},{10,25},
    }; 
    test_case(intervals);
}