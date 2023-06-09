#include<bits/stdc++.h>
using namespace std;

/*The most basic approach to solve this problem is to simply use recursion and backtracking. The key idea is to check every possible prefix of the given string in the dictionary of words. If the prefix is found in the dictionary of words, run the recursive function for the rest of the string and at any point if the whole string is found, simply return True.*/
/*T(n)=O(2^n) .. S(n)=O(n)*/
bool word_break_brute_force_REC(string &s, set<string> &words, int i)
{
    if(i==s.length())return true;/*if we reach till end succesfully*/
    else
    {
        for (int j = i + 1; j <= s.length(); j++)/*generate the prefix strings*/
        {
            if( words.find( s.substr(i, j-i) )!= words.end() && word_break_brute_force_REC(s, words, j)) return true;
            /*if the prefix is found in set then go for next prefix*/
        }
        return false;/*if no way we havent reach the end of the string so, not possible*/
    }
}

/*T(n)=O(N^3) and S(n)=O(N), where N is the length of the given string.
How can you calculate the number of different possible words that can be constructed from the given string?
Following the dynamic programming approach discussed above, instead of making dp[i] = true, add dp[[j – 1] with dp[i] for j > 0. At the end, return dp[N].*/
bool word_break_DP(string &s, set<string> &words)
{
    int n = s.size();/*length of the string*/
    vector<bool> dp(n+1);/*if we found true for len=1 le=2 ... if len=n is true then ans=true */
    dp[0] = true;/* len=0 obviously true*/

    for (int i = 1; i <= n; i++)/*for len=1, len2,..... till len=n*/
    {
        for (int j = 0; j <= i; j++)/*substring from 0th to till ith position*/
        {
            if( dp[j]==true and words.find(s.substr(j, i-j)) != words.end() )/*if that len=true and if we found that substr in dictionay then for len=mark true*/
            {
                dp[i]=true;
                break;/*....mark true for that len then go for next...*/
            }
        }
    }

    /*debug*/
    // for(auto it : dp) cout<<it<<" ";
    // cout << endl;
    
    return dp[n];/*....if for len=n true then return true....*/
}

/*T(n)=O(n^2) and S(n)=O(n)
eg :: s=applepenapple and words=apple, pen 
here we get dp as 0 1 2 3 4 0 1 2 0 1 2 3 4 0
                  here the value=0 indicates the length at which the substr is found say 5th position in dp is "0" right? so, in the main string we can see from (0->4)th index the dictionaty string is found in main string
                  again 8th pos=0 so, in th main string till 7 index we found the dic strings.... so, on so forth if till "n" length if we get ==0 in dp tht signifies our main string is whole found in dictionary. so, if(dp[n]==0 the yes else no.)*/
string word_break_opt(string s, vector<string>&dic)
{
    int n=s.size();
    unordered_set<string>words;/*used this ds coz for find function it uses only O(1) time complexity*/
    for(auto &it : dic)words.insert(it);
    vector<int>dp(n+1,0);
    
    for(int i=1;i<=n;i++)
    {
        dp[i]=1+dp[i-1];
        for(int j=max(1,i-19);j<=i;j++)/*note here we did max(1,i-19) coz in qn they mentioned maxlen of dictionaty word=20 so, we did (i-19) for general case if they mention dictionary maxlen is "m" then run j loop from max(1, i-m) till <=i*/
        {
            string sub=s.substr(j-1,i-j+1);
            if(words.find(sub)!=words.end()) dp[i]=min(dp[i],dp[j-1]);
        }
    }
    /*dbg*/
    // for(auto &it : dp) cout<<it<<" ";
    // cout << endl;

    return dp[n]==0 ? "YES" : "NO";
}

int main()
{
    string s;
    cin >> s;

    int n;
    cin >> n;
    vector<string> dictionary(n);
    for(auto &it : dictionary) cin>>it;

    // set<string> words(dictionary.begin(), dictionary.end());

    // bool fg = 0;
    // int i = 0;/*i= starting index of the string*/
    // fg = word_break_brute_force_REC(s, words, i);
    // if(fg==1)cout<<"YES"<<endl;
    // else cout<<"NO"<<endl;

    // fg = 0;
    // fg = word_break_DP(s, words);
    // if(fg==1)cout<<"YES"<<endl;
    // else cout<<"NO"<<endl;

    /*------use this most efficient--------*/
    string fgopt = word_break_opt(s, dictionary);
    cout << fgopt << endl;
    
    return 0;
}
