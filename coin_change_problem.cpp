#include <bits/stdc++.h>
using namespace std;

/*The naive approach is to check for every combination of coins for the given sum.
In this approach, we can use recursion to solve this as we have to iterate over all the possible combinations of coins that equal the given sum every time update the minimum no of coins needed to create this sum.*/
/*T(n)=O(2^n) and S(n)=O(1)*/
int coin_change_brute_force(int n, vector<int> &coins, int sum)
{
    if (sum == 0)    return 0;

    int min_needed = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if(coins[i] <= sum )
        {
            int sub_res = coin_change_brute_force(n, coins, sum - coins[i]);
            if (sub_res != INT_MAX and 1 + sub_res < min_needed)    min_needed = 1 + sub_res;
        }
    }

    return min_needed;
}

/*T(n)=O(n*sum) and S(n)=O(n*sum)
                         min( uppervalue, 1+uppervalue-coinsweight_in same row=samerow_but_(uppervalue-coinswt)th col )
        (coins[i]-i\ j(sum)_________
coin_weights->index \ (0) (1) (2) (3)     
     0|0        1                                             2                                             3
(1)  1|0        min(1, 1+(1-1)th=1+(0)th col_val=1+0=1 )->1   min( 2, 1+(2-1)th=1+(1)th col val=1+1=2)=2   min(3,1+2)=3
(2)  2|0        copy_uppervalue coz 2>1..therefore hereval=1  min(2,1+0)=1                                 min(3,1+1)=2
(3)  3|0        copy_same_upper_value coz 3>1 ..value=1       same value upper= 1                          min(3,1+0)=1
*/
int coin_change_DP(int n, vector<int> &coins, int sum)
{
        vector<vector<int>> dp(n + 1, vector<int>(sum + 1, INT_MAX));

        for (int i = 0; i <= n; i++) dp[i][0]=0;/*coins needed to make 0sum with n coins minimum coins needed=0*/

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= sum; j++)
            {
                if (coins[i - 1] > j)    dp[i][j] = dp[i - 1][j];/*upper row and same col value*/
                else if (coins[i - 1] <= j)/*if we can tke weight into consideration*/
                {
                    int take = 1 + dp[i][j - coins[i - 1]];/*1 is added coz we have taken this coin and added sme row and now_sum-this coin weight it gives minimum coins needed which is stored previously for that here_sum-now coin weight.*/
                    int not_take = dp[i - 1][j];/*if we not take*/
                    dp[i][j] = min(take, not_take);/*take min of both*/
                }
            }
        }
        return dp[n][sum];/*resulst will be stored at end of the 2-d matrix*/
}

/*T(n)=O(n*sum) and S(n)=O(sum)*/
int coin_change_DP_Space_opt(int n, vector<int> &coins, int sum)
{
    vector<int> dp(sum + 1, INT_MAX);
    dp[0] = 0;/*to make sum=0 we need 0 coins*/

    for (int i = 1; i <= sum; i++)/*for each sum*/
    {
            for (int j = 0; j < n; j++)/*we see every coin can be added or not*/
            {
                if(coins[j]<=i)/*if we take this coins */
                {
                    int take = 1 + dp[i - coins[j]];/*last calculted value is stored at sum-weight of this coin*/
                    int not_take = dp[i];/*if we not take*/
                    dp[i] = min(take, not_take);
                }
            }
    }
    return dp[sum];
}

int main()
{
    int n;
    cin >> n;

    vector<int> coins(n);
    for (auto &it : coins)    cin >> it;

    int sum;
    cin >> sum;

    int min_coins_needed_brute = coin_change_brute_force(n, coins, sum);
    cout << min_coins_needed_brute << endl;

    int min_coins_needed_DP= coin_change_brute_force(n, coins, sum);
    cout << min_coins_needed_DP << endl;

    /*---------use this coz this is space and time optimized---------------------*/
    int min_coins_needed_DP_Space_opt = coin_change_DP_Space_opt(n, coins, sum);
    cout << min_coins_needed_DP_Space_opt << endl;

    return 0;
}