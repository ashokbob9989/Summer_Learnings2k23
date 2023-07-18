#include<bits/stdc++.h>
using namespace std;

void constructlps(string &txt,string &pat, int n, int m, vector<int>&lps)
{
    lps[0]=0;
    int i=1,len=0;
    while(i<m)
    {
        if(pat[i]==pat[len])
        {
            len++;
            lps[i]=len;
            i++;
        }
        else
        {
            if(len!=0)
            {
                len=lps[len-1];
            }
            else
            {
                lps[i]=0;
                i++;
            }
        }
        
    }
}
void KMPalgo(string &txt, string &pat, int n, int m, vector<int>&lps,vector<int>&patpos)
{
    int i=0,j=0;
    while( (n-i)>=(m-j) )
    {
        if(txt[i]==pat[j])
        {
            i++;
            j++;
        }
        if(j==m)
        {
            patpos.push_back(i-j);
            j=lps[j-1];
        }
        else if( (i<n) and (txt[i]!=pat[j]) )
        {
            if(j!=0)
            {
                j=lps[j-1];
            }
            else 
            {
                i++;
            }
        }
    }
}
int strstr(string txt, string pat)
{
    int n=txt.size();
    int m=pat.size();
    
    vector<int>lps(m,0);
    constructlps(txt,pat,n,m,lps);
    
    /*debug*/ 
    //for(auto &it : lps) cout<<it<<" "; cout<<endl;
  
    vector<int>patpos;
    KMPalgo(txt,pat,n,m,lps,patpos);
    
    if(patpos.size()==0) return -1;
    else  return patpos[0];
}
int main()
{

    string txt,pat;
    cin>>txt>>pat;
    strstr(txt,pat);

    return 0;

}
