
# Max sum of non-adjacent elements
Given an array of integers, find the subset of non-adjacent elements with the maximum sum.  
https://www.hackerrank.com/challenges/max-array-sum/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming  

```c++
/*
5
3 5 -7 8 10

[] sum = 0, nonadj sum up to i = 0, dp[i] = 0
dp[0] = 0
3 | 5 -7 8 10 
dp[1] = 3 
3* 5 | -7 8 10 
dp[2] = 5 // max(dp[i-2] + a[i], dp[i-1]) 
3 5* -7 | 8 10 
dp[3] = 5 
3 5* -7 8 | 10 
dp[4] = 13 
3 5 -7 8* 10 | 
dp[4] = max(15,13) = 15 
*/
int maxSubsetSum(const vector<int>& arr) 
{
    // dp[i] max nonadj subs sum for subarray [a[0], ..., a[i-1]]
    int n = arr.size();
    vector<int> dp(n + 1); 
    dp[0] = 0;
    dp[1] = arr[0];
    for(int i = 2; i < n + 1; ++i)
    {
        dp[i] = max({dp[i-2] + arr[i-1], dp[i-1],arr[i-1]});
    }
    return dp[n];

```