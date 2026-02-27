//agr kabhi bhi prefix of the root ki baat use ho always use it

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


























#include<bits/stdc++.h>
using namespace std;

const int N = 200005;

vector<int> g[N];
int tin[N], tout[N];
int timer = 0;

void dfs(int v, int parent){
    tin[v] = timer;
    timer++;

    for(int u : g[v]){
        if(u != parent){
            dfs(u, v);
        }
    }

    tout[v] = timer;
}

int main(){
    int n;
    cin >> n;

    for(int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    return 0;
}


















Convert tree subtree → array range using Euler Tour → solve with range data structure.

















Flatten tree with Euler Tour → subtree becomes array range → solve using range data structure.













Use entry times only.

Store node value at arr[tin[v]].

Subtree of v corresponds to range:

[tin[v], tout[v])

tout[v] is boundary, not a value position.











#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

vector<int> adj[N];
int tin[N], tout[N];
int timer = 0;

void dfs(int v, int parent) {
    tin[v] = timer;
    timer++;

    for (int child : adj[v]) {
        if (child != parent) {
            dfs(child, v);
        }
    }

    tout[v] = timer;
}

int main() {
    int n;
    cin >> n;

    // reading edges
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);  // assuming 1 is root

    return 0;
}











#include<bits/stdc++.h>
using namespace std;

const int N = 200005;

vector<int> adj[N];
vector<int> euler;   // full euler tour
int tin[N], tout[N];
int timer = 0;

void dfs(int v, int parent) {
    tin[v] = timer;
    euler.push_back(v);
    timer++;

    for(int child : adj[v]) {
        if(child != parent) {
            dfs(child, v);
            euler.push_back(v);   // after every child repeat
            timer++;
        }
    }

    tout[v] = timer - 1;
}










Euler Tour tree ko array me convert kar deta hai.











#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> adj[N];

int tin[N];      // tin[v] = time when we FIRST enter node v
int timer = 0;   // global timer increases only when we enter a node

void dfs(int v, int parent) {
    tin[v] = timer++;  
    // Assign current time to node v
    // Each node gets exactly one position in flattened order

    for(int child : adj[v]) {
        if(child != parent) {
            dfs(child, v);
        }
    }

    // No tout[] here
    // This version only records entry time
}

/*
WHAT THIS STORES:
DFS order of nodes.

USE CASE:
- Checking relative order
- Sometimes ancestor checks (but less common alone)

LIMITATION:
No direct subtree boundary stored.
*/


















#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> adj[N];

int tin[N];     // entry time of node
int tout[N];    // exit boundary of subtree
int timer = 0;

void dfs(int v, int parent) {

    tin[v] = timer++;
    // Subtree of v STARTS here
    // Each node occupies exactly one position in flattened array

    for(int child : adj[v]) {
        if(child != parent) {
            dfs(child, v);
        }
    }

    tout[v] = timer;
    // Subtree of v ENDS here (exclusive boundary)
}

/*
INTERVAL TYPE:
Subtree of v = [tin[v], tout[v])

Half-open interval:
Includes tin[v]
Excludes tout[v]

WHY WORKS?
Because all subtree nodes are visited
between tin[v] and tout[v].

USE CASE:
- Subtree sum queries
- Subtree min/max
- XOR queries
- Segment Tree / Fenwick Tree

MOST COMMON in CP.
*/













#include<bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> adj[N];

vector<int> euler;   // stores full DFS walk (nodes repeated)
int tin[N];          // first occurrence of node
int tout[N];         // last occurrence of node
int timer = 0;

void dfs(int v, int parent) {

    tin[v] = timer;
    euler.push_back(v);
    timer++;
    // Record node when ENTERING

    for(int child : adj[v]) {
        if(child != parent) {

            dfs(child, v);

            euler.push_back(v);
            timer++;
            // After finishing child,
            // we come back to v and record it again
        }
    }

    tout[v] = timer - 1;
    // Last occurrence of v in Euler array
}

/*
INTERVAL TYPE:
Subtree of v = [tin[v], tout[v]]
Fully inclusive interval

WHAT STORED?
Entire DFS traversal path.
Nodes appear multiple times.

EXAMPLE:
Tree:
    1
   / \
  2   3

Euler array:
[1, 2, 1, 3, 1]

USE CASE:
- LCA using RMQ
- Depth tracking
- Tree distance queries

NOT used for subtree sum directly.
*/









