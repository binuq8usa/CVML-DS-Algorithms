/*
We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit of profit[i].

You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.

startTime = [1,1,3,5,6] # jobs are increasing order of the start times 
endTime =   [2,3,5,6,8]
profit =    [10,30,5,100,60]

Approach #1 - Will work only for cases where end time is increasing, and the maximum end time is in the end of the array.
list of overlapping intervals - get the maximum profit from the non-overlapping set
non-overlapping jobs = 

Which can be mered? merge critera is if there is an overlap.
[1,2]
[1,3]
[3,5]
[5,6]
[6,8]
Node A - (start,endtime)
Node B.  Node A -> Node B => if there is overlap (edge).
O(N) N-1 comparisons - you have to create the graph - O(N^2) - operations . Get connected componens through BFS - from each connected component, find max and the add the maximums profits.

if startTime[i] < endTime[i-1] => merge or update the profit

1,1,3,5,6,8
2,3,5,9,8,12

1,2,3,5,8
3,4,6,8,20
| | +
    | +
      | |. |. => max(profit) +

O(N) - times
N.Log(N)

*/


/*
Solution similar to my DP but search is on a binary search of the start in the end times of the previous jobs. The job having the end time closest to the current job start time and less than current job start time will be selected. 
Mav value of dp[i-1] (if current job is not selected), dp[i] + prevjob. This is the recursion. 




*/

#include <iostream>
#include <ostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

typedef tuple<int,int,int> Entry;

ostream& operator<<(ostream& os, const Entry& entry) {
  os << "(" << get<0>(entry) << "," << get<1>(entry) << "," << get<2>(entry) << ")";
  return os;
}

template <typename T>
void printArray(string_view text, const vector<T>& entries) {
  std::cout << text << " ";
  for(auto& entry: entries ) {
    std::cout << entry << std::endl;
  }
}

vector<Entry> getTuples(const vector<int>& startTimes, const vector<int>& endTimes, const vector<int>& profit) {
    vector<Entry> entries; 
  for (auto it = startTimes.cbegin(), it_e = endTimes.cbegin(), it_p = profit.cbegin() ; ; it++, it_e++, it_p++) {
    if (it == startTimes.cend() || it_e == endTimes.cend() || it_p == profit.cend()) {
      break;
    }
    entries.push_back(make_tuple(*it, *it_e, *it_p));
  }
  return entries;
}

int findMaximumProfit(const vector<int>& startTimes, const vector<int>& endTimes, const vector<int>& profit) {
  // combine startTimes, endTimes, profit
  vector<Entry> entries; 
  for (auto it = startTimes.cbegin(), it_e = endTimes.cbegin(), it_p = profit.cbegin() ; ; it++, it_e++, it_p++) {
    if (it == startTimes.cend() || it_e == endTimes.cend() || it_p == profit.cend()) {
      break;
    }
    entries.push_back(make_tuple(*it, *it_e, *it_p));
  }

  printArray("Tuples", entries);

  // sort the entries - N log N operations
  sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b) -> bool 
  {
    return get<0>(a) < get<0>(b);
  });

  printArray("Sorted Tuples", entries);

  int sumProfit = 0;
  int maxProfit = 0;
  Entry selected;
  // O(N) 
  for(int i = 0 ; i < entries.size(); i++) { //(1,3,50) , (2,4,10) , (3,5,40), (3,6,70)
    if (i == 0) {
      maxProfit = get<2>(entries[i]); // 50 
      selected = entries[i]; // (1,3,50)
      continue;
    } 
    // startime i < endtime i-1
    int currProfit = get<2>(entries[i]); // 40
    if (get<0>(entries[i]) < get<1>(selected)) { // here save the tuple that got selected and compare with the selected version
      if (currProfit > maxProfit) {
        maxProfit = currProfit; //50 // 70
        selected = entries[i];
      } 
      // maxProfit = max(maxProfit, get<2>(entries[i])); // 100
    } else {
      sumProfit += maxProfit; //50
      maxProfit = currProfit; // 40
      selected = entries[i];
    }
  }
  sumProfit += maxProfit; // to add the last element // 135
  return sumProfit;
}

// 2 6 3 8 -> a.start, a.end, b.start, b.end

// 3 8 2 6
// a.end > b.start or a.start < b.end
//                     2         6              2           8             2       3 
//                           3       8              3.    6                          6       8 
//.                     3           8            3     6
//                  2       6                  2         8

//                     3     6
//.                  2   5
//                  2     3
//                        3        6
//                         1.    2  
//                         1        3
bool isThereOverlap(const Entry& a, const Entry& b) {
  int startTimeA = get<0>(a);
  int endTimeA = get<1>(a);
  int startTimeB = get<0>(b);
  int endTimeB = get<1>(b);
  // startTimeA 
  std::cout << "Start Time, End time A : " << startTimeA << "," << endTimeA << std::endl;
  std::cout << "Start Time, End time B : " << startTimeB << "," << endTimeB << std::endl;

  return ( (endTimeA > startTimeB &&  startTimeA <= startTimeB) || (startTimeA < endTimeB && startTimeA >= startTimeB ) );
}

