1.Version control systems use it to find merge points, file systems use it to find common directories
2.LCA (Lowest Common Ancestor) = do nodes ka sabse deep common ancestor, jise efficiently nikalne ke liye binary lifting (O(log n)) ya Euler + RMQ (O(1)) use karte hain.
3.LCA (Lowest Common Ancestor) = do nodes ka sabse neeche wala common ancestor, yani jab dono ko upar trace karein to jo pehla common node mile.
4.LCA important hai kyunki distance, path queries aur tree problems ko fast solve karne ke liye LCA zaroori hota hai (warna har query O(n) lagti).
5.Naive LCA approach: dono nodes ko root tak upar le jao, first common marked ancestor hi LCA hota hai (time O(h)).
Naive approach:-
  int lca(int u, int v, vector<int>& parent) {
    unordered_set<int> ancestors;

    while (u != 0) {
        ancestors.insert(u);
        u = parent[u];
    }

    while (v != 0) {
        if (ancestors.count(v))
            return v;
        v = parent[v];
    }

    return -1;
}


6.Binary Lifting se LCA O(log n) time mein milta hai by pehle depths equal karna aur phir dono nodes ko saath-saath upar jump karna.
  int lca(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);

    int diff = depth[u] - depth[v];

    // Step 1: bring u to same depth
    for (int i = 0; i < LOG; i++) {
        if (diff & (1 << i))
            u = up[u][i];
    }

    if (u == v)
        return u;

    // Step 2: lift both together
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0]; // parent is LCA
}


7.Binary Lifting preprocessing mein up[v][i] (2^i-th ancestor) aur depth[v] build karte hain in O(n log n), phir har LCA query O(log n) mein solve hoti hai.
  void dfs(int u, int parent) {
    up[u][0] = parent;
    for (int v : adj[u]) {
        if (v == parent) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

// Build binary lifting table
for (int j = 1; j < LOG; j++) {
    for (int i = 1; i <= n; i++) {
        if (up[i][j - 1] != 0)
            up[i][j] = up[ up[i][j - 1] ][j - 1];
    }
}




8.Depth equal karne ke baad, dono nodes ko largest possible binary jumps se upar le jaate hain jab tak unke parents same na ho — unka parent hi LCA hota hai.
  for (int i = LOG - 1; i >= 0; i--) {
    if (up[u][i] != up[v][i]) {
        u = up[u][i];
        v = up[v][i];
    }
}

return up[u][0];  // LCA


9.Same depth par aane ke baad, dono nodes ko highest power of 2 se upar jump karte hain jab tak unke ancestors alag ho — unka parent hi LCA hota hai.
  for (int i = LOG - 1; i >= 0; i--) {
    if (up[u][i] != 0 && up[u][i] != up[v][i]) {
        u = up[u][i];
        v = up[v][i];
    }
}

return up[u][0];  // LCA



10.Binary Lifting mein preprocessing O(n log n) lagta hai aur har LCA query O(log n) mein solve hoti hai.
  O(n log n + q log n)




11.Binary tree mein single LCA query ke liye simple recursive DFS use karo — time O(n), space O(h).
  class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q)
            return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right)
            return root;

        return left ? left : right;
    }
};





12.Binary tree mein LCA find karne ke liye recursive DFS use karo: agar p left mein aur q right mein mile, to current node LCA hai; warna jo subtree target return kare wahi upar propagate karo.
13.LCA ke multiple approaches hote hain: single query ke liye simple recursive O(n) solution kaafi hai, aur multiple queries ke liye Euler Tour + RMQ ya Binary Lifting better hai.
14.Recursive LCA ke base cases: agar node null ho to null return karo, aur agar node p ya q ho to wahi return karo.
15.Recursive LCA post-order traversal karta hai: left aur right subtree check karo, dono side se node mile to current node LCA hai, warna jo mila use upar return karo.
16.Recursive LCA implementation: base cases handle null/target, left aur right subtree search karo, dono side mile to root LCA hai, warna jo mila use return karo.
17.Example tree mein recursive LCA ka logic dikhaya: agar targets alag subtrees mein milte hain to root LCA, aur agar ek target doosre ka ancestor hai to wahi LCA.
18.Recursive LCA bottom-up pattern follow karta hai: children se result lo, combine karo, aur parent ko return karo — ye pattern tree problems mein common hai.
19.Euler Tour DFS se tree ko array mein flatten karta hai (length ≈ 2n−1), jisse LCA ko RMQ bana kar O(1) query mein solve kar sakte hain after preprocessing.
  DFS se Euler Tour banao: node enter karte hi record karo, har child se wapas aate hi parent ko phir record karo.
  const int MAXN = 200005;

