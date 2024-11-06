/**
Julie goes to a bank to open up an account. When she arrives at the bank, there are N agents (number 1 to N) who are not serving any customer, and M customers have already arrived before Julie (Julie is at position M+1 in the line). 

This particular bank follows the rule of first-come-first-serve. If more than 1 agent can serve a customer at any time, the customer will always choose the one with the lowest agent number. For agents, each of them has a constant serving time that the ith agent will take times[i] minutes to serve a customer. 

Assume Julie arrived at time 0, and all the agents are idle and start to serve the customers.

We would like to know how many minutes Julie has to wait before meeting with an agent?

Give a quick example to illustrate the question
There are 3 agents with processing time 1min, 2min and 3min. 3 other people are currently waiting in front of Julie. All 3 customers can be taken in by the 3 agents. Given the first agent (index 0) will finish processing in 1min and then take in Julie, the waiting time here is 1 minute (return 1)


1. N agents -1 to N not serving customer
M customers arrived , M+1

times[i] = ith time to serve a customer

A1 , A2, ........ AN

C1 C2 ...CM

# Case 1
N = M
output = min(times[i])

# Case 2
N > M, output = 0;

# Case 3 
N < M; 

Time at which 3 agents 6 customers

A1 A2 A3.  --- M=4 

time taken for 4th customer, Julie
(M - N)  

times[i] = 
A1 A2 A3 
Eg: 

A = 1min., 2min, 3min 
C = C1.     c2    c3

C4 min(C4) = min(times)

A = 1 min, 1 min, 2 min 
    C4

Julie = min(C4) + min(times)

Another exmaples
A = 3 min, 2 min, 5 min.  => A = 1 min, 2 min, 3 min

time()  times[i] - min(times[i])


customers 1 to M-
  N to M

Hoa many minutes
out[i] = time take to start serving the customer
out[i] = 0 (1 <i <= N)

out[N+1] to ...out[M]
out[N+1] = min(times). ; times -> update

out[N+j] = 

out[M+1] = Julies
out[N+1] = min(times)

A = 3 min, 2 min, 5 min

3 min, 5 min -> heap 
3 - 2, 5-2 => 1,5 

heap (, time taken for agent)
heap (fin_time taken, time taken for agen)

1. heap - (3 min, 3min), (2min, 2 min), (5 min, 5min)
2. (2min, 2min) --> (3 min, 3 min), (5min, 5 min) --  
  add back to the heap (3 min, 3min), (5 min).  ,(4min, 2min)
  (3min, 3min) => (5 min, 5 min),  (4min, 2min).   -> (5,5),(4,2), (6, 3min)
  (5,5)(6,3).(6,2) 

  M+1 iteration = (a,b)
  =>a i finidhing time
  */

#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>

using namespace std;

typedef pair<int,int> TimePair; // holds finishing time stamp, time taken

int findJulieTime(vector<int>& times, int M) {
  int N = times.size();

  // create the heap
  vector<TimePair> timepairs;;
  for(auto& time : times) {
    timepairs.push_back(make_pair(time,time));
  }

  // create a min heap
  // N- 
  make_heap(timepairs.begin(), timepairs.end(), std::greater<pair<int,int>>());

  // iterate from 0 to N-1 (0 to N-1 agents) already served
  // from N to M-1 (0 to M-1 customers) -> Mth customer is Julie  
  // 

  /*
  (3 min, 3min), (2min, 2 min), (5 min, 5min)

  (2,2),(5,5),(3,3)
  
  3 M + Julie  
  */
  for(int i = N; i < M ; i++) {
    // pop the min heap - Log(N)
    pop_heap(timepairs.begin(), timepairs.end(),std::greater<pair<int,int>>()); 
    TimePair tt = (*timepairs.rbegin()); //(2,2)
    timepairs.pop_back(); 

    // update the popped element with double the value
    tt.first += tt.second;  //(4,2)

    // push the heap
    timepairs.push_back(tt); //Log(N)  (5,5),(3,3),.(4,2)
    push_heap(timepairs.begin(), timepairs.end(),std::greater<pair<int,int>>());
  }

  // time complexicty = M-N Log(N), space complexity - O(N)
  // Julies turn
  pop_heap(timepairs.begin(), timepairs.end(),std::greater<pair<int,int>>()); 
  TimePair tt = (*timepairs.rbegin());

  return tt.first;
}

// To execute C++, please define "int main()"
int main() {



}


// Your previous Plain Text content is preserved below:

// Pad for Binu Nair - Sr. Machine Learning Engineer, Core Engineering