#include <bits/stdc++.h>
using namespace std;

/*For this approach, we have two cases.
Let’s take the last element and now the sum = target sum – value of ‘last’ element and elements remaining = size of array – 1.
Now  don’t take the ‘last’ element and now the  sum = target sum and elements remaining = size of array – 1.*/
/*Yes, it is an NP-hard problem.*/
/*T(n)=O(2^n) and S(n)=O(1)*/
bool subset_sum_brute_force_REC(int n, vector<int> &v, int sum)
{
    if (sum == 0)    return true; /*we attained the sum is somehow path*/
    if (n == 0)      return false; /*if no element is present in array but we need sum>0 so, not possible*/

    if (v[n - 1] > sum) /*if the element > sum so, we dont take it*/
    {
        bool not_take = subset_sum_brute_force_REC(n - 1, v, sum);
        return not_take;
    }
    else if (v[n - 1] <= sum)
    {
        bool take = subset_sum_brute_force_REC(n - 1, v, sum - v[n - 1]); /*we took so n dec by 1 and sum-its element*/
        bool not_take = subset_sum_brute_force_REC(n - 1, v, sum);        /*we looked for nth element so, now go for n-1 elements*/
        return take || not_take;
    }
}

/*T(n)=O(n*sum) and S(n)=O(n*sum)*/
bool subset_sum_memo(int n, vector<int> &v, int sum, vector<vector<int>> &memo)
{
    if (sum == 0)    return true;
    if (n == 0)      return false;
    if (memo[n - 1][sum] != -1)    return memo[n - 1][sum];

    if (v[n - 1] > sum)
    {
        bool not_take = memo[n - 1][sum];
        return not_take;
    }
    else if (v[n - 1] <= sum)
    {
        bool take = memo[n - 1][sum - v[n - 1]];
        bool not_take = memo[n - 1][sum];
        return memo[n - 1][sum] = take || not_take;
    }
}

/*T(n)=O(n*sum) and S(n)=O(n*sum)*/
bool subset_sum_dp(int n, vector<int>&v, int sum, vector<vector<int>> &dp)
{
    for (int i = 0; i <= n; i++) dp[i][0]=true;/*elements are ample enough but sum==0 then its true we can make*/
    for (int j = 1; j <= sum; j++) dp[0][j]=false;/* no elements but need some sum not possible*/

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            if(v[i-1]>j)
            {
                bool not_take=dp[i-1][j];
                dp[i][j] = not_take;
            }
            else if(v[i-1]<=j)
            {
                bool take = dp[i - 1][j - v[i - 1]];/*take that element*/
                bool not_take = dp[i - 1][j];
                dp[i][j] = take || not_take;
            }
        }
    }

    return dp[n][sum];
}

int main()
{
    int n;
    cin >> n;
    int sum;
    cin >> sum;

    vector<int> v(n);
    for (auto &it : v)    cin >> it;

    bool fg = subset_sum_brute_force_REC(n, v, sum);
    cout << fg << endl;

    vector<vector<int>> memo(n + 1, vector<int>(sum + 1, -1));
    bool fgmemo = subset_sum_memo(n, v, sum, memo);
    cout << fgmemo << endl;

    /*-----------------------use this -------------------------------*/
    vector<vector<int>> dp(n + 1, vector<int>(sum + 1, -1));
    bool fgdp = subset_sum_dp(n, v, sum, dp);
    cout << fgdp << endl;

    return 0;
}