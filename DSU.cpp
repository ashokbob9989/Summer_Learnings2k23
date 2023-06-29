#include<bits/stdc++.h>
using namespace std;
/*if we use DFS/BFE to find each time ancestor or somekind of operations we need O(N+E) time complexity 
but if we use DSU we can get all those operations done in T(n)=O(4*alpha) where alpha~1(very close to 1)
so, overall T(n)=O(4) which is a constant.*/
class Disjoint
{
    vector<int> parent, size, rank;
    public:
            Disjoint(int n)
            {
                parent.resize(n + 1);
                size.resize(n + 1,0);
                rank.resize(n + 1,0);
                for (int i = 0; i <= n; i++)
                {
                    parent[i]=i;
                    size[i] = 1;
                }
            }
            /*we are using path compression here.. so, instead of O(lg(n)) time we are having only O(4*alpha) time complexity which is indeed better, for proof do research of it.*/
            int FindUPar(int ver)
            {
                if(ver==parent[ver]) return ver;
                else return parent[ver]=FindUPar(parent[ver]);
            }

            void UnionByRank(int u, int v)
            {
                int ultpar_u = FindUPar(u);
                int ultpar_v = FindUPar(v);
                if(ultpar_u==ultpar_v) return;
                else
                {
                    if(rank[ultpar_v]<rank[ultpar_u]) parent[ultpar_v]=ultpar_u;
                    else if(rank[ultpar_u<rank[ultpar_v]]) parent[ultpar_u]=ultpar_v;
                    else 
                    {
                        parent[ultpar_v] = ultpar_u;
                        rank[ultpar_u]++;
                    }
                }
            }

            void UnionBySize(int u, int v)
            {
                int ultpar_u = FindUPar(u);
                int ultpar_v = FindUPar(v);
                if(ultpar_u==ultpar_v) return;
                else
                {
                    if(size[ultpar_v]<=size[ultpar_u])
                    {
                        parent[ultpar_v] = ultpar_u;
                        size[ultpar_u] += size[ultpar_v];
                    }
                    else 
                    {
                        parent[ultpar_u] = ultpar_v;
                        size[ultpar_v] += size[ultpar_u];
                    }
                }
            }
};

int main()
{
            int n, m;
            cin >> n >> m;
            Disjoint dsu(n);
            for (int i = 0; i < m; i++)
            {
                int x, y;
                cin >> x >> y;
                dsu.UnionBySize(x, y);
            }
            /*say we have 7 vertices and edges are 
              {1 2}, {2,3}, {4,5}, {6,7} here 5 and 6 are not connected and 1 and 3 are connecetd.*/
            int u, v;
            cin >> u >> v;
            if(dsu.FindUPar(u)==dsu.FindUPar(v)) cout<<"Connecetd"<<endl;
            else cout<<"Not Connected"<<endl;

            return 0;
}