/*
Approach #2 - DP problem
DP problem - if no jobs are scheduled. 
dp[i] = profit obtained from jobs at ith iteration (for some overlapping jobs -only one job is completed)
maxprofit depends on what non-overlapping jobs were scheduled.

O(N^2) - 
x  1   1    3     4      5
   2   3    5     6      8
   10  30   5    100     60

   10.  30.  35.  130.   90

for j <= i
no_overlap[i,j] = {j if no overlap else None if overlap}
is_there_no_overlap[3] =  list_of_nonoverlapping_indices = list(0,1)

dp[-1] = 0 // 
dp[0] = profit[0] // 10 
dp[1] = (overlap with previous job and max(of the jobs)) or  profit[0] + profit[1]
dp[1] = max(dp[0], profit[1]) if overlap(0,1) // 30
      = dp[0] + profit[1] if no overlap  

dp[2] = profit[2] + max_j<=2 and no overlap( dp[j]).   // 35 
       = max(dp[1], profit[2])          if all j's overlap

dp[i] = max_j<=i, no_overlap (dp[j] + profit[i]).     // 130 
      = max(do[i-1], profit[i])

//190 

n jobs = 5
startTime[i] =     ; endTime[i] >= startTime[i]
endTime[i]
profit[i]

*/

vector<int> extractEndTimes(const vector<Entry>& entries) {
    vector<int> elements; 
  for (auto it = entries.cbegin(); it != entries.cend() ; it++) {
    elements.push_back(get<1>(*it));
  }
  return elements;
}


int findMaximumProfitDP(const vector<int>& startTimes, const vector<int>& endTimes, const vector<int>& profit) {
  auto entries = getTuples(startTimes, endTimes, profit);
  
  // sort the entries - N log N operations - based on end time
  auto cmp = [](const Entry& a, const Entry& b) -> bool 
  {
    return get<1>(a) < get<1>(b);
  };
  sort(entries.begin(), entries.end(), cmp);

  printArray("Entries", entries);
  vector<int> sortedEndTimes = extractEndTimes(entries);

  int maxProfit = 0;
  vector<int> dp(entries.size(),0); //

  for(int i = 0; i < entries.size(); i++) {

    // find any non overlapping segments
    dp[i] = get<2>(entries[i]);
    if (i == 0) continue;

    // int max_val = 0;
    // bool foundNoOverlap = false;
    // std::cout << "Value i : " << i << std::endl; 
    // for(int j = 0; j < i; j++) {
    //   if(!isThereOverlap(entries[j], entries[i])) {
    //     std::cout << "Max val : " << max_val << std::endl;
    //     max_val = max(max_val, dp[j]);
    //     std::cout << "Max val after max : " << max_val << std::endl;
    //     std::cout << "dp [" << j << "] : " << dp[j] << std::endl;
    //     foundNoOverlap = true;
    //   }
    // }
    // if (foundNoOverlap) dp[i] += max_val;
    // else dp[i] = max(dp[i], dp[i-1]); // either i do ith job or use selections from dp[i-1]

    int prevJobProfit = 0;
    // use the start time of current job, and search for the end jobs from 0 to i-1
    int startTime = get<0>(entries[i]);
    auto it = std::upper_bound(sortedEndTimes.begin(), sortedEndTimes.begin() + i, startTime); // lower bound gives startTime <= x , so what we want is startTime >y <=x. we need y which is lower_bound - 1
    
    if (it != sortedEndTimes.begin()) { 
        int ind = it - sortedEndTimes.begin()-1;
        prevJobProfit = dp[ind];
    }

    dp[i] = max(get<2>(entries[i]) + prevJobProfit, dp[i-1]);
    maxProfit = max(maxProfit, dp[i]); 
  }
  printArray("DP", dp);
  return maxProfit;
}

void test_case(vector<int> startTimes, vector<int> endTimes, vector<int> profit) {
  //int maxP = findMaximumProfit(startTimes, endTimes, profit);
  int maxP = findMaximumProfitDP(startTimes, endTimes, profit);
  std::cout << "Max P : " << maxP << std::endl;
}

// To execute C++, please define "int main()"
int main() {
  // vector<int> startTimes{1,1,3,5,6};
  // vector<int> endTimes{2,3,5,7,8};
  // vector<int> profit{10,30,5,100,60};

//   vector<int> startTimes{1,1,1};
//   vector<int> endTimes{2,3,4};
//   vector<int> profit{5,6,4};

    // FAILING : Actual answer - 150, I am getting 120
    // because (3,10,100) hogs up the rest of the search. We need a way to back track the search based on end time also. 
    // This is why DP needs to be solved from nth iteration back to zero, dp[n] = maxProfit at n = 0 since there is no more jobs to be scheduled. 
  // vector<int> startTimes{1,2,3,4,6};
  // vector<int> endTimes{3,5,10,6,9};
  // vector<int> profit{20,20,100,70,60};

  // vector<int> startTimes{1,1,3,4,5};
  // vector<int> endTimes{2,3,5,6,8};
  // vector<int> profit{10,30,5,100,60};

  vector<int> startTimes{1,2,3,3};
  vector<int> endTimes{3,4,5,6};
  vector<int> profit{50,10,40,70};

    // vector<int> startTimes{15,44,15,47,11,18,5,41,38,25,19,25};
    // vector<int> endTimes{33,48,20,49,37,22,32,48,39,37,38,40};
    // vector<int> profit{18,19,16,1,5,12,17,7,19,9,18,9};


  test_case(startTimes, endTimes, profit);
}