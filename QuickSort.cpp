/*By Ashok_Zayn--------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ll long long
#define ld double
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ff first
#define ss second
#define ins insert
#define vll vector <ll>
#define vvll vector <vll>
#define vbool vector <bool>
#define pll pair <ll,ll>
#define vpll vector <pll>
#define set_bits __builtin_popcountll
#define sz(v) (int)v.size()
#define allin(v) v.begin(), v.end()
#define allinr(v) v.rbegin(), v.rend()
#define desc() greater <ll>()
#define rapido ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define mll map<ll,ll>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
/*------------------Policy based data structures-----------------------------------------------------------------------------
template<class T> using oset = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class key, class value> using omap = tree <key,value,less<key>,rb_tree_tag,tree_order_statistics_node_update>;
find_by_order(k) -> returns iterator to kth element from start 0
order_of_key(k) -> returns count of elements < k */
const int ebl = 1e9+7;
const int newmod = 998244353;
const int N = 2e5+7;
const ll inf = 1e18;
const ld eps = 1e-9;
#define PI 3.141592653589793238462
#define modinv2 500000004
ll gcd(ll a, ll b) { while (b) {a %= b; swap(a,b);} return a; }
ll lcm(ll a, ll b) { ll g=gcd(a,b); ll res=a*(b/g); return res; }
ll extended_gcd(ll a,ll b,ll &x,ll &y){if (b==0){ x=1;y=0;return a;}ll x1,y1;ll g=extended_gcd(b,a%b,x1,y1);x=y1;y=x1-y1*(a/b);return g; }
ll binExp(ll a, ll b, ll m) { a = a % m; ll res = 1; while (b) { if (b&1) { res=(res * a) % m; } a=(a * a) % m; b>>=1; } return res; }
ll mod_inv(ll a, ll m) { a = a % m; return binExp(a,m-2,m); }
ll mod_add(ll a, ll b, ll m) { a = a % m; b = b % m; return (((a + b) % m) + m) % m; }
ll mod_sub(ll a, ll b, ll m) { a = a % m; b = b % m; return (((a - b) % m) + m) % m; }
ll mod_mul(ll a, ll b, ll m) { a = a % m; b = b % m; return (((a * b) % m) + m) % m; }
ll mod_div(ll a, ll b, ll m) { a = a % m; ll binv = mod_inv(b,m); return (((a * binv) % m) + m) % m; }
ll sqrtll(ll n) { ll lo=0,hi=1e9+7; while (hi-lo>1) { ll m=(hi+lo)/2; if (m*m<=n) { lo=m; } else { hi=m-1; }} if (hi*hi<=n) { return hi; }
return lo; }
ld sqrtld(ll n) { ld lo=0,hi=1e9+7; while (hi-lo>eps) { ld m=(hi+lo)/2; if ((n-m*m)>eps) { lo=m; } else { hi=m-eps; }} return lo; }
struct custom_hash{static uint64_t splitmix64(uint64_t x){x+=0x9e3779b97f4a7c15;x=(x^(x>>30))* 0xbf58476d1ce4e5b9;
x=(x^(x>>27))* 0x94d049bb133111eb;return x^(x>>31);}size_t operator()(uint64_t x)const{
static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();return splitmix64(x+FIXED_RANDOM);}};
unordered_map<ll,ll,custom_hash>uchm;
 
/*----------------------------------------------------------------------------------------------------------------------------
----------------------to find whether a substr present or not-----------------------------------------------------------------
size_t pos=s.find(tt);if(pos!=string::npos)*/
 
/*----------------------------------------------------------------------------------------------------------------------------
------------to calculate prime factors and their freqs and among them the max_freq...tt_numii is eql to numi------------------
mll numpri;ll tt_numi=numi;ll toti_maxii=1;for(ll p1=2;p1*p1<=numi;p1++){if(tt_numi%p1==0){ll cali=0;while(tt_numi%p1==0)
{cali++;tt_numi/=p1;}numpri[p1]=cali;if(cali>toti_maxii)toti_maxii=cali;}}*/
 
/*---------------------------------------------------------------------------------------------------------------------------
ll comb(ll n, ll r){return findfact(n)/findfact(r)/findfact(n-r);}
------------------------------------------------------------------------------------------------------------------------------*/
 
/*----sparse Table------------------------------------------------------------------------------------------------------------
 
struct sparseTable{ ll n,k; vvll  table; vll logs;
void init(ll x) n=x; logs.resize(n+1); logs[1]=0;
for(int i=2;i<=n;i++) logs[i]=logs[i/2]+1; k=*max_element(logs.begin(),logs.end());
table.resize(k+1,vll(n+1,-1e9) );}
ll operation(ll x,ll y){return max(x,y);}
void build(vll &arr){for(int j=0;j<n;j++)table[0][j]=arr[j];
for(int i=1;i<=k;i++){for(int j=0;j+(1<<i)<=n;j++)
table[i][j]=operation(table[i-1][j],table[i-1][j+(1<<(i-1))]);}}
ll query(ll l,ll r){ll i = logs[r -l +1];ll ans= operation(table[i][l],table[i][r-(1<<i)+1]);
return ans;}
};
---------------------------------------------------------------------------------------------------------------------------*/
void debug(vll &v){for(auto &it : v)cout<<it<<'-';cout<<endl;}

int partition(vll &arr, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = arr[low]; // we choose always first element as pivot that is arr[low].

    while (i < j)
    {
        while (arr[i] <= pivot && i <= high - 1) //find first largest element from left for i
        {
            i++;
        }
        while (arr[j] > pivot && j >= low + 1) // finf first least element from right for j
        {
            j--;
        }

        if (i < j) swap(arr[i], arr[j]); //swap them
    }

    swap(arr[low], arr[j]); //swap pivot and right element..now next pivot is jth

    return j;
}

void QuickSort(vll &arr, int low, int high)
{
    if (low >= high) return;

    int pindex = partition(arr, low, high);
    QuickSort(arr, low, pindex - 1);
    QuickSort(arr, pindex + 1, high);
}
void do_it()
{
    ll n;
    cin >> n;
    vll arr(n);
    for (auto &it : arr) cin >> it;
    QuickSort(arr, 0,n-1);
    //debug(arr);
}
signed main(int argc, char const *argv[])
{
    rapido
        /*#ifndef ONLINE_JUDGE
                freopen(input.txt,r,stdin);
                freopen(output.txt,w,stdout);
          #endif*/
    ll kin = 1;
    cin >> kin;
    while (kin--) do_it();
    return 0;
}