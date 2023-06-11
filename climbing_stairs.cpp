#include <bits/stdc++.h>
using namespace std;

/*The approach is to consider all possible combination steps i.e. 1 and 2, at every step. To reach the Nth stair, one can jump from either (N – 1)th or from (N – 2)th stair. Hence, for each step, total ways would be the summation of (N – 1)th stair + (N – 2)th stair.
The recursive function would be:
ClimbStairs(N) = ClimbStairs(N – 1) + ClimbStairs(N – 2).*/
/*T(n)=O(2^n) and S(n)=O(1)*/
int climbing_stairs_brute_REC(int n)
{
    if (n < 2)    return 1;
    else    return climbing_stairs_brute_REC(n - 1) + climbing_stairs_brute_REC(n - 2);
}

int climbing_stairs_memo(int n, vector<int> &memo)
{
    if (n < 2)    return 1;
    if (memo[n] != -1)    return memo[n];
    else    return memo[n] = climbing_stairs_memo(n - 1, memo) + climbing_stairs_memo(n - 2, memo);
}

int climbing_stairs_dp(int n, vector<int> &dp)
{
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++)    dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

/*T(n)=O(n) and S(n)=O(1)*/
int climbing_stairs_fibo(int n)
{
    if (n == 1 || n==2)    return n;

    int first = 1, second = 2;
    int next = 0;
    for (int i = 3; i <= n; i++)
    {
        next = first + second;
        first = second;
        second = next;
    }

    return next;
}
int main()
{
    int n;
    cin >> n;

    int ways_brute = climbing_stairs_brute_REC(n);
    cout << ways_brute << endl;

    vector<int> memo(n + 1, -1);
    int ways_memo = climbing_stairs_memo(n, memo);
    cout << ways_memo << endl;

    vector<int> dp(n + 1, 0);
    int ways_dp = climbing_stairs_dp(n, dp);
    cout << ways_dp << endl;

    /*--------most optimized way---use this---*/
    int ways_fib = climbing_stairs_fibo(n);
    cout << ways_fib << endl;
    /*How to solve this problem if it’s given that one can climb up to K steps at a time?
    If one can climb K steps at a time, try to find all possible combinations from each step from 1 to K. The recursive         
    function would be : climbStairs(N, K) = climbStairs(N – 1, K) + climbStairs(N – 2, K) + … + climbStairs(N – K , K).*/
    
    return 0;
}