int tour[2 * MAXN];
int tourDepth[2 * MAXN];
int first[MAXN];
vector<int> adj[MAXN];

int timer = 0;

void eulerTour(int v, int d) {
    first[v] = timer;
    tour[timer] = v;
    tourDepth[timer] = d;
    timer += 1;

    for (int c : adj[v]) {
        eulerTour(c, d + 1);

        tour[timer] = v;
        tourDepth[timer] = d;
        timer += 1;
    }
}

20.LCA ko Euler Tour par RMQ bana dete hain: first[u] aur first[v] ke beech minimum depth wala node hi LCA hota hai.
  int l = first[u];
int r = first[v];
if (l > r) swap(l, r);

int idx = rmq(l, r);   // returns index in tour with minimum depth
return tour[idx];


21.Sparse Table se tourDepth par RMQ bana kar LCA queries O(1) time mein solve kar sakte hain after O(n log n) preprocessing.
  #include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;

vector<int> adj[MAXN];

int tour[2 * MAXN];
int tourDepth[2 * MAXN];
int first[MAXN];

int st[2 * MAXN][LOG];
int logVal[2 * MAXN];

int timer = 0;
int N; // size of euler tour

// ---------------- Euler Tour ----------------
void eulerTour(int v, int parent, int d) {
    first[v] = timer;
    tour[timer] = v;
    tourDepth[timer] = d;
    timer++;

    for (int c : adj[v]) {
        if (c == parent) continue;

        eulerTour(c, v, d + 1);

        tour[timer] = v;
        tourDepth[timer] = d;
        timer++;
    }
}

// ---------------- Build Sparse Table ----------------
void buildSparseTable() {
    for (int i = 0; i < N; i++)
        st[i][0] = i;   // store index

    for (int j = 1; (1 << j) <= N; j++) {
        for (int i = 0; i + (1 << j) <= N; i++) {

            int left = st[i][j - 1];
            int right = st[i + (1 << (j - 1))][j - 1];

            if (tourDepth[left] < tourDepth[right])
                st[i][j] = left;
            else
                st[i][j] = right;
        }
    }
}

// ---------------- RMQ Query ----------------
int rmq(int L, int R) {
    int len = R - L + 1;
    int j = logVal[len];

    int left = st[L][j];
    int right = st[R - (1 << j) + 1][j];

    if (tourDepth[left] < tourDepth[right])
        return left;
    else
        return right;
}

// ---------------- LCA Query ----------------
int lca(int u, int v) {
    int L = first[u];
    int R = first[v];
    if (L > R) swap(L, R);

    int idx = rmq(L, R);
    return tour[idx];
}

// ---------------- Main ----------------
int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        adj[i].clear();

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    timer = 0;
    eulerTour(1, 0, 0);
    N = timer;

    // Precompute logs
    logVal[1] = 0;
    for (int i = 2; i <= N; i++)
        logVal[i] = logVal[i / 2] + 1;

    buildSparseTable();

    int q;
    cin >> q;

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}




22.Distance between two nodes in a tree = depth[u] + depth[v] − 2 × depth[LCA(u,v)] because the path goes up to LCA and then down.
23.Distance queries in a tree reduce to LCA queries: preprocess with DFS + Euler Tour + Sparse Table to answer each distance query in O(1).
24.To answer distance queries in a tree, preprocess using binary lifting for LCA in O(log n) and compute distance using
   depth[u] + depth[v] − 2 × depth[LCA(u,v)].

25.Build depth[] and binary lifting table using DFS, then for each query compute sum using
sum[u] + sum[v] − 2 × sum[LCA(u,v)].


