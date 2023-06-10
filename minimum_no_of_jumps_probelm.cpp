#include <bits/stdc++.h>
using namespace std;

/*A simple approach to solve this problem is to start from the first element of the array and recursively travel to all elements that are reachable from that element. Similarly, recursively travel to all other elements and find the minimum jumps to reach the end of the array.*/
/*T(n)=O(n^n) and S(n)=O(1)*/
int minimum_no_of_jumps_req_brute_force(int currpos, int n, vector<int> &lens)
{
    if (currpos >= n - 1)    return 0;

    int min_jumps_req = INT_MAX;
    int start_val = lens[currpos];
    while (start_val > 0)
    {
        /*[2, 3, 1, 1, 4] and sol=2.. pth from 2->3 move =1 and 3->4 moves=1+1=2*/
        /*we iterate from all posibilities from that point nd next fro other element ... so on nd we take min from them*/
        min_jumps_req = min(min_jumps_req, 1 + minimum_no_of_jumps_req_brute_force(currpos + start_val, n, lens));
        start_val--;
    }

    return min_jumps_req;
}

/*T(n)=O(n^2) and S(n)=O(n)*/
int minimum_jumps_dp(int n, vector<int> &lens)
{
    vector<int> dp(n, INT_MAX);
    dp[0] = 0; /*to each 0th index from the 0th posotion we want 0moves*/

    for (int i = 0; i < n; i++) /*lens elements*/
    {
        for (int j = i + 1; j < min(i + lens[i] + 1, n); j++) /*if we are at position i, the maximum one can jump is (i,  i + lens[i]).*/
        {
            int take = 1 + dp[i]; /*we took a jump so add +1 to the previous jumps*/
            int not_take = dp[j]; /*not taken */
            dp[j] = min(take, not_take);
        }
    }

    return dp[n - 1];
}

/*
say lens :: 2 3 1 1 4
initially we are 0th pos -> ele=2
jumps=1, steps=2,maxreach=2
for i=1 to <=n-1 
   when i=1->  i==n-1 (NO) maxreach=max(2,1+3)=4, steps=1, steps==0(NO)
   when i=2->  i==n-1 (NO) maxreach=max(4,2+1)=4, steps=0, steps==0(YES) so, jumps=jumps+1, so now jumps=1+1=2, steps=maxreach-i=4-2=2
   when i=3->  i==n-1 (NO) maxreach=max(4,3+1)=4, steps=1, steps==0(NO)
   when i=4->  i==n-1 (YES)return jumps=2 
*/
/*T(n)=O(n) and s(n)=O(1)*/
int minimum_jumps_greedy(int n, vector<int> &lens)
{
    if(n<=1)         return 0; /*if array contains 1 element or NO elemets then  jumps=0*/
    if(lens[0]==0)   return -1; /*we are at 0th position and we cant make move from 0th positio coz jumps we can make from that pos=0*/
    if(lens[0]>=n-1) return 1;/*if we have 4 1 2 then it is obvious that with the first jump we can mke at max 4 jumps so, direct we can reach at last index indeed, so need only one jump*/

    int jumps = 1, steps = lens[0], maxreach = lens[0];/*we are at 0th pos in array we can maxrch lens[0] from that psoition and we are ledt with lens[0] steps initilly and we assumed we jumped from 0th to 1st pos so jumps=1*/

    /*we strt our traversing from 1st pos*/
    for (int i = 1; i < n; i++)
    {
        if(i==n-1) return jumps; /*we reached to end*/

        maxreach = max(maxreach, i + lens[i]);/*with the current index the max postion we can reach = i+lens[i]*/
        /*we used one step from this current index so dec by 1*/
        if(maxreach>=n-1) return jumps+1;/*if we have more jumps than the left indices we need to visit so with just one more jump from this step to last step we can reach end eg :: 1 2 8 3 if we are at 2nd pos that is =8 then we can mke 8 steps from that pos so, previous jumps+1(for this long jump) return it.*/

        steps--;

        if(steps==0) 
        {
            if(i>=maxreach) return -1;/*if we have 0valued elements in between path(from that point we have only 0jumps) then -1*/

            jumps++;
            steps = maxreach - i;/*those previous steps re completed so, for next steps we have = mxreach-its posotion, this many steps we can make further*/
        }
    }
    return -1;/*cant reach the last index*/
}

int main()
{
    int n;
    cin >> n;

    vector<int> lens(n);
    for (auto &it : lens)    cin >> it;

    int jumps_req_brute = minimum_no_of_jumps_req_brute_force(0, n, lens);
    cout << jumps_req_brute << endl;

    int jumps_req_dp = minimum_jumps_dp(n, lens);
    cout << jumps_req_dp << endl;

    /*--------use this one most optimal----------------*/
    int jumps_req_greedy = minimum_jumps_greedy(n, lens);
    cout << jumps_req_greedy << endl;

}