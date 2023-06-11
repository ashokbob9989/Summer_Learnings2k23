#include<bits/stdc++.h>
using namespace std;

/*we start from its length and see if the iterator's value is equal then inc ans by 1 else recursively call the function once by includeing the last element in s1 and excluding last element in s2 and vice versa*/
/*T(n)=O(2^(n+m)) nd S(n)=O(1)excluding stack space*/
int lcs_brute_REC(string &s1, string &s2, int i, int j)
{
    if(i==0 || j==0) return 0;
    if(s1[i-1]==s2[j-1]) return 1+lcs_brute_REC(s1,s2,i-1,j-1);
    else return max(lcs_brute_REC(s1,s2,i-1,j),lcs_brute_REC(s1,s2,i,j-1));
}

/*T(n)=O(n*m) nd S(n)=O(n*m)*/
int lcs_memo(string &s1, string &s2, int i, int j, vector<vector<int>>&memo)
{
    if(i==0 || j==0) return 0;
    if(memo[i][j]!=-1) return memo[i][j];
    if(s1[i-1]==s2[j-1]) return memo[i][j]=1+lcs_memo(s1,s2,i-1,j-1,memo);
    else return memo[i][j]=max(lcs_memo(s1,s2,i-1,j,memo),lcs_memo(s1,s2,i,j-1,memo));
}

/*T(n)=O(n*m) nd S(n)=O(n*m)*/
int lcs_dp(string &s1, string &s2, int n, int m, vector<vector<int>>&dp)
{
    for (int i = 0; i <= n; i++) dp[i][0]=0;
    for (int j = 0; j <= m; j++) dp[0][j]=0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if(s1[i-1]==s2[j-1]) dp[i][j]=1+dp[i-1][j-1];
            else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    return dp[n][m];
}
int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    int n = s1.length();
    int m = s2.length();
    int lcs_len_brute = lcs_brute_REC(s1, s2, n, m);
    cout << lcs_len_brute << endl;

    vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
    int lcs_len_memo = lcs_memo(s1, s2, n, m, memo);
    cout << lcs_len_memo << endl;

    /*--- use this approach which is optimal -----------*/
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int lcs_len_dp = lcs_dp(s1, s2, n, m, dp);
    cout << lcs_len_dp << endl;

    return 0;
}