26.Amortized preprocessing means spending O(nlogn) time upfronts ets you answer q queries in O(qlogn) total time.
27.Har path ko individually walk karne ki jagah LCA-based marking trick use karo, jisse total time O(n + m) ho jaata hai.
28.To count how many given paths pass through each node, mark endpoints using LCA and propagate counts upward with one DFS in O(n + m).








29.#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 200005;
const int LOG = 20;

vector<int> g[N];
int up[N][LOG];
int depth[N];
int cnt[N];

void dfs(int v, int p){
    up[v][0] = p;
    for(auto u : g[v]){
        if(u == p) continue;
        depth[u] = depth[v] + 1;
        dfs(u, v);
    }
}

int lca(int u, int v){
    if(depth[u] < depth[v]) swap(u,v);

    int d = depth[u] - depth[v];
    for(int j=LOG-1;j>=0;j--)
        if(d & (1<<j))
            u = up[u][j];

    if(u == v) return u;

    for(int j=LOG-1;j>=0;j--){
        if(up[u][j] != up[v][j]){
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

void dfs2(int v, int p){
    for(auto u : g[v]){
        if(u == p) continue;
        dfs2(u, v);
        cnt[v] += cnt[u];
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin >> n >> m;

    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs(1,0);

    for(int j=1;j<LOG;j++)
        for(int i=1;i<=n;i++)
            if(up[i][j-1])
                up[i][j] = up[up[i][j-1]][j-1];

    while(m--){
        int u,v;
        cin >> u >> v;

        int l = lca(u,v);

        cnt[u]++;
        cnt[v]++;
        cnt[l]--;

        if(up[l][0])
            cnt[up[l][0]]--;
    }

    dfs2(1,0);

    for(int i=1;i<=n;i++)
        cout << cnt[i] << " ";
}






30.Count nodes on path (u, v) by splitting at LCA and using a tree-difference trick: mark +1 at u and v, −2 at LCA (and −1 at parent of LCA if needed), then propagate with one DFS.
31.Mark each path in O(1) using +1 at u and v and −2 at LCA, then run one post-order DFS to propagate counts upward so each node stores how many paths pass through it.








32.#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 200005;
const int LOG = 20;

vector<int> g[N];
int up[N][LOG];
int depth[N];
int cnt[N];

void dfs(int v, int p){
    up[v][0] = p;
    for(auto u : g[v]){
        if(u == p) continue;
        depth[u] = depth[v] + 1;
        dfs(u, v);
    }
}

int lca(int u, int v){
    if(depth[u] < depth[v]) swap(u,v);

    int d = depth[u] - depth[v];

    for(int j=LOG-1;j>=0;j--)
        if(d & (1<<j))
            u = up[u][j];

    if(u == v) return u;

    for(int j=LOG-1;j>=0;j--){
        if(up[u][j] != up[v][j]){
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

void propagate(int v, int p){
    for(auto u : g[v]){
        if(u == p) continue;
        propagate(u, v);
        cnt[v] += cnt[u];
    }
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin >> n >> m;

    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    // Root = 1
    dfs(1,0);

    for(int j=1;j<LOG;j++)
        for(int i=1;i<=n;i++)
            if(up[i][j-1])
                up[i][j] = up[up[i][j-1]][j-1];

    // Process paths
    while(m--){
        int u,v;
        cin >> u >> v;

        int l = lca(u,v);

        cnt[u]++;
        cnt[v]++;
        cnt[l] -= 2;
    }

    // Propagate upward
    propagate(1,0);

    // Output edge usage
    // For each node v (except root),
    // cnt[v] = number of paths using edge (v -> parent[v])
    for(int i=2;i<=n;i++)
        cout << cnt[i] << " ";
}










33.#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 200005;
const int LOG = 20;

vector<pair<int,int>> g[N];   // {neighbor, edge_weight}
int up[N][LOG];
int depth[N];

int mxEdge[N][LOG];  // max edge weight to 2^k ancestor
int mxNode[N][LOG];  // max node value to 2^k ancestor

int val[N];          // node values

void dfs(int v, int p){
    for(auto it : g[v]){
        int u = it.first;
        int w = it.second;

        if(u == p) continue;

        depth[u] = depth[v] + 1;
        up[u][0] = v;

        mxEdge[u][0] = w;        // edge weight
        mxNode[u][0] = val[u];   // node value

        dfs(u, v);
    }
}

pair<int,int> query(int u, int v){
    int ansEdge = 0;
    int ansNode = max(val[u], val[v]);

    if(depth[u] < depth[v]) swap(u,v);

    int d = depth[u] - depth[v];

    for(int j=LOG-1;j>=0;j--){
        if(d & (1<<j)){
            ansEdge = max(ansEdge, mxEdge[u][j]);
            ansNode = max(ansNode, mxNode[u][j]);
            u = up[u][j];
        }
    }

    if(u == v){
        ansNode = max(ansNode, val[u]);
        return {ansEdge, ansNode};
    }

    for(int j=LOG-1;j>=0;j--){
        if(up[u][j] != up[v][j]){
            ansEdge = max(ansEdge, mxEdge[u][j]);
            ansEdge = max(ansEdge, mxEdge[v][j]);

            ansNode = max(ansNode, mxNode[u][j]);
            ansNode = max(ansNode, mxNode[v][j]);

            u = up[u][j];
            v = up[v][j];
        }
    }

    // last step to reach LCA
    ansEdge = max(ansEdge, mxEdge[u][0]);
    ansEdge = max(ansEdge, mxEdge[v][0]);

    ansNode = max(ansNode, mxNode[u][0]);
    ansNode = max(ansNode, mxNode[v][0]);

    // include LCA node value
    int l = up[u][0];
    ansNode = max(ansNode, val[l]);

    return {ansEdge, ansNode};
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for(int i=1;i<=n;i++)
        cin >> val[i];

    for(int i=0;i<n-1;i++){
        int x,y,w;
        cin >> x >> y >> w;
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }

    // root = 1
    mxNode[1][0] = val[1];
    dfs(1,0);

    for(int j=1;j<LOG;j++){
        for(int i=1;i<=n;i++){
            int p = up[i][j-1];
            if(p){
                up[i][j] = up[p][j-1];

                mxEdge[i][j] = max(mxEdge[i][j-1],
                                   mxEdge[p][j-1]);

                mxNode[i][j] = max(mxNode[i][j-1],
                                   mxNode[p][j-1]);
            }
        }
    }

    int q;
    cin >> q;

    while(q--){
        int u,v;
        cin >> u >> v;

        auto ans = query(u,v);

        cout << "Max Edge = " << ans.first
             << " , Max Node = " << ans.second << "\n";
    }
}







34.#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 200005;
const int LOG = 20;

vector<pair<int,int>> g[N];
int up[N][LOG];
int depth[N];

int mxEdge[N][LOG], mxNode[N][LOG];
int sumEdge[N][LOG], sumNode[N][LOG];

int val[N];

void dfs(int v, int p){
    for(auto it : g[v]){
        int u = it.first;
        int w = it.second;

        if(u == p) continue;

        depth[u] = depth[v] + 1;
        up[u][0] = v;

        mxEdge[u][0] = w;
        mxNode[u][0] = val[u];

        sumEdge[u][0] = w;
        sumNode[u][0] = val[u];

        dfs(u, v);
    }
}

struct Ans{
    int maxEdge, maxNode;
    int sumEdge, sumNode;
};

Ans query(int u, int v){
    int ansMaxEdge = 0;
    int ansMaxNode = max(val[u], val[v]);

    int ansSumEdge = 0;
    int ansSumNode = val[u] + val[v];

    if(depth[u] < depth[v]) swap(u,v);

    int d = depth[u] - depth[v];

    for(int j=LOG-1;j>=0;j--){
        if(d & (1<<j)){
            ansMaxEdge = max(ansMaxEdge, mxEdge[u][j]);
            ansMaxNode = max(ansMaxNode, mxNode[u][j]);

            ansSumEdge += sumEdge[u][j];
            ansSumNode += sumNode[u][j];

            u = up[u][j];
        }
    }

    if(u == v){
        ansSumNode -= val[u]; // avoid double count
        return {ansMaxEdge, ansMaxNode,
                ansSumEdge, ansSumNode};
    }

    for(int j=LOG-1;j>=0;j--){
        if(up[u][j] != up[v][j]){

            ansMaxEdge = max(ansMaxEdge, mxEdge[u][j]);
            ansMaxEdge = max(ansMaxEdge, mxEdge[v][j]);

            ansMaxNode = max(ansMaxNode, mxNode[u][j]);
            ansMaxNode = max(ansMaxNode, mxNode[v][j]);

            ansSumEdge += sumEdge[u][j];
            ansSumEdge += sumEdge[v][j];

            ansSumNode += sumNode[u][j];
            ansSumNode += sumNode[v][j];

            u = up[u][j];
            v = up[v][j];
        }
    }

    // last step
    ansMaxEdge = max(ansMaxEdge, mxEdge[u][0]);
    ansMaxEdge = max(ansMaxEdge, mxEdge[v][0]);

    ansMaxNode = max(ansMaxNode, mxNode[u][0]);
    ansMaxNode = max(ansMaxNode, mxNode[v][0]);

    ansSumEdge += sumEdge[u][0];
    ansSumEdge += sumEdge[v][0];

    ansSumNode += sumNode[u][0];
    ansSumNode += sumNode[v][0];

    int l = up[u][0];

    ansMaxNode = max(ansMaxNode, val[l]);
    ansSumNode += val[l];

    return {ansMaxEdge, ansMaxNode,
            ansSumEdge, ansSumNode};
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for(int i=1;i<=n;i++)
        cin >> val[i];

    for(int i=0;i<n-1;i++){
        int x,y,w;
        cin >> x >> y >> w;
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }

    sumNode[1][0] = val[1];
    mxNode[1][0] = val[1];

    dfs(1,0);

    for(int j=1;j<LOG;j++){
        for(int i=1;i<=n;i++){
            int p = up[i][j-1];
            if(p){
                up[i][j] = up[p][j-1];

                mxEdge[i][j] = max(mxEdge[i][j-1], mxEdge[p][j-1]);
                mxNode[i][j] = max(mxNode[i][j-1], mxNode[p][j-1]);

                sumEdge[i][j] = sumEdge[i][j-1] + sumEdge[p][j-1];
                sumNode[i][j] = sumNode[i][j-1] + sumNode[p][j-1];
            }
        }
    }

    int q;
    cin >> q;

    while(q--){
        int u,v;
        cin >> u >> v;

        auto ans = query(u,v);

        cout << "MaxEdge=" << ans.maxEdge
             << " MaxNode=" << ans.maxNode
             << " SumEdge=" << ans.sumEdge
             << " SumNode=" << ans.sumNode
             << "\n";
    }
}










35.Precompute prefix count of marked nodes from root to each node, then for each query use
count[u] + count[v] − count[lca] − count[parent(lca)] to get marked nodes on path in O(log n).



36.count[u] + count[v] − count[lca] − count[parent(lca)] to get marked nodes on path in O(log n).
There are some nodes marked zero or 1 and some are marked as 0 and  we are finding the values for the path between the nodes A and B and then we are considering the path from root to the node u and from the root to the node v and then removing the values from the root to the lca and from the root to the parent[lca] and so on.




37.We mark endpoints +1, subtract at LCA and its parent to prevent overflow, then propagate counts upward to compute how many paths pass through each node




38.Agar tum parent(lca) par decrement nahi karoge,
   toh counts LCA ke upar ke nodes tak leak ho jayenge


39.Difference array ka concept arrays se trees tak extend hota hai.
   cnt[u]++
   cnt[v]++
   cnt[lca]--
   cnt[parent(lca)]--





40.Extend binary lifting by storing maximum edge weight for each 2^j jump, and compute path maximum while climbing to LCA in O(log n).
41.Weighted Binary Lifting extends LCA by storing aggregated path information (like max edge) for every 2^i jump, allowing path queries in O(log n).
42.Only switch to Euler tour if you are certain time limit requires O(1) queries.
43.Common LCA mistakes include not handling ancestor cases, using wrong stopping condition while climbing, and indexing errors.
44.





