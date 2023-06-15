#include<bits/stdc++.h>
using namespace std;

/*this is same as LCS problem but here we dont consider the same index chars thats it.
T(n)=O(n^2) and S(n)=O(n^2)*/
int LRS(string &s1)
{
    string s2 = s1;
    int n = s1.size();

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= n;i++) dp[i][0]=0;
    for (int j = 0; j <= n;j++) dp[0][j]=0;

    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= n;j++)
        {
            if(s1[i-1]==s2[j-1] && i-1 != j-1) dp[i][j]= 1+dp[i-1][j-1];
            else dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[n][n];
}

int main()
{
    string s; cin >> s;
    int len = LRS(s);
    cout << len << endl;

    return 0;
}