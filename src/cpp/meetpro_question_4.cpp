
// A path consists of a sequence of stones, each marked with a non-negative integer.
//  You start at the beginning and progress always forwards toward the end. 
//  When you step (or jump) onto a stone, you earn points equal to the value 
//  on that stone times the sqrt(length of the step or jump). The sum of all points 
//  is the total score you earned from traversing the complete path.

/*        6ht
 2 3 4 5 --> 5 * 4 = 20
1        - --> 3 * 2 + 5 * 2. =
1 2        ---> 2 * 1 + 5 * 3 = 
o to n-1
maximum_points
arr = x  [0,b,c,d,e]
1 3 5 7 9 -> 9 * 4 = 36

dp(i) = total_score_from_traversing_the_path from 0 to it

dp(0) = 0
dp(1) = b * 1. //1
dp(2) = max (c * 2, dp(1) + c * 1) // 5*2, 1+5 => 10
dp(2) = max( c * 2, dp(1) + c)


dp(3) = max (d * 3 , dp (2) + d) //. 3 * 3 , 10 + 3 =  13

[0,b,c,d,e]
dp(3) = max( 3 * d, dp[1] + 2*d, dp[2] + d) 

dp(i) = max ( i * arr[i], dp[i-2] + 2 * arr[i], dp[i-1] + 1 * arr[i] )

j < i
prev_cost[i,j] = dp[i-j] + j * arr[i] , forall j >= 0, j <= i

dp(i) = max(prev_cost[i,0], prev_cost[i,1], prev_cost[i,2],.... )


dp(i) = max(  dp[i-1] + 1* arr[i], dp[i-2] + 2 * arr[i] , ....., dp[0] + i*arr[i] )
        = max ( )

dp(4) = 4 * 4, 13 +4 = 17

#
dp(i) = max (i * arr[i], dp[i-1] + arr[i] )

return dp(n-1)
[0, 7, 5, 3, 4]  ->  arr[i]
[7, 7, 5, 4, 4]

=  
dp(n-1) = max(dp(n-2), 1 * dp(n-1), 2 * dp(n-2), ...(n-1) * dp(0))


prev_cost[i,j] = dp[i-j] + j * arr[i]
max_prev_cost

dp(i) = max(prev_cost[i,0], prev_cost[i,1], prev_cost[i,2],.... )
i=2 
prev_cost[2,0], prev_cost[2,1], prev_cost[2,2]

i =3 
prev_cost[3,0] prev_cost[3,1], prev_cost[3,2], prev_cost[3,3]

*/


#include <iostream>
#include <vector>
#include <algorithm>

// Time O(N2), Space - O(N)
int maxScore(std::vector<int>& stones) {
  vector<int> maxPoints(stones.size(),0);

  // i =1 ; j 0,1 => maxPoints[i=1] ;
  // i =2 ; j 0,1,2 => maxPoints[i-1], 
  // O(N )
  for(int i = 1; i < stones.size(); i++ ) {
    int localMaxPoints = 0;
    // (O(N-1))
    for(int j = 1; j<= i; j++) {
      localMaxPoints = max(maxPoints[i - j] + j * stones[i], localMaxPoints) ;
    }
    maxPoints[i] = localMaxPoints;
  }
  return *(maxPoints.rbegin());
}


