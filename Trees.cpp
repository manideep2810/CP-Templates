#include<bits/stdc++.h>
using namespace std;
#define int long long int


/*------------------------------------ Binary Lifting ------------------------------------*/
const int N = 2*1e5 + 5 , M = 20;
vector<int> adj[N],depth(N,0);
int par[N][M];

// par[i][j] -> 2^j th parent of vertex i
// par[i][j] -> par[par[i][j-1]][j-1] i.e [8 = 4 + 4 , 16 = 8 + 8 similarly 2^j = 2^(j-1) + 2^(j-1) 
// which is 2^(j-1)th parent of vertex par[i][j-1]];

void dfs(int s,int parent){
    par[s][0] = parent;
    for(int i = 1 ; i < M ;i++){
        par[s][i] = par[par[s][i-1]][i-1];
    }
    for(auto &i:adj[s]){
        if(i!=parent){
            dfs(i,s);
        }
    }
}

int kthparent(int u,int k){
    for(int i = 0 ; i < M ; i++){
        if((k&(1<<i))){
            u = par[u][i];
        }
    }

    return u;
}

/*----------------------------------         LCA            -----------------------------------
 const int N = 2*1e5 + 5 , M = 20;
 vector<int> adj[N],depth(N,0);
 int par[N][M]; */

void dfs(int s,int parent,int level){
    depth[s] = level;
    par[s][0] = parent;
    for(int i = 1 ; i < M ; i++){
        par[s][i] = par[par[s][i-1]][i-1];
    }
    for(auto &i:adj[s]){
        if(i!=parent){
            dfs(i,s,level + 1);
        }
    }
}

int LCA(int u,int v){
    if(u==v) return u;
    if(depth[u] < depth[v]){
        swap(u,v);
    }
    int diff = depth[u] - depth[v];
    for(int i = 0 ; i < M ; i++){
        if((diff & (1<<i))){
            u = par[u][i];
        }
    }

    for(int i = M-1 ; i>=0 ; i--){
        if(par[u][i]!=par[v][i]){
            u = par[u][i];
            v = par[v][i];
        }
    }

    if(u==v){
        return u;
    }

    return par[u][0];
}





signed main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    t = 1;
    while(t--)
    {
        int n;
        cin >> n;

        for(int i = 0 ; i < n - 1 ; i++){
            int u,v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(0,-1);
        int ans = LCA(9,5);
        
    
    }
    return 0;
}