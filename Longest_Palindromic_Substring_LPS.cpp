#include<bits/stdc++.h>
using namespace std;

/*The brute force solution which comes into our mind is to pick all the substrings from a string that is possible and then we will check whether that substring is a palindrome or not.
T(n)=O(n^3) and S(n)=O(1)*/
pair<int,int> longest_palindromic_substring_brute(string &s)
{
    int n = s.length();
    int start = 0, maxlen = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            bool fg = 1;
            int sublen = j - i + 1;/*note endind pos at j*/
            for (int k = 0; k < (sublen) / 2; k++) if(s[i+k]!=s[j-k]){fg=0;break;}

            if(fg==1 && sublen>maxlen) {start=i; maxlen=sublen;}
        }
    }
    return {start,maxlen};
}

/*Consider one example “cbebc”. If we already knew that “beb” is a palindrome, it is obvious that “cbebc” must be a palindrome since the two left and right end letters are the same.
so, we define dp[i][j]= (s[i]==s[j] and  dp[i+1][j-1]) if yes we assign true else false
cbebc -> say i=0 and j=4 so, s[0]==s[4] and dp[i+1(that from 1st index)][j-1(till 3rd index)] it ws alreday stored true so here also assign true for dp[i][j]

important : we fill values as diagonal not in first row then second(X) we fill in \[in this diagonal fashion]
                                                                                   \
eg :: a   b                               c                              c       b        c
     (a) (ab)                           (abc)                          (abcc) (abccb)  (abccbc)
    a 1  (len=1 a!=b,sol=0)  (len=2 a!=c,from i+1->j-1 not pali sol=0)   0       0          0
    b     1(b)                            (bc)                          (bcc)    (bccb)    (bccbc)
    c                                      1
    c                                                                    1
    b                                                                             1
    c                                                                                        1
*/
pair<int,int> longest_palindromic_substring_dp(string &s)
{
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int start = 0, maxlen = 0;
    /*note i=0,j=0 gap=0 ..  i=0, j=2 gap=2 like this... it is like where the new sybstr starts and where it ends */
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)/*from startwe genertae substr's then if we already know in between are palindrome and we are now with i, j new chrs if they re also equal then true else false at that (i,j) pos in dp*/
        {
            if(gap==0)dp[i][j]=true;
            else if(gap==1) dp[i][j]= (s[i]==s[j]) ? 1 : 0;
            else dp[i][j]= (s[i]==s[j] && dp[i+1][j-1]==true) ? 1 : 0;

            if(dp[i][j]==true)
            {
                start = i;
                maxlen = j - i + 1;/*note ending pos j*/
            }
        }
    }
    return {start, maxlen};
}



/*eg :: s=abccbc 
i=0 we get maxlen=1 and sol="a" for odd and even check 
i=1 for odd check only b is passed so, b==b then a!=c so we get sol="b" and maxlen=1
    for odd check bc are passed so, b!=c sol="b" and maxlen=1
i=2 for odd check only c is passed so, c==c then b!=c so weget sol="c" and maxlen=1
    for even check cc are passedso, c==c sol="cc" and maxlen=2 ... then l--,r++ we are at 1st pos and 4th pos again b==b sol="bccb" and mxlen=4
..... till end pos we check all this nd we return "bccb" as sol*/
/*T(n)=O(n^2) and S(n)=O(1)*/
int start = 0, maxlen = 1;
string sol = "";
pair<int,int> lpsevenodds(string &s,int l, int r)
{
    while( l>=0 && r<s.length() && (s[l]==s[r]) ) {l--;r++;}

    if(r-l-1>=maxlen) { sol=s.substr(l+1,r-l-1); start=l+1; maxlen=r-l-1; }
    /*note :: we are doinf r-l-1 coz we break the palindrome check bond just left and just right to the actual palindrome erlier seq say
              "abccbc"  .. for i=2 [in the odd palindrome check function[we passed c,c] we reach l=0 and r=5 which is a!=c therefore here dist= r-l+1 -2(this 2 is for the (l,r)th chars currently  ) therfore overall dist= r-l+1-2= r-l-1 which is 5-0-1=4 
              and palindrome starts at l+1 and ends at r-1 with len=r-l-1*/
}
pair<int,int> longest_palindromic_substring_centre_expand(string &s)
{

    int n = s.length();

    if(n==0) return {0,0};

    for (int i = 0; i < n; i++)
    {
        lpsevenodds(s, i, i);    /*for odd length palindrome*/
        lpsevenodds(s, i, i + 1);/*for even length palindrome*/
    }

    return {start, maxlen};
}
int main()
{
    string s;
    cin >> s;

    pair<int, int> Start_Maxlen = longest_palindromic_substring_brute(s);
    cout << Start_Maxlen.first << " " << Start_Maxlen.second << endl;

    pair<int, int> Start_Maxlen_dp = longest_palindromic_substring_dp(s);
    cout << Start_Maxlen_dp.first << " " << Start_Maxlen_dp.second << endl;

    /*-----------------use this most optimized way----------------------------------------*/
    pair<int, int> Start_Maxlen_centre_expand = longest_palindromic_substring_centre_expand(s);
    cout << Start_Maxlen_centre_expand.first << " " << Start_Maxlen_centre_expand.second << endl;

    return 0;

}
