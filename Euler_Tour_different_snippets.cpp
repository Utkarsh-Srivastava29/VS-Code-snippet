// ------------------------------
// Euler Tour Type 1: Entry Only
// ------------------------------
// Usage:
// - Subtree queries
// - Subtree sum, subtree max
// - Segment Tree / BIT on subtree
// Subtree of u = [in[u], out[u]]
// ------------------------------

#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> g[N];

int in[N], out[N], flat[N];
int timer = 0;

void dfs(int u, int p){
    in[u] = ++timer;
    flat[timer] = u;   // or store value[u]

    for(int v : g[u]){
        if(v == p) continue;
        dfs(v, u);
    }

    out[u] = timer;
}







// --------------------------------------
// Euler Tour Type 2: Repeat After Child
// --------------------------------------
// Usage:
// - LCA using RMQ
// - First occurrence array
// Size ≈ 2*n - 1
// --------------------------------------

#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> g[N];
vector<int> euler;
int depth[N];
int firstOcc[N];

void dfs(int u, int p, int d){
    depth[u] = d;
    firstOcc[u] = euler.size();

    euler.push_back(u);

    for(int v : g[u]){
        if(v == p) continue;
        dfs(v, u, d+1);
        euler.push_back(u);   // repeat after child
    }
}












// --------------------------------------
// Euler Tour Type 3: Entry + Exit
// --------------------------------------
// Usage:
// - Mo's algorithm on tree
// - Frequency counting
// - Subtree distinct queries
// Size = 2*n
// --------------------------------------

#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> g[N];
vector<int> euler;

void dfs(int u, int p){
    euler.push_back(u);   // entry

    for(int v : g[u]){
        if(v == p) continue;
        dfs(v, u);
    }

    euler.push_back(u);   // exit
}














// --------------------------------------
// Euler Tour Type 4: Edge Based
// --------------------------------------
// Usage:
// - Edge frequency counting
// - Edge contribution problems
// - Bridge / articulation related tasks
// --------------------------------------

#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> g[N];
vector<pair<int,int>> euler;

void dfs(int u, int p){
    for(int v : g[u]){
        if(v == p) continue;

        euler.push_back({u,v});   // going down
        dfs(v, u);
        euler.push_back({v,u});   // coming up
    }
}





















// --------------------------------------
// Euler Tour Type 5: In-Out Time
// --------------------------------------
// Usage:
// - Check if u is ancestor of v in O(1)
// Condition:
// in[u] <= in[v] && out[v] <= out[u]
// --------------------------------------

#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> g[N];

int in[N], out[N], timer = 0;

void dfs(int u, int p){
    in[u] = ++timer;

    for(int v : g[u]){
        if(v == p) continue;
        dfs(v, u);
    }

    out[u] = timer;
}

bool isAncestor(int u, int v){
    return in[u] <= in[v] && out[v] <= out[u];
}











// --------------------------------------
// Euler Tour Type 6: Depth + Euler
// --------------------------------------
// Usage:
// - LCA via RMQ
// - Store depth for RMQ
// --------------------------------------

#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> g[N];

vector<int> euler, depthEuler;
int firstOcc[N];

void dfs(int u, int p, int d){
    firstOcc[u] = euler.size();

    euler.push_back(u);
    depthEuler.push_back(d);

    for(int v : g[u]){
        if(v == p) continue;
        dfs(v, u, d+1);

        euler.push_back(u);
        depthEuler.push_back(d);
    }
}














// --------------------------------------
// Euler Tour Type 7: Flatten for HLD
// --------------------------------------
// Usage:
// - Heavy Light Decomposition
// - Path queries with segment tree
// - Subtree updates
// --------------------------------------

#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> g[N];

int in[N], out[N], flat[N];
int timer = 0;

void dfs(int u, int p){
    in[u] = ++timer;
    flat[timer] = u;

    for(int v : g[u]){
        if(v == p) continue;
        dfs(v, u);
    }

    out[u] = timer;
}








// --------------------------------------
// Euler Tour Type 8: Mo's on Tree
// --------------------------------------
// Usage:
// - Distinct values on path
// - Offline tree queries
// - Frequency problems
// --------------------------------------

#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> g[N];

int in[N], out[N], euler[2*N];
int timer = 0;

void dfs(int u, int p){
    in[u] = ++timer;
    euler[timer] = u;

    for(int v : g[u]){
        if(v == p) continue;
        dfs(v, u);
    }

    out[u] = ++timer;
    euler[timer] = u;
}



















