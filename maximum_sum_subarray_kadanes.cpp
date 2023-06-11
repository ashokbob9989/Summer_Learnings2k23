#include<bits/stdc++.h>
using namespace std;

/*T(n)=O(n^3) and S(n)=O(1)*/
int subarray_sum_brute(vector<int>&v, int n)
{
    if(n==0) return 0;
    int sol = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int currsum = 0;
            for (int k = i; k <= j; k++)
            {
                currsum += v[k];
            }
            sol = max(sol, currsum);
        }
    }
    return sol;
}

/*store the running sum at all possible positions
T(n)=O(n^2) and S(n)=O(1)*/
int subarray_sum_brute_2nd_way(vector<int>&v, int n)
{
    if(n==0) return 0;
    int sol = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int curr_sum = 0;
        for (int j = i; j < n; j++)
        {
            curr_sum += v[j];
            sol = max(sol, curr_sum);
        }
    }
    return sol;
}

/*dp state = ending at index i the max sum is dp[i]
recurrence realation will be :: dp[i]=max( dp[i-1]+v[i], v[i] ) and we return max in dp array
T(n)=O(n) and S(n)=O(n)*/
int subarray_sum_dp(vector<int>&v, int n)
{
    if(n==0) return 0;

    vector<int> dp(n, 0);
    dp[0] = v[0];

    for (int i = 1; i < n; i++) dp[i]=max(dp[i-1]+v[i], v[i]);
    return *max_element(dp.begin(),dp.end());
}

/*T(n)=O(n) and S(n)=O(1)*/
int subarray_sum_kadanes(vector<int>&v, int n)
{
    if(n==0) return 0;
    int maxsum = INT_MIN;
    int currsum = 0;

    for (int i = 0; i < n; i++)
    {
        currsum += v[i];
        if(currsum>maxsum) maxsum=currsum;
        if(currsum<0) currsum=0;/*if we get -ve sum then it will not contribute for the next subrray.. coz if we include we have choices that our total sum will get decreased*/
    }
    return maxsum;
}

int main()
{
    int n; cin>>n;
    vector < int>v(n);
    for(auto &it : v) cin>>it;

    int sum_brute = subarray_sum_brute(v, n);
    cout << sum_brute << endl;

    int sum_brute_2nd = subarray_sum_brute_2nd_way(v, n);
    cout << sum_brute_2nd << endl;

    int sum_dp = subarray_sum_dp(v, n);
    cout << sum_dp << endl;

    /*--------effective approach KADANES ALGORITHM-use this----------*/
    int sum_kadanes = subarray_sum_kadanes(v, n);
    cout << sum_kadanes << endl;

    return 0;

}