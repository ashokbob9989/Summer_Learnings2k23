#include<bits/stdc++.h>
using namespace std;

/*say :: n=6, k=3 and lens=10,20,60,50,30,40 for i=1 to <=n we make partition between { lens[i-1] | lens[i] }so, we make a partition that means we allocated a painter for this portion so, we reduce k by 1 (i.e k=k-1)and we recursively call the another portion for the answer... 
say k=3
1)assumed (k-1) partitions are made using (k-2)dividers eg :: ...|...  with one | we can make 2 partitions
2)now  we have to put (k-1)th divider somehwhere to get (k) partitions eg :: ...|....|... with 2|| we can mke 3 partitions
3)we place (k-1)th divider between (i-1) and (i)th element*/

/*T(n)=O(2^n) and S(n)=O(1) If recursion stack space is ignored*/
/*RECursion tree 
      (4,3)
     /  |   \
    /   |    \
(1,2) (2,2)  (3,2)
        |     /   \
      (1,1)  (2,1) (1,1)*/
int getsum(vector<int> &lens, int st, int en)
{
    int sum = 0;
    for (int i = st; i <= en; i++) sum+=lens[i];
    return sum;
}
int painters_partition_brute_REC(vector<int> &lens, int n, int k)
{
    if(k==1) return getsum(lens,0,n-1);/*if only one painter is there then he takes min sum_array time*/
    if(n==1)
        return lens[0]; /*if only one painting is there then he need this lens[0] time*/

    int time = INT_MAX;
    for (int i = 1; i <= n; i++)
    {
        int partition_cost = max(painters_partition_brute_REC(lens, i, k - 1), getsum(lens, i, n - 1));/*assumed one painter is allocated for this portion and we made a partition between (i-1) and (i) so, now we have to calculate from [i,n] recursively*/
        time = min(time, partition_cost);/*we take min at each partions*/

        /*say 10_20_60_ | 50_30_40  partition made at this we will recursively call the right portion that is 50_30_40 and for each partition we will calculate its value from the right side say its got partition as 50 | 30_40  (right portion)  and the left portion alreday has 10_20_60 so sums  are (10+20+60, 50, 30+40) from this max is 90 .... SEE WE GET ALL MAXIMUMS LIKE THIS..FROM THEM WE NEED TO GET THE MINIMUM*/

    }
    return time;
}

/*The DP states are DP(i, j) represents computing the optimal cost for putting i partitions for the first j elements in the array. The answer can be found in DP(k, n)*/
/*T(n)=O(k*n*n) and S(n)=O(k*n)*/
/*prefix sum to easily get the sum between [l...r]*/
int getsum_dp(vector<int> &pref, int l, int r)
{
    if(l==0) return pref[r];
    else return pref[r]-pref[l-1];
}
int painters_partition_dp(vector<int> &lens, int n, int k)
{
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));
    vector<int> pref(n);
    pref[0] = lens[0];
    for (int i = 1; i < n; i++) pref[i]=pref[i-1]+lens[i];

    /*if k==1 then he need sum_array time*/
    for (int j = 1; j <= n; j++) dp[1][j]=getsum_dp(pref,0,j-1);
    /*if n==1 then we need onlt lens[0] time*/
    for (int i = 1; i <= k; i++) dp[i][1]=lens[0];

    for (int i = 2; i <= k; i++)
    {
        for (int j = 2; j <= n; j++)
        {
            int time = INT_MAX;
            for (int cuts = 1; cuts <= j; cuts++)
            {
                int partition_cost = max(dp[i - 1][cuts], getsum_dp(pref, cuts, j - 1));
                time = min(time, partition_cost);
            }
            dp[i][j] = time;
        }
    }
    return dp[k][n];
}



/*say we have n==k that is n no.of painters then we can allocate each painter a board so, max time we need to get job done = sum_array time,
say we have only one painter then minimum time we need is max_element in array

so our low=max_element in array
so our high=sum_of_array

now, we find mid=(low+high)/2 then we find the NO_OF_PAINTERS REQ TO MAKE THE JOB DONE WITH GIVEN MAX_TIME SPAN=MID
if we find req_painters till MID<=K then we are good with this time space so, lets drop our search space even less and see if we can get the job done with less time too so, HIGH=MID-1.
if we find req_painters till MID>K [this means we are required more painters if we decrease the time so we need to increse the time in order to get the job done if not we required more painters which is not optimal case so, INCREASE TIME TO EVEN MORE THAT IS  LOW=MID+1]

note:: ans is at MID.*/
/*Time Complexity: O(n * log2(sum(a)))
Space Complexity: O(1)*/
int findpaintersreq(vector<int>&lens, int n, int maxlen)
{
    int paintersreq = 1;/*initailly we started with 1 painter*/
    int totallen = 0;/*total len we covered till now*/
    for (int i = 0; i < n; i++)
    {
        totallen += lens[i];/*add those lens we cover*/
        if(totallen>maxlen)/*if we covered more len then we need to allocate another painter, and from here new len=lens[i] where it is got crossed the limit of a certain painter*/
        {
            paintersreq++;
            totallen = lens[i];
        }
    }
    return paintersreq;/*noofpainters req to cover till this len*/
}
int painters_partition_Binary_Search(vector<int>&lens, int n, int k)
{
    int low = *max_element(lens.begin(), lens.end());/*min time required to paint all boards*/
    int high = accumulate(lens.begin(), lens.end(), 0);/*max time req to paint all boards*/
    int time = 0;/*resultant min time to paint all boards*/

    while(low<=high)
    {
        int mid = (low + high) / 2;
        int no_of_painters = findpaintersreq(lens, n, mid);/*to paint till this mid how many painters req??*/

        if(no_of_painters>k)low=mid+1;/*if we crossed available pianters then need to increse the time span so, that paintersreq are decreased*/
        else
        {
            time = mid;
            high = mid - 1;/*else if no_of_painters<=k we are at good zone still... so, lets give them a less time to check if they can paint all boards in this min time or not without exceeding the noofpainters available before.*/
        }
    }
    return time;
}
int main()
{
    int n, k; cin>>n>>k;
    vector<int> lens(n);
    for(auto &it : lens) cin>>it;

    int time_brute = painters_partition_brute_REC(lens, n, k);
    cout << time_brute << endl;

    int time_dp = painters_partition_dp(lens, n, k);
    cout << time_dp << endl;

    /*-----use this most optimal approach ---------------------*/
    /*When should such binary search approaches be thought of?
     ans. Whenever, there is some pattern such that there is a point before and after which the nature of the curve changes, we 
          can use binary search to search for that point.*/
    int time_bs = painters_partition_Binary_Search(lens, n, k);
    cout << time_bs << endl;

    return 0;
} 