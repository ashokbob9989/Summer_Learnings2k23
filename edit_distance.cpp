#include <bits/stdc++.h>
using namespace std;

/*we place two pointers at the end of the strings say i=s1.size()-1 and j=s2.size()-1
T(n)=O(3^n * 3^m)  and S(n/=O(n+m) */
int edit_distance_brute_force(int i, int j, string &s1, string &s2)
{
    if (i == 0)    return j; /*if s1 is got completed then we need s2's left len*/
    if (j == 0)    return i; /*if s2 is got completed */

    if (s1[i - 1] == s2[j - 1])    return edit_distance_brute_force(i - 1, j - 1, s1, s2); /*if equal go for checking others and dec each len by 1*/
    else
    {
        int for_insert = edit_distance_brute_force(i, j - 1, s1, s2);       /*for insert that is say s1=horse and i is at (e that is 4th pos) we re assuming we inserted "s" after "e" so that s2 gets match thats why (i is not changed and we assumed for jth its matched so, check for left portion in s2 )*/
        int for_delete = edit_distance_brute_force(i - 1, j, s1, s2);       /* for delete say s1=horse and i is at 4th pos we assumed after deleting 4th pos ( now string is hors so we assumed with jth pos its matched so, check for others)*/
        int for_replace = edit_distance_brute_force(i - 1, j - 1, s1, s2);  /* for replace .. we asummed we placed both string's pos as same char so, need to go for others now*/
        int tot_needed = 1 + min(for_insert, min(for_delete, for_replace)); /*we assumed above from 3 types of operations we performed anyone (i.e insert/delete/replace so for that reason we need to add +1 operation into count) and minimum among all 3.*/
        return tot_needed;
    }
}

/*T(n)=O(n*m) and S(n)=O(n*m)*/
int edit_distance_memo_top_down(int i, int j, string &s1, string &s2, vector<vector<int>> &memo)
{
    if (i == 0)    return j;
    if (j == 0)    return i;
    if (memo[i][j] != -1)    return memo[i][j]; /*if alredy stored just return that soln*/

    if (s1[i - 1] == s2[j - 1])    return memo[i][j] = edit_distance_memo_top_down(i - 1, j - 1, s1, s2, memo);
    else
    {
        int for_insert = edit_distance_memo_top_down(i, j - 1, s1, s2, memo);
        int for_delete = edit_distance_memo_top_down(i - 1, j, s1, s2, memo);
        int for_replace = edit_distance_memo_top_down(i - 1, j - 1, s1, s2, memo);

        int tot_needed = 1 + min(for_insert, min(for_delete, for_replace));

        return memo[i][j] = tot_needed;
    }
}

int edit_distance_DP_bottom_up(int n, int m, string &s1, string &s2, vector<vector<int>> &dp)
{
    for (int i = 0; i <= n; i++)    dp[i][0] = i;/*same logic.. if j=0 then we need i len to make them equal*/
    for (int j = 0; j <= m; j++)    dp[0][j] = j;/*if i=0 then we need j len to make them equal*/

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1];/*copy the diagonal value*/
            else
            {
                int for_insert = dp[i][j - 1];
                int for_delete = dp[i - 1][j];
                int for_replace = dp[i - 1][j - 1];

                int tot_needed = 1 + min(for_insert, min(for_delete, for_replace));

                dp[i][j] = tot_needed;
            }
        }
    }

    return dp[n][m];
}

int edit_distance_space_opt_bottom_up(int n, int m, string &s1, string &s2)
{
    vector<int> prev(m + 1, 0);/*note :: prev=dp[i-1]*/
    vector<int> curr(m + 1, 0);/*note :: curr= dp[i]*/

    for (int j = 0; j <= m; j++) prev[j]=j;

    for (int i = 1; i <= n; i++)
    {
        curr[0] = i;
        for (int j = 1; j <= m; j++)
        {
            if(s1[i-1]==s2[j-1]) curr[j]=prev[j-1];
            else
            {
                int for_insert = curr[j - 1];
                int for_delete = prev[j];
                int for_replace = prev[j - 1];

                int tot_needed = 1 + min(for_insert, min(for_delete, for_replace));
                curr[j] = tot_needed;
            }
        }
        prev = curr;
    }
    return prev[m];/*we are returning this prev[m] insetad of curr[m] coz if s1==empty and s2!=empty then prev will stores the values not curr..*/
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;

    int n = s1.size();
    int m = s2.size();
    int min_operations_need_to_change_s1_to_s2 = edit_distance_brute_force(n - 1, m - 1, s1, s2); /*passed n-1, m-1 coz handling with 0based*/
    cout << min_operations_need_to_change_s1_to_s2 << endl;

    vector<vector<int>> memo(n, vector<int>(m, -1));
    int min_oprns_need_using_dp = edit_distance_memo_top_down(n - 1, m - 1, s1, s2, memo); /*0based so, passed n-1,m-1*/
    cout << min_oprns_need_using_dp << endl;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); /*1based*/
    int sol = edit_distance_DP_bottom_up(n, m, s1, s2, dp);
    cout << sol << endl;

    /*----------------------most optimal and space optimized code use this one --------------------*/
    int optsol = edit_distance_space_opt_bottom_up(n, m, s1, s2);
    cout << optsol << endl;

    return 0;
    
}