#include<bits/stdc++.h>
using namespace std;

const int N = 200005;

vector<int> adj[N];
int tin[N], tout[N];
int timer = 0;
long long val[N];

long long seg[8*N];   // segment tree
int n;

/* -------- Segment Tree -------- */

void update(int node, int start, int end, int idx, long long value) {
    if(start == end) {
        seg[node] += value;
        return;
    }

    int mid = (start + end) / 2;

    if(idx <= mid)
        update(2*node, start, mid, idx, value);
    else
        update(2*node+1, mid+1, end, idx, value);

    seg[node] = seg[2*node] + seg[2*node+1];
}

long long query(int node, int start, int end, int l, int r) {
    if(r < start || end < l) return 0;

    if(l <= start && end <= r)
        return seg[node];

    int mid = (start + end) / 2;

    return query(2*node, start, mid, l, r)
         + query(2*node+1, mid+1, end, l, r);
}

/* -------- DFS Euler Tour -------- */

void dfs(int v, int parent) {

    tin[v] = timer++;
    update(1, 0, 2*n, tin[v], val[v]);   // +value at entry

    for(int child : adj[v]) {
        if(child != parent)
            dfs(child, v);
    }

    tout[v] = timer++;
    update(1, 0, 2*n, tout[v], -val[v]); // -value at exit
}

/* -------- Main -------- */

int main() {

    cin >> n;

    for(int i=1;i<=n;i++)
        cin >> val[i];

    for(int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,0);   // assuming 1 is root

    int q;
    cin >> q;

    while(q--) {

        int type;
        cin >> type;

        if(type == 1) {
            // Update node value
            int v;
            long long newVal;
            cin >> v >> newVal;

            long long delta = newVal - val[v];
            val[v] = newVal;

            update(1, 0, 2*n, tin[v], delta);
            update(1, 0, 2*n, tout[v], -delta);
        }

        else if(type == 2) {
            // Query path sum root → v
            int v;
            cin >> v;

            cout << query(1, 0, 2*n, 0, tin[v]) << "\n";
        }
    }
}












Subtree → Entry-Only

Range mark subtree → Entry-Exit

LCA → Full Tour








#include<bits/stdc++.h>
using namespace std;

const int N = 200005;

vector<int> adj[N];
int tin[N], sz[N];
int timer = 0;
long long val[N];

long long seg[4*N];
int n;

/* -------- Segment Tree -------- */

