/*

You are painting a fence of n posts with k different colors. You must paint the posts following these rules:

Every post must be painted exactly one color.
There cannot be three or more consecutive posts with the same color.
Given the two integers n and k, return the number of ways you can paint the fence.

5 posts 3 colors - r ,g ,b 

k colors - atmost only 2 repeated colors

r,r,g,b,r
r,r,g,b,b - 
r,g,g,r,b

n > k

state : index of post 0 <= i <= N-1 ; 0 <= k <= K-1 -> kith color

n < k

5 posts, 3 colors

ith post - 
numWaysToPaintPost(i) =  

numWaysToPaintPost(0) = k # r #r 
numWaysToPaintPost(1) = k # g #r 
numWaysToPaintPost(2) = k-1 if paint(0) == paint(1) or k ways if not same
numWaysToPaintPost(3) = 
...
numWaysToPaintPost(k) = 

# number of ways to paint post i with k 
dp[ith,kth] =  

dp[i] = number of ways to paint i posts
dp[i] = k-1 if different from previous painted post (color(post[i-1]) + 1 if post[i-1] is same but not post[i-2]

base case
r -> 2 ways or 3 ways
dp[1] = k # to paint one post
dp[2] = k * k
dp[3] = (k-1) * dp[2] + (k-1) * dp[1] 

totalways(i) = (k-1) * total_ways(i-1) + (k-1) * total_ways(i-2)
 = (k-1) * (totay_ways(i-1) + total_ways(i-2))

*/


#include <iostream>
#include <typeinfo>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unordered_map<int, int> Cache;

int findNumWays(int pIndex, int k, Cache& cache) {
    if (pIndex == 1) { 
        return k;
    }
    if (pIndex == 2) {
        return k*k;
    }

    if (cache.find(pIndex) == cache.end()) {
        int val = (k-1) * (findNumWays(pIndex-1,k, cache) + findNumWays(pIndex-2,k, cache));
        cache.insert(make_pair(pIndex,val));
    }
    return cache[pIndex];
}


// To execute C++, please define "int main()"
int main() {
    int N = 7;
    int K=2;
    Cache cache;
    int num_ways = findNumWays(N,K,cache);
    std::cout << "num ways : " << num_ways << std::endl;
}
