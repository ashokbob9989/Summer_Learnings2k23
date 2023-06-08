#include <bits/stdc++.h>
using namespace std;

/*Consider city 1 as the starting and ending point. Since the route is cyclic, we can consider any point as a starting point.
Now, we will generate all possible permutations of cities which are (n-1)!.
Find the cost of each permutation and keep track of the minimum cost permutation.
Return the permutation with minimum cost.*/
/*T(n)=O(N!) .. S(n)=O(1)[note adjacency matrix is already given.. so no extra space needed]*/
int Travelling_Salesman_Problem_BruteForce(vector<vector<int>> &adj, int start, int n, int &cost)
{
    cost = INT_MAX;

    /*say if the cities are :: 0 1 2 3 then start=0 and vertex contains {1,2,3}*/
    vector<int> vertex;
    for (int i = 0; i < n; i++)
    {
        if (i != start)    vertex.push_back(i);
    }

    do
    {
        int herestart = start;
        int curr_cost = 0; /*for this path what is the sum_path we get*/
        for (int i = 0; i < vertex.size(); i++)
        {
            curr_cost += adj[herestart][vertex[i]]; /*0->1 add in curr_cost now from 1->2 then 2->3*/
            herestart = vertex[i];
        }
        curr_cost += adj[herestart][start]; /*this is done coz cyclic 0->1, 1->2, 2->3 then need to add 3->1 */
        cost = min(cost, curr_cost);        /*take minimum from the ll paths generated till now*/
    } while (next_permutation(vertex.begin(), vertex.end()));

    return cost;
}

/*We start with all subsets of size 2 and calculate C(S, i) for all subsets where S is the subset, then we calculate C(S, i) for all subsets S of size 3 and so on......
There are at most O(n2^n) subproblems, and each one takes linear time to solve. The total running time is, therefore, O(n^22^n). The time complexity is much less than O(n!) but still exponential. The space required is also exponential.*/
void Travelling_Salesman_Problem_DP(vector<vector<int>> &adj, int &i, int &n, int &cost, vector<int> &visited, vector<int> &Shortest_path)
{
    int mn = INT_MAX, min_path_we_add; /*the cost from this city to the nearest minimum one*/
    int j = INT_MAX;                   /*for the next minimum city*/
    /*mn -> to find the next cost minimum city*/
    visited[i] = 1;                 /*we visited this city*/
    Shortest_path.push_back(i + 1); /*1 based so, did +1*/

    /*iterate in adjacency matrxi and find the minimum city from it*/
    for (int jj = 0; jj < n; jj++)
    {
        if (adj[i][jj] != 0 && visited[jj] == 0) /*if we are not calculated the paths from this city and if its cost!=0[note:: cost from itself=0] we avoid those cass too*/
        {
            if (adj[i][jj] + adj[jj][i] < mn) /*cost from city1->city2 + city2->city1*/
            {
                mn = adj[i][jj] + adj[jj][i];
                min_path_we_add = adj[i][jj]; /*this weight we have to add in out shortest path cost*/
                j = jj;                       /*the next city we visit coz.. this is the minimum*/
            }
        }
    }

    if (mn != INT_MAX)    cost += min_path_we_add; /*if we found any city near from this source so, we need to add*/
    if (j == INT_MAX)            /*if we not found any city minimun from it we are done*/
    {
        j = 0; /*we are done so we need return city1.. 0->(in 1based it is=1)*/
        Shortest_path.push_back(j + 1);
        cost += adj[i][j]; /*cost from the last city to the first city..sy i=3 the j becomes =0 so need to add final (cyclic one as 3->0 cost)*/
        return;
    }

    Travelling_Salesman_Problem_DP(adj, j, n, cost, visited, Shortest_path); /*if not then from the new city(i.e j as our strting point start from it)*/
}

/*First of all, we have to create two primary data holders.
First of them is a map (to get visitedcity->true/false)
And the Second one is the array which is our result path
Perform traversal on the given adjacency matrix adj[][] for all the city and if the cost of reaching any city from the current city is less than the current cost the update the cost.
Generate the minimum path cycle using the above step and return their minimum cost.*/
/*T(n)=O(n^2 * log2(n)) ..S(n)=O(n)*/
void Travelling_Salesman_Problem_Greedy(vector<vector<int>> &adj, int &cost, map<int, int> &visited_city_bool, vector<int> &greedyroute)
{
    /*0 10 15 20
     10 0 35 25
     15 35 0 30
     20 25 30 0*/
    /*sol = 1 2 4 3 1 and cost = 80*/

    int i = 0, j = 0; /*to traverse adjacency matrix*/
    int counter = 0;  /*to track if we reached all cities*/
    int mn = INT_MAX;
    visited_city_bool[0] = 1; /*visited city 1*/

    while (i < adj.size() && j < adj[i].size())
    {
        if (counter >= adj.size() - 1)    break; /*say cities are 4 then if we are at 3 or 4 th city then need to break*/

        if (j != i && visited_city_bool[j] == 0) /*if we are not calculating for the same city and if it is not visited then do visit*/
        {
            if (adj[i][j] < mn) /*calcutes the minimun cost needed from this city*/
            {
                mn = adj[i][j];
                greedyroute[counter] = j + 1; /*to make city numbers from 1,2,3.....*/
            }
        }

        j++; /*if i==j then inc j for the next city to get*/

        if (j == adj[i].size()) /*if we reach the last col in  particular row then add the min we got from the bove process*/
        {
            cost += mn;
            mn = INT_MAX;                                    /*for next process need to initialize it*/
            visited_city_bool[greedyroute[counter] - 1] = 1; /*mark this city as visited*/
            i = greedyroute[counter] - 1;                    /*note:: storing city numbers as 1 bsed but to traverse 0based thats why -1 to get next city(starting)*/
            j = 0;
            counter++; /*inc city numbers*/
        }
    }

    /*to get the city which is last visited say.. if we visited 1,2,4,3 currently we re 3rd but need to move to previous that is 4th city so it is just stored in greedyroute at current-1 position nd we did overll -1 coz (0 based in adj matrix)*/
    i = greedyroute[counter - 1] - 1;
    for (int j = 0; j < adj[i].size(); j++)
    {
        if (i != j && adj[i][j] < mn)
        {
            mn = adj[i][j];
            greedyroute[counter] = j + 1;
        }
    }

    cost += mn;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> adj[i][j];
        }
    }

    int start = 0, cost = 0;
    cost = Travelling_Salesman_Problem_BruteForce(adj, start, n, cost);
    cout << cost << endl;


    vector<int> visited(n, 0);
    vector<int> Shortest_Path;
    cost = 0;
    Travelling_Salesman_Problem_DP(adj, start, n, cost, visited, Shortest_Path);
    for (auto &it : Shortest_Path)    cout << it << " ";
    cout << endl;
    cout << cost << endl;

/*----------use this one the most optimized one-----------------------------------------*/
    map<int, int> visited_city_bool;
    vector<int> greedyroute(n);
    vector<int> fin_greedy_path;
    cost = 0;
    Travelling_Salesman_Problem_Greedy(adj, cost, visited_city_bool, greedyroute);
    fin_greedy_path.push_back(1);
    for (auto &it : greedyroute)    fin_greedy_path.push_back(it);
    for (auto &it : fin_greedy_path)    cout << it << " ";
    cout << endl;
    cout << cost << endl;

    return 0;
}
