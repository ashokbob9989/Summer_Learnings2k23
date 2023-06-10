#include <bits/stdc++.h>
using namespace std;

/*The problem can be solved with recursion by considering the choices we have for the nth person. For the nth person,
The nth person stays single or unpaired, and we recurse for the remaining n – 1 people.
Nth person pairs up with any for the remaining n – 1 people. The number of ways of doing this (n – 1) * Rec(n – 2).*/
/*The recurrence can then be written as: Rec(n) = Rec(n – 1) + (n – 1) * Rec(n – 2)
Base Case: Note that if there are 2 friends, there are 2 ways to arrange them, and for a single friend, there is only 1 way to arrange them. So for n <= 2, the answer will be n.*/
/*T(n)=O(2^n) and S(n)=O(1)*/
int friends_pairing_brute_force_REC(int n)
{
    if (n <= 2)    return n; /*pairing only 1 person or 2 persons(both stays single 1 way or both get paired 2nd way) ways = itself*/
    else
    {
        int single = friends_pairing_brute_force_REC(n - 1);/*nth person stays single so, do calculate for n-1 persons*/
        int paired = (n - 1) * friends_pairing_brute_force_REC(n - 2);/*nth person gets paired with out of n-1 persons so, now clculate for n-2 persons*/
        return single + paired;/*add all the wys*/
    }
}

/*T(n)=O(n) and S(n)=O(n)*/
int friends_pairing_memo(int n, vector<int> &memo)
{
    if(n<=2) return memo[n]=n;/*pairing <=2 persons is n itself*/
    if( memo[n] != -1) return memo[n];/*if alreday done calculating for this many persons*/
    else
    {
        int single = friends_pairing_memo(n - 1, memo);
        int paired = (n - 1) * friends_pairing_memo(n - 2, memo);
        return memo[n] = single + paired;
    }
}

/*T(n)=O(n) and S(n)=O(n)*/
int friends_pairing_dp(int n, vector<int>&dp)
{
    for (int i = 0; i <= n; i++)
    {
        if(i<=2) dp[i]=i;
        else
        {
            int single = dp[i - 1];
            int paired = (i - 1) * dp[i - 2];
            dp[i] = single + paired;
        }
    }
    return dp[n];
}

/*Combinatorics Based Approach
The problem given is basically equivalent to the combinatorial problem of “In how many ways can we divide a total of n items into multiple groups (maximum group size here being 2).” This problem is solved by the following formula:image.png*/
/*formula as :: (n!) / ((grp1)^x * (grp2)^y......* (grpn)^z) * (x! * y! ....* z!)*/
/*T(n)=O(n) and S(n)=O(n)*/
int friends_pairing_combinations_methos(int n)
{
    vector<int> fact(n + 1);
    fact[0] = 1;

    for (int i = 1; i <= n; i++) fact[i]=fact[i-1]*i;
    int grp1 = n;
    int grp2 = 1;
    int sol = 0;

    while(grp1>=0)
    {
        sol += fact[n] / (grp2 * fact[grp1] * fact[(n - grp1) / 2]);
        grp1 -= 2;
        grp2 *= 2;
    }
    return sol;
}
int main()
{
    int n;
    cin >> n;

    int sol_brute = friends_pairing_brute_force_REC(n);
    cout << sol_brute << endl;

    vector<int> memo(n + 1, -1);/*to make one based coz say n=4 then our ans has to be stored at 4th place*/
    int sol_memo = friends_pairing_memo(n, memo);
    cout << sol_memo << endl;

    vector<int> dp(n + 1, -1);
    int sol_dp = friends_pairing_dp(n, dp);
    cout << sol_dp << endl;

    int sol_with_combs = friends_pairing_combinations_methos(n);
    cout << sol_with_combs << endl;

    return 0;
}