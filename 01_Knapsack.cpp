#include <bits/stdc++.h>
using namespace std;

/*Our approach with recursion will be to try and create all the subsets of items with total weight less than that of the given capacity W. From the result we will return the subset with maximum value.
For every element we can, either select it or, ignore and move forward.
If we select an item then its value will be added to our current value and weight will be subtracted from the current available space.
Thus, if we take the maximum value out of both the calculated result for nth element i.e. result after selecting that element and after ignoring it, we can get to our desired answer. */
/*T(n)=O(2^n) if tack_space is considered S(n)=O(n) else S(n)=O(1)*/
int Knapsack_Brute_REC(int W, int N, vector<int> &v, vector<int> &w) 
{
    /*if the bag is of 0capacity or no items left*/
    if (N == 0 || W == 0)    return 0;

    /*if the weight can be accommodated in the bag then we have two choices take/not_take*/
    if (w[N] <= W)
    {
        int take = v[N] + Knapsack_Brute_REC(W - w[N], N - 1, v, w); /*take-> so, value has to be added*/
        int not_take = Knapsack_Brute_REC(W, N - 1, v, w);           /*not_take->value is not added, we done for this ith call for i-1th now*/
        return max(take, not_take);                                  /*take max values of both*/
    }
    else if (w[N] > W) /*if weight is greater so, we dont need this(not_tke case)*/
    {
        int not_take = Knapsack_Brute_REC(W, N - 1, v, w);
        return not_take;
    }
}

/*In this approach we’ll store all the computed answers in a 2 dimensional Array with indices  of items in rows and weights in columns and use it further for overlapping subproblems.*/
/*T(n)=O(N*W). S(n)=O(N*W).*/
int Knapsack_Memoization_REC(int W, int N, vector<int> &v, vector<int> &w, vector<vector<int>> &memo)
{
    if (W == 0 || N == 0)    return 0;
    if (memo[N][W] != -1)    return memo[N][W];

    if (w[N] <= W)
    {
        int take = v[N] + Knapsack_Memoization_REC(W - w[N], N - 1, v, w, memo);
        int not_take = Knapsack_Memoization_REC(W, N - 1, v, w, memo);
        memo[N][W] = max(take, not_take);
        return memo[N][W];
    }
    else if (w[N] > W)
    {
        int not_take = Knapsack_Memoization_REC(W, N - 1, v, w, memo);
        memo[N][W] = not_take;
        return memo[N][W];
    }
}

/*In this approach we’ll define 2 dimensional DP of index for items defined on rows whereas weights from 1 to W on columns and for every weight we can compute the answer for placing items till nth item.
DP[i][j] = max(v[i-1] + DP[i-1][j-w[i-1]],DP[i-1][j])->last taken value is at (i-1,j-w[i-1]) postion in 2-d arry and not taken is at (i-1,j)....the result will be at [N][W] position in 2-d array*/
/*T(n)=O(N*W). S(n)=O(N*W)*/
int Knapsack_Tabulation_Iterative(int W, int N, vector<int> &v, vector<int> &w, vector<vector<int>> &dp)
{
    for (int i = 0; i <= N; i++) dp[i][0]=0;/*these two stepssame as N==0 || W==0 then 0.*/
    for (int j = 0; j <= W; j++) dp[0][j]=0;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if(w[i-1]<=j)/*if w[N]<=W where in 2-d array the value is at (i-1)th position actully 0based indexing*/
            {
                int take = v[i - 1] + dp[i - 1][j - w[i - 1]];/*for the same position in actual arrays..like if i-1=0 then in "v" array 0th position and "w" array 0th position if this weight is taken the add value(which is at pos=i-1) and subtract its weight(which is at pos=i-1) from total weight till it.*/
                int not_take = dp[i - 1][j];/*not taken so, no need to subtract weight of current item*/
                dp[i][j] = max(take, not_take);
            }
            else if(w[i-1]>j)
            {
                int not_take = dp[i - 1][j];
                dp[i][j] = not_take;
            }
        }
    }
    return dp[N][W];
}

/*In the above approach we used a 2D array to store the computed results in our DP but we can observe one thing that to compute the result for the nth element we just need the results for the (n-1)th element thus we do not need the rest of the result.Thus we can reduce the size of our DP to 1D just storing the results on different weights till the previous element.*/
/*T(n)=O(N*W)  S(n)=O(W)*/
int Knapsack_Tabulation_Iterative_Space_opt(int W, int N, vector<int> &v, vector<int> &w, vector<int>&dpSpace_opt)
{
    for (int j = 0; j <= W; j++) dpSpace_opt[j]=0;

    for (int i = 1; i <= N; i++)
    {
        for (int j = W; j >= w[i - 1]; j--)
        {
            int take = v[i - 1] + dpSpace_opt[j - w[i - 1]];
            int not_take = dpSpace_opt[j];
            dpSpace_opt[j] = max(take, not_take);
        }
    }
    return dpSpace_opt[W];
}

int32_t main()
{
    int W, N;
    cin >> W >> N;

    vector<int> v(N), w(N);
    for (auto &it : v)    cin >> it;
    for (auto &it : w)    cin >> it;

    cout << Knapsack_Brute_REC(W, N, v, w) << endl;

    vector<vector<int>> memo(N + 1, vector<int>(W + 1, -1));
    cout << Knapsack_Memoization_REC(W, N - 1, v, w, memo) << endl;/*note that N-1 did coz in main array out last index(0 indexed is at N-1 position)*/
    /*debug*/
    //for(auto &it : memo){for(auto &it2 : it)cout<<it2<<" ";cout<<endl;}

    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));
    cout << Knapsack_Tabulation_Iterative(W, N, v, w, dp) << endl;
    /*debug*/
    //for(auto &it : dp){for(auto &it2 : it)cout<<it2<<" ";cout<<endl;}

    /*---------------Use This One which is more optimized------------------------------------*/
    vector<int> dpSpace_opt(W + 1,0);
    cout << Knapsack_Tabulation_Iterative_Space_opt(W, N, v, w, dpSpace_opt) << endl;
    /*debug*/
    //for(auto &it : dpSpace_opt) cout<<it<<" ";

    return 0;

}