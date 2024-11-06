#include <bits/stdc++.h>
using namespace std;
#define int long long int

/*-----------------Binary Exponentiation---------------------*/
/* RECURSIVE */
int powerr0(int a, int n, int mod)
{
    if (n == 0)
        return 1;
    a %= mod;
    int x = powerr0(a, n / 2, mod) % mod;
    int res = (x * x) % mod;
    if (n % 2)
    {
        res = (res * a) % mod;
    }
    return res;
}

/* Iterative */
int powerr1(int a, int n, int mod)
{
    if (n == 0)
        return 1;
    a %= mod;
    int res = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        n = (n >> 1);
    }
    return res;
}

/* Modular Inverse Using Binary Exponentiation */
/* Note that this method is only valid for prime m */
int modinverse(int a, int m)
{
    if (__gcd(a, m) != 1)
    {
        return -1; // no mod-Inverse
    }
    return powerr1(a, m - 2, m);
}

/* Apply Permutation k times */
vector<int> Apply_permutation(vector<int> &permutation, vector<int> &sequence)
{
    int n = sequence.size();
    vector<int> new_sequence(n);
    for (int i = 0; i < n; i++)
    {
        new_sequence[i] = sequence[permutation[i]];
    }
    return new_sequence;
}

vector<int> permute(vector<int> permutation, vector<int> sequence, int k)
{
    if (k == 0)
        return sequence;
    while (k > 0)
    {
        if (k & 1)
        {
            Apply_permutation(permutation, sequence);
        }
        Apply_permutation(permutation, permutation);
        k = (k >> 1);
    }
    return sequence;
}

/* Number of Paths of Fixed length K in a graph */
vector<vector<int>> matrix_mul(vector<vector<int>> &a, vector<vector<int>> &b)
{
    int n = a.size();
    vector<vector<int>> res(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int sum = 0;
            for (int k = 0; k < n; k++)
            {
                sum += (a[i][k] * b[k][j]);
            }
            res[i][j] = sum;
        }
    }
    return res;
}

// res[i][j] contain number of paths from i to j with exactly k edges in between
vector<vector<int>> Num_paths(vector<vector<int>> adj, int k)
{
    int n = adj.size();
    vector<vector<int>> res(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        res[i][i] = 1;
    }

    while (k > 0)
    {
        if (k & 1)
        {
            res = matrix_mul(res, adj);
        }
        adj = matrix_mul(adj, adj);
        k = (k >> 1);
    }
    return res;
}

/* Number of Shortes paths Having atmost K edges in between */
vector<vector<int>> modified_floyd_Warshall(vector<vector<int>> res, vector<vector<int>> adj)
{
    int n = adj.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            if (adj[i][j] == 0)
                adj[i][j] = INT_MAX;
            if (res[i][j] == 0)
                res[i][j] = INT_MAX;
        }
    }

    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int mini = INT_MAX;
            for (int k = 0; k < n; k++)
            {
                mini = min(adj[i][k] + res[k][j], mini);
            }
            ans[i][j] = mini;
        }
    }
    return ans;
}

// res[i][j] represents number of shortest paths between i and j with atmost k edges in between
vector<vector<int>> Num_Shortest_paths(vector<vector<int>> adj, int k)
{
    int n = adj.size();
    vector<vector<int>> res(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                res[i][j] = 0; // Distance to self is 0
            else if (adj[i][j] != 0)
                res[i][j] = adj[i][j]; // Direct edge distance
        }
    }

    k--;

    while (k > 0)
    {
        if (k & 1)
        {
            res = modified_floyd_Warshall(res, adj);
        }
        adj = modified_floyd_Warshall(adj, adj);
        k = (k >> 1);
    }
    return res;
}

signed main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    t = 1;
    while (t--)
    {
        vector<vector<int>> adj = 
        {
            {0,1,4,0,0},{0,0,0,2,0},{0,0,0,3,0},{0,0,0,0,5},{6,0,0,0,0}
        };

        vector<vector<int>> res = Num_Shortest_paths(adj, 2);
        for (auto &i : res)
        {
            for (auto &j : i)
            {
                cout << j << " ";
            }
            cout << endl;
        }

        vector<vector<int>> ans = adj;
        for(int i = 0 ; i < 4 ; i++){
            ans = modified_floyd_Warshall(ans,adj);
        }

        // for (auto &i : ans)
        // {
        //     for (auto &j : i)
        //     {
        //         cout << j << " ";
        //     }
        //     cout << endl;
        // }
    }
    return 0;
}