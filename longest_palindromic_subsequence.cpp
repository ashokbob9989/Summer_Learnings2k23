#include<bits/stdc++.h>
using namespace std;

/*T(n)=O(n^2) and S(n)=O(n^2)
trick :: say the longest palindromic sebseq in s2 = "xxx" then it is observed that the same paindromic subseq in found in reverse order also.
then as we know the palindrome reads same in front and back so, we reverse the string s1 and store it as s2 and we find the LCS of s1 nd s2. where s1=actual string and s2=reverse of s1 the lCS len is the lpsubseq length */
int longest_palindromic_subsequence_dp(string &s1)
{
    string s2 = s1;
    reverse(s2.begin(), s2.end());
    int n = s1.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i <= n;i++) dp[i][0]=0;
    for (int j = 0; j <= n;j++) dp[0][j]=0;

    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= n;j++)
        {
            if(s1[i-1]==s2[j-1]) dp[i][j]=1+dp[i-1][j-1];
            else dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[n][n];
}
int main()
{
    string s;
    cin >> s;

    int len = longest_palindromic_subsequence_dp(s);
    cout << len << endl;

    return 0;
}