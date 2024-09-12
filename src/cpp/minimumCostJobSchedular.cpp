/*
You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the ith job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done on that day.

You are given an integer array jobDifficulty and an integer d. The difficulty of the ith job is jobDifficulty[i].

Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.

*/
/*

States -> i th job, 0 <= i < N - N jobs
Days -> d th day , 0 <= d < D

Finish atleast one job per day

dp(i,d) - minimumu difficulty of starting with ith job on day d 

dp(0,1) - this the result

on the ith job and d th day, the remaining number of days is D-d where atleast one job will be on d day
on the dth day, we can have ith job, i+1 th job, ....i + N-1-(D-d) jobs, so that remaining D-d is distributed across the D-d days.

dp(i,d) = min( (hardest_among_(k) for all i<=k<=j) + dp(j+1,d+1)  ) forall i <= j <= N-(D-d)

dp(i,d) = min_j=i->N-(D-d) ( max_k=i->j jobDifficulty[k]) + dp(j+1,d+1))


*/

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cassert>
#include <string_view>

using namespace std;

typedef vector<vector<int>> Cache;

void print(string_view text, vector<int> arr) {
  std::cout << text << ": ";
  for(auto it = arr.begin(); it!= arr.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << "\n";
}

void ComputeCumulativeHardest(const vector<int>& jobDifficulty, vector<int>& cumulativeHardest) {
  cumulativeHardest = vector<int>(jobDifficulty.size(), 0);

  int maxValue = std::numeric_limits<int>::min();
  auto r_it_c = cumulativeHardest.rbegin();
  for(auto r_it = jobDifficulty.crbegin(); r_it != jobDifficulty.crend(); r_it++) {
    maxValue = max(*r_it, maxValue);
    *r_it_c = maxValue;
    r_it_c++;
  }
}

int findMinimumCost(const vector<int>& jobDifficulty, const vector<int>& cumulativeHardest,int jobId, int day, int numDays, Cache& cache) {
  int N = jobDifficulty.size();
  int D = numDays;
  if (day == D) {
    return cumulativeHardest[jobId]; // returns the hardest job from ith job on the day
  }

  assert(cache.size() == N && cache[0].size() == numDays);

  if (cache[jobId][day] != -1) return cache[jobId][day]; 

  int minVal = std::numeric_limits<int>::max();
  int hardest = std::numeric_limits<int>::min();
  for(int j = jobId ; j < N-(D-day); j++) { 
    //hardest = max(hardest, cumulativeHardest[j]);
    hardest = *std::max_element(jobDifficulty.begin() + jobId, jobDifficulty.begin() + j+1);
    int val = findMinimumCost(jobDifficulty, cumulativeHardest, j+1, day+1, numDays, cache) + hardest;
    minVal = min(minVal, val);
  }
  assert (cache[jobId][day] == -1);
  cache[jobId][day] = minVal;
  return minVal;
}

int findMinimumCostDay0(const vector<int>& jobDifficulty, int numDays) {
  if (jobDifficulty.size() < numDays) return -1;

  vector<int> cumulativeHardest;
  ComputeCumulativeHardest(jobDifficulty, cumulativeHardest);
  //print("Cumulative", cumulativeHardest);

  Cache cache(jobDifficulty.size(), std::vector<int>(numDays, -1));
  
  return findMinimumCost(jobDifficulty, cumulativeHardest, 0, 1, numDays, cache);
}

void run_test(const std::vector<int> jobDifficulty, int numDays) {
  int cost = findMinimumCostDay0(jobDifficulty, numDays);
  std::cout << "Cost : " << cost << std::endl;
}


// To execute C++, please define "int main()"
int main() {
  run_test(vector<int>{6,5,4,3,2,1}, 2);
  run_test(vector<int>{9,9,9}, 4);
  run_test(vector<int>{1,1,1}, 3);
  run_test(vector<int>{11,111,22,222,33,333,44,444},6);
}
