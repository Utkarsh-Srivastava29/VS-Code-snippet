#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> g[N];
int n, m;

int tin[N], low[N], timer;
bool isBridge[N];
int U[N], V[N];

int comp[N], comp_cnt;

// -------- Find bridges --------
void dfs_bridge(int u, int p_edge){
    tin[u] = low[u] = ++timer;
    for(int id : g[u]){
        if(id == p_edge) continue;
        int v = U[id] ^ V[id] ^ u;

        if(!tin[v]){
            dfs_bridge(v, id);
            low[u] = min(low[u], low[v]);
            if(low[v] > tin[u])
                isBridge[id] = true;
        }
        else{
            low[u] = min(low[u], tin[v]);
        }
    }
}

// -------- Build components --------
void dfs_comp(int u){
    comp[u] = comp_cnt;
    for(int id : g[u]){
        if(isBridge[id]) continue;
        int v = U[id] ^ V[id] ^ u;
        if(!comp[v])
            dfs_comp(v);
    }
}

int main(){
    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> U[i] >> V[i];
        --U[i]; --V[i];
        g[U[i]].push_back(i);
        g[V[i]].push_back(i);
    }

    // 1. find bridges
    for(int i=0;i<n;i++)
        if(!tin[i])
            dfs_bridge(i, -1);

    // 2. build components
    for(int i=0;i<n;i++){
        if(!comp[i]){
            ++comp_cnt;
            dfs_comp(i);
        }
    }

    // 3. build bridge tree
    vector<vector<int>> tree(comp_cnt + 1);
    for(int i=0;i<m;i++){
        if(isBridge[i]){
            int a = comp[U[i]];
            int b = comp[V[i]];
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
    }

    // bridge tree is in `tree`
}
