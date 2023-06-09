#include<bits/stdc++.h>
using namespace std;

class Solution
{
    public:

    int lip(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& memo)
    {
        if( i<0 || j<0 || i>=matrix.size() || j>=matrix[0].size() ) return 0; /*outofBounds*/
        if(memo[i][j]>0) return memo[i][j];/*alreday calculted*/

        int currMaxPath=1;
        
        /*useful up neighbour*/
        if( i-1<matrix.size() && i-1>=0 && matrix[i-1][j] > matrix[i][j] )
            currMaxPath= max( currMaxPath, 1+lip(matrix, i-1, j, memo ) );

        /*useful down neighbour*/
        if( i+1<matrix.size() && i+1>=0 && matrix[i+1][j] > matrix[i][j] ) 
            currMaxPath= max( currMaxPath, 1+lip(matrix, i+1, j, memo ) );
        
        /*useful left neighbour*/
        if( j-1<matrix[0].size() && j-1>=0 && matrix[i][j-1] > matrix[i][j] )
            currMaxPath= max( currMaxPath, 1+lip(matrix, i, j-1, memo ) );
        
        /*useful right neighbour*/
        if( j+1<matrix[0].size() && j+1>=0 && matrix[i][j+1] > matrix[i][j] )
            currMaxPath= max( currMaxPath, 1+lip(matrix, i, j+1, memo ) );

        memo[i][j]=currMaxPath;

        return currMaxPath;

    }

    int longestIncreasingPath(vector<vector<int>>& matrix) 
    {
        int sol=0;
        vector< vector<int> > memo( matrix.size(), vector<int>( matrix[0].size(), 0) );

        for(int i=0;i<matrix.size();i++)
        {
            for(int j=0;j<matrix[0].size();j++)
            {
                sol= max( sol, lip(matrix, i, j, memo) );
            }
        }
        
        return sol;    
    }
};

class Solution
{
    public:
    int maxIncreasingCells(vector<vector<int>>& matrix) 
    {
       int n=matrix.size();
       int m=matrix[0].size();

       /*approach:: we process the elements in matrix in decreasing order(there may be duplicates but we traverse unique elements coz this will not chnage our solution)*/
       vector<int>roweles(n);/*stores max element in row*/
       vector<int>coleles(m);/*stores max element in col*/

       unordered_map< int, vector<pair<int,int>> >valuepos; /*element->{its positions}*/
       vector<vector<int>> temp(n, vector<int>(m));
       set<int>unqvals;/*we process unique values*/

       for(int i=0;i<n;i++)
       {
           for(int j=0;j<m;j++)
           {
               int value=matrix[i][j];
               valuepos[-value].push_back({i,j});/*we re storing them in -ve values coz we are trversing in decresing order like in question mentioned from (less cell)->(greter cell) but we process in order (greater cell)->(less cell) coz we know from max element we cant go further at that mx position our answer is 1*/
               unqvals.insert(-value);/*max element is stored at beginnning coz we know in set elements are stored in inc fashion so, to process max element we stores in -ele*/
           }
       }

       for(auto &it1 : unqvals)/*for each element in set*/
       {
           for(auto &it2 : valuepos[it1])/*we track its position*/
           {
               int rowno=it2.first;
               int colno=it2.second;
               temp[rowno][colno]= 1+max(roweles[rowno],coleles[colno]);/*if we choose col path what max steps we can cover, if we choose rowpath what the max steps we can cover "once we got the max steps from that point we add 1 to the steps coz considering the  current element itself"*/
           }
           
           /*update the max row, max col vectors for further calculations*/
           for(auto &it2 : valuepos[it1])
           {
               int rowno=it2.first;
               int colno=it2.second;
               roweles[rowno]=max(roweles[rowno],temp[rowno][colno]);/* max of stored val previously at that position, now rowval*/
               coleles[colno]=max(coleles[colno],temp[rowno][colno]);
           }
       }

       /* ans can be found if we choose col paths/ row paths both max sol is the steps/cells we can cover in a matrix*/
       int rowmx=*max_element(roweles.begin(),roweles.end());
       int colmx=*max_element(coleles.begin(),coleles.end());

       return max(rowmx, colmx);
    }
};
