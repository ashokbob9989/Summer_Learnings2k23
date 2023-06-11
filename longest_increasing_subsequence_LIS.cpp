#include<bits/stdc++.h>
using namespace std;
/*we start from every index and calculate what is the max lis value we get if we start from that index
eg :: 5 4 1 2 3 if we are at index=4 the we start checking from 3rd index v[3]<v[4] yes sol=1+next calculation recursive  
v[2]<v[3] yes sol=2+next v[1]<v[2] no  i==0 yes so, return 1.. overall sol=1+1+(index==0 thats why +1) =3
array :: |5|4|1|2|3| 
         +-+-+-+-+-+
LIS   :: |1|1|1|2|3|

T(n)=O(2^n) and S(n)=O(n) for stack space in recusrion ...if it is not considerred then O(1)*/
int lis_brute_force(vector<int> &v, int ind)
{
    if(ind==0) return 1;

    int sol = 1;
    for (int i = 0; i < ind; i++)
    {
        if( v[i] < v[ind] )
        {
            sol = max(sol, 1 + lis_brute_force(v, i));
        }
    }
    return sol;
}

/*T(n)=O(n^2) and S(n)=O(n)*/
int lis_dp(vector<int> &v, int n)
{
    vector<int> dp(n, 1);/*till 0th index lis value-> ? .... till (n-1)th index lis=?..therfore dp_state=dp[i]->max lis till that ith index*/

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if(v[j]<v[i] && dp[i]<1+dp[j])
            {
                dp[i] = 1 + dp[j];
            }
        }
    }
    /*dng*/
    // for(auto &it : dp) cout<<it<<" ";
    // cout << endl;
    return *max_element(dp.begin(),dp.end());
}

/*T(n)=O(nlg(n)) and S(n)=O(n)*/
int lis_binary_search(vector<int> &v, int n)
{
    vector<int> lis;
    lis.push_back(v[0]);

    for (int i = 1; i < n; i++)
    {
        if( v[i] > lis.back() ) lis.push_back(v[i]);
        else if( v[i] <= lis.back() )
        {
            /*lower_bound of a number saay x returns position of x in the array if "x" is present else returns just next_greter numeber in the array say :: 5 3 4 3 1 then lower_bound of 4 will be 2nd pos whereas lower_bound of 2 will be 0th pos coz this is the first element in the array which is just greater than the current x */
            /*upper_bound if the number is present/not present dont care we just return the index which is just greater than the current value eg:: upper_bound  of 3 wil be index=2 (ele=4)*/
            int pos = lower_bound(lis.begin(), lis.end(), v[i]) - lis.begin();
            lis[pos] = v[i];
        }
    }
    return lis.size();
}

int main()
{
    int n; cin>>n;

    vector<int> v(n);
    for(auto &it : v) cin>>it;

    int sol_brute = 1;/*coz max ans can be 1 the element itself is a subsequence*/
    for (int i = 0; i < n; i++)
    {
        sol_brute = max(sol_brute, lis_brute_force(v, i));
        /*dbg*/
        //cout << sol_brute << endl;
    }
    cout << sol_brute << endl;


    int sol_dp = lis_dp(v, n);
    cout << sol_dp << endl;

    /*---effectice approach using binary search----use this one*/
    int sol_bs = lis_binary_search(v,n);
    cout << sol_bs << endl;
    
    return 0;

}