void build(int node, int start, int end, vector<long long>& arr) {
    if(start == end) {
        seg[node] = arr[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2*node, start, mid, arr);
    build(2*node+1, mid+1, end, arr);
    seg[node] = seg[2*node] + seg[2*node+1];
}

void update(int node, int start, int end, int idx, long long value) {
    if(start == end) {
        seg[node] = value;
        return;
    }
    int mid = (start + end) / 2;
    if(idx <= mid)
        update(2*node, start, mid, idx, value);
    else
        update(2*node+1, mid+1, end, idx, value);

    seg[node] = seg[2*node] + seg[2*node+1];
}

long long query(int node, int start, int end, int l, int r) {
    if(r < start || end < l) return 0;
    if(l <= start && end <= r) return seg[node];

    int mid = (start + end) / 2;
    return query(2*node, start, mid, l, r)
         + query(2*node+1, mid+1, end, l, r);
}

/* -------- DFS Entry-Only -------- */

void dfs(int v, int parent) {

    tin[v] = timer++;
    sz[v] = 1;

    for(int child : adj[v]) {
        if(child != parent) {
            dfs(child, v);
            sz[v] += sz[child];
        }
    }
}

/* -------- Main -------- */

int main() {

    cin >> n;

    for(int i=1;i<=n;i++)
        cin >> val[i];

    for(int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,0);

    // Flatten tree into array
    vector<long long> arr(n);
    for(int i=1;i<=n;i++)
        arr[tin[i]] = val[i];

    build(1, 0, n-1, arr);

    int q;
    cin >> q;

    while(q--) {

        int type;
        cin >> type;

        if(type == 1) {
            // Update node value
            int v;
            long long x;
            cin >> v >> x;

            val[v] = x;
            update(1, 0, n-1, tin[v], x);
        }

        else if(type == 2) {
            // Subtree sum
            int v;
            cin >> v;

            int l = tin[v];
            int r = tin[v] + sz[v] - 1;

            cout << query(1, 0, n-1, l, r) << "\n";
        }
    }
}















#include<bits/stdc++.h>
using namespace std;
#define int long long
 
struct segment{
   int sz;
   vector<int>summed;
   void init(int n){
      sz=1;
      while(sz<n) sz*=2;
      summed.resize(2*sz,0);
   }
   
   
   void build(vector<int>&flat,int x,int lx,int rx){
    if(rx-lx==1){
         if(lx<(flat.size())){
            summed[x]=flat[lx];
         }
          return;
      }
      int m=(lx+rx)/2;
      build(flat,2*x+1,lx,m);
      build(flat,2*x+2,m,rx);
      summed[x]=summed[2*x+1]+summed[2*x+2];
   }
   void build(vector<int>&flat){
      build(flat,0,0,sz);
   }
   
   void set(int i,int val,int x,int lx,int rx){
    if(rx-lx==1){
          summed[x]=val;
          return;
      }
      int m=(lx+rx)/2;
      if(i<m)
      set(i,val,2*x+1,lx,m);
      else
      set(i,val,2*x+2,m,rx);
      summed[x]=summed[2*x+1]+summed[2*x+2];
   }
   
   void set(int i,int val){
      set(i,val,0,0,sz);
   }
   
   
   int calc(int l,int r,int x,int lx,int rx){
      if(lx>=r or rx<=l) return 0;
      if(lx>=l and rx<=r) return summed[x];
      int m=(lx+rx)/2;
      int m1=calc(l,r,2*x+1,lx,m);
      int m2=calc(l,r,2*x+2,m,rx);
      return m1+m2;
   }
   
   int calc(int l,int r){
      return calc(l,r,0,0,sz);
   }
   
};
 
 
 
 
vector<int>start;
vector<int>end1;
vector<int>value;
vector<int>flat;//for euler tour
 
void dfs(int src,int par,vector<vector<int>>&g,int &cnt){
    start[src]=cnt;
    flat[cnt]=value[src];
    cnt++;
    for(auto &x:g[src]){
        if(x!=par){
            dfs(x,src,g,cnt);
        }
    }
    end1[src]=cnt;
    flat[cnt]=-value[src];
    cnt++;
}
int32_t main(){
   int n,m;
   cin>>n>>m;
   segment st;
   st.init(2*n);
   vector<int>v(n);
   for(int i=0;i<n;i++){
      cin>>v[i];
   }
   start.resize(n);
   end1.resize(n);
   value=v;
   flat.resize(2*n);
   vector<vector<int>>g(n);
   for(int i=0;i<n-1;i++){
        int x,y;
        cin>>x>>y;
        x--;
        y--;
        g[x].push_back(y);
        g[y].push_back(x);
   }
   int cnt=0;
   dfs(0,-1,g,cnt);
   st.build(flat);
   while(m--){
    int op;
    cin>>op;
    if(op==1){
        int i,val;
        cin>>i>>val;
        i--;
        int left=start[i];
        int right=end1[i];
        st.set(left,val);
        st.set(right,-val);
    }
    if(op==2){
        int x;
        cin>>x;
        x--;
        int right=start[x]+1;
        cout<<st.calc(0,right)<<"\n";
    }
   }
}











Slide basically bol rahi hai:

Path ko simple range me convert nahi kar sakte.

Isliye entry-exit + prefix approach use karni padegi.

Ya heavy-light decomposition use karna padega.














Entry → +value
Exit → -value
Prefix till tin[v] → path sum

That’s it.














DFS → O(n)
Each update → O(log n)
Each query → O(log n)
Space → O(n)
function dfs(v, parent):
    tin[v] := timer
    timer := timer + 1
    for child in adj[v]:
        if child != parent then
            dfs(child, v)
    tout[v] := timer










Entry → +value
Exit → -value
Prefix till tin[v] → path sum

Update → modify both entry and exit

That’s it.









Euler Tour sirf flattening karta hai.
Kaunsi operation karni hai (sum/min/max/XOR/GCD) — woh Segment Tree decide karega.













#include<bits/stdc++.h>
using namespace std;

const int N = 200005;

vector<int> adj[N];
int tin[N], tout[N];
int timer = 0;
int val[N];
int flat[N];          // flattened tree
int seg[4*N];         // segment tree
int n;

/* -------- DFS (Entry Only) -------- */

void dfs(int v, int parent) {

    tin[v] = timer;
    flat[timer] = val[v];
    timer++;

    for(int child : adj[v]) {
        if(child != parent)
            dfs(child, v);
    }

    tout[v] = timer - 1;
}

/* -------- Segment Tree -------- */

void build(int node, int l, int r) {
    if(l == r) {
        seg[node] = flat[l];
        return;
    }

    int mid = (l + r) / 2;
    build(2*node, l, mid);
    build(2*node+1, mid+1, r);

    seg[node] = min(seg[2*node], seg[2*node+1]);
}

int query(int node, int l, int r, int ql, int qr) {

    if(qr < l || r < ql)
        return INT_MAX;

    if(ql <= l && r <= qr)
        return seg[node];

    int mid = (l + r) / 2;

    return min(
        query(2*node, l, mid, ql, qr),
        query(2*node+1, mid+1, r, ql, qr)
    );
}

void update(int node, int l, int r, int idx, int value) {

    if(l == r) {
        seg[node] = value;
        return;
    }

    int mid = (l + r) / 2;

    if(idx <= mid)
        update(2*node, l, mid, idx, value);
    else
        update(2*node+1, mid+1, r, idx, value);

    seg[node] = min(seg[2*node], seg[2*node+1]);
}

/* -------- Main -------- */

int main() {

    cin >> n;

    for(int i=1;i<=n;i++)
        cin >> val[i];

    for(int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,0);      // assume root = 1

    build(1, 0, n-1);

    int q;
    cin >> q;

    while(q--) {

        int type;
        cin >> type;

        if(type == 1) {
            // Update node value
            int v, newVal;
            cin >> v >> newVal;

            update(1, 0, n-1, tin[v], newVal);
        }

        else {
            // Subtree minimum query
            int v;
            cin >> v;

            cout << query(1, 0, n-1, tin[v], tout[v]) << "\n";
        }
    }
}















Euler Tour = tree flattening
Segment Tree = operation engine

Flatten once.
Operation change freely.










Hum log path queries ka use nahin kr skte hain and that is it for the value of minimum from the root to the node.












If problem solve ho raha hai BIT se → use BIT.
Agar BIT se possible nahi → tab Segment Tree use karo.






sum->bit,xor->bit,subtree sum->bit or segtree,min->seg tree,range gcd->segtree,path sum->bit,general path min->hld+segtree







#include<bits/stdc++.h>
using namespace std;

const int N = 200005;

vector<int> adj[N];
int tin[N], tout[N], timer = 0;
long long val[N], flat[N];
long long bit[N];
int n;

/* -------- BIT -------- */

void update(int idx, long long delta) {
    for(++idx; idx <= n; idx += idx & -idx)
        bit[idx] += delta;
}

long long query(int idx) {
    long long sum = 0;
    for(++idx; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}

long long rangeQuery(int l, int r) {
    return query(r) - (l ? query(l-1) : 0);
}

/* -------- DFS -------- */

void dfs(int v, int p) {
    tin[v] = timer;
    flat[timer] = val[v];
    timer++;

    for(int u : adj[v]) {
        if(u != p)
            dfs(u, v);
    }

    tout[v] = timer - 1;
}

/* -------- Main -------- */

int main() {
    cin >> n;

    for(int i = 1; i <= n; i++)
        cin >> val[i];

    for(int i = 0; i < n-1; i++) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,0);

    for(int i = 0; i < n; i++)
        update(i, flat[i]);

    int q;
    cin >> q;

    while(q--) {
        int type;
        cin >> type;

        if(type == 1) {
            int v;
            long long newVal;
            cin >> v >> newVal;

            long long delta = newVal - val[v];
            val[v] = newVal;
            update(tin[v], delta);
        }
        else {
            int v;
            cin >> v;
            cout << rangeQuery(tin[v], tout[v]) << "\n";
        }
    }
}














Euler Tour + Segment Tree/BIT
→ Time O(log n) per query
→ Space O(n)

Fully scalable for n up to 2e5 or even 1e6.


Node → single index
Subtree → continuous range
Root path → entry/exit trick









subtree->range(tin[u],tin[v])-->sum,min,max,XOR,GCD
Path query-->add/subtract trick
ancestor u is ancestor of v
with path queries between arbitrary nodes,combine lca with euler tourto split the path into two root-to-node paths.






Ye slide Ancestor Check ka sabse powerful use batati hai — aur ye Euler Tour ka ek hidden superpower hai.





Euler Tour:
Tree ko flatten karta hai.
Rerooting DP:
Tree ko rotate karta hai (root shift karta hai).
We cannot change the root for the case of euler tour







Euler Tour:

One-time cost = O(n)

After that:

Fast queries possible because tree → array






Child order affects numbers
But does NOT affect correctness for euler tour







| Query Type | Euler Tour | HLD                 |
| ---------- | ---------- | ------------------- |
| Subtree    | ✅ Easy     | ✅ Possible          |
| Root → v   | ✅ Easy     | ✅ Possible          |
| u → v      | ❌ Hard     | ✅ Designed for this |










Before building segment tree, check:

✔ tin unique hain
✔ subtree contiguous hai
✔ tout[root] = n-1
✔ timer exactly n pe khatam hua









🔴 3️⃣ Important Mistake

Querying range [tin[v], tout[v]] but forgetting only entry positions hold values.

Ye bahut subtle mistake hai 👇

Entry-only variant me:

arr[tin[v]] = value[v]

tout par koi value store nahi hoti.

Toh range query me dhyaan rakho:

Sirf entry positions meaningful hain.




LCA = Lowest Common Ancestor
Tree me do nodes ka sabse neeche wala common parent.






Because Euler tour exactly captures the path structure of the tree.

Between u aur v ke first appearance ke beech jo sabse upar ka node aata hai, wahi common ancestor hota hai.





Whenever we get subtree sum or subtree update think of euler tour and then go with it and that is it.







//O(1) LCA
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
vector<int> adj[N];

int n;
int timer = 0;

vector<int> euler;     // stores nodes in full euler tour
vector<int> depth;     // depth corresponding to euler positions
int first[N];          // first occurrence of node in euler tour
int level[N];          // depth of each node in tree

int st[20][2*N];       // sparse table (store index in euler array)
int logg[2*N];

void dfs(int v, int p, int d) {
    level[v] = d;

    first[v] = euler.size();
    euler.push_back(v);
    depth.push_back(d);

    for (auto child : adj[v]) {
        if (child == p) continue;

        dfs(child, v, d + 1);

        // add parent again when returning
        euler.push_back(v);
        depth.push_back(d);
    }
}

void build_sparse() {
    int m = depth.size();

    for (int i = 0; i < m; i++)
        st[0][i] = i;

    for (int j = 1; (1 << j) <= m; j++) {
        for (int i = 0; i + (1 << j) <= m; i++) {
            int l = st[j-1][i];
            int r = st[j-1][i + (1 << (j-1))];

            st[j][i] = (depth[l] < depth[r] ? l : r);
        }
    }

    logg[1] = 0;
    for (int i = 2; i <= m; i++)
        logg[i] = logg[i/2] + 1;
}

int lca(int u, int v) {
    int l = first[u];
    int r = first[v];

    if (l > r) swap(l, r);

    int len = r - l + 1;
    int j = logg[len];

    int left = st[j][l];
    int right = st[j][r - (1 << j) + 1];

    return (depth[left] < depth[right] ? euler[left] : euler[right]);
}

int main() {
    cin >> n;

    for (int i = 1; i <= n; i++)
        adj[i].clear();

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    euler.clear();
    depth.clear();

    dfs(1, 0, 0);   // assuming 1 is root
    build_sparse();

    int q;
    cin >> q;

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}
