Q1.Checking Existence of Edge Length Limited Paths Task: Given edges with weights and queries (u,v,limit) determine if u and v are connected using only edges with weight<limit.
Solution:-
class Solution {
public:
    vector<int> parent, rankv;

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (rankv[a] < rankv[b]) swap(a, b);
        parent[b] = a;
        if (rankv[a] == rankv[b]) rankv[a]++;
    }

    vector<bool> distanceLimitedPathsExist(
        int n,
        vector<vector<int>>& edges,
        vector<vector<int>>& queries
    ) {
        // Sort edges by weight
        sort(edges.begin(), edges.end(),
             [](auto &a, auto &b) {
                 return a[2] < b[2];
             });

        // Store queries with original indices
        vector<array<int,4>> q;
        for (int i = 0; i < queries.size(); i++) {
            q.push_back({queries[i][2], queries[i][0], queries[i][1], i});
        }

        // Sort queries by limit
        sort(q.begin(), q.end());

        parent.resize(n);
        rankv.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;

        vector<bool> ans(queries.size());
        int edgePtr = 0;

        for (auto &[limit, u, v, idx] : q) {
            // Add all edges with weight < limit
            while (edgePtr < edges.size() && edges[edgePtr][2] < limit) {
                unite(edges[edgePtr][0], edges[edgePtr][1]);
                edgePtr++;
            }
            // Check connectivity
            ans[idx] = (find(u) == find(v));
        }

        return ans;
    }
};












Point 2.Core patterns: cycle detection, component counting, hub nodes, offline queries, reverse time trick. These cover most DSU problems you will encounter. Practice them until the patterns become automatic.




Point 3.If you can swap item A with B, and swap B with C, can you swap A with C?
        Yes. You swap A ↔ B, then B ↔ C, effectively swapping A and C.
        Transitivity means swap relationships form groups. Any two items in the same group can be swapped (eventually). DSU tracks these groups perfectly.
        This observation solves problems about rearranging elements through allowed swaps.




Point 4.Sometimes nodes are not numbers 1 … n. They might be strings, emails, or coordinates. You need to map these complex objects to integer IDs before using DSU. Use a hash map: when you see a new object, assign it the next available ID.
Then proceed with standard DSU on the IDs. This pattern appears whenever the “nodes” are not naturally numbered. The mapping itself takes O(1) amortized per lookup with a hash map, so it does not change the overall time complexity.






Point 5.If you have a set of items that are all connected to each other (a clique), adding edges between every pair is O(k²) for k items. Too slow for large cliques.
       Instead, create a virtual “hub” node. Connect every item to the hub. Now you have k edges instead of k². Items in the same clique share the hub as their leader.
       This pattern appears when problems have large groups that must be unified.
       Space complexity is O(n) for the data structures used.




Point 6.In case of dsu with rank we can say that using induction we can prove that we need 1 for 2^0(base case) and 2^r(induction hypothesis) for rank 2^r+2^r final for the final part that is 2^(r+1)










Point 7.Union by rank has the height of the tree equal to rank withour path compression else the height changes 












Spanning Tree:-
1.A spanning tree is a subgraph that connects all the nodes using exactly n-1 edges and gives the maximum connectivity.No cycle is allowed.Remove an edge and the graph becomes disconnected.This is the foundation of the mst.
    
2.A Minimum Spanning Tree (MST) connects all nodes of a graph with minimum possible total edge weight. If multiple spanning trees exist, the MST is the cheapest one. It’s useful for problems like connecting cities at the lowest construction cost.
An MST is not always unique—when edges have equal weights, multiple MSTs can have the same total cost.
    
3.Cut Property kehta hai ki agar graph ko do groups me baant do, to in dono groups ko jodne wali sabse sasti edge hamesha kisi na kisi Minimum Spanning Tree (MST) ka hissa hoti hai.
  Iska matlab hai ki is edge ko choose karna safe hota hai.
  Isi rule par Kruskal aur Prim algorithms kaam karte hain.
    
4.Kisi bhi cycle me sabse heavy edge kabhi bhi MST ka hissa nahi hoti (jab tak weights equal na hon).
  Isliye aisi edge ko safe tarike se hata sakte hain.
  Ye rule MST algorithms ko samajhne aur galat edges ko remove karne me help karta hai.
    
5.The time complexity of krushkal algorithm is ElogE.
  So the bottleneck is sorting. If edges are already sorted, Kruskal runs in O(Ealpha(V)) where alpha is the inverse ackermann function.Space is O(V).

6.Prim ek node se shuru hota hai aur har step pe blob ke bahar ka sabse paas (cheapest) node andar kheench leta hai.

7.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<bool> inMST(n, false);
    priority_queue<array<int,3>, vector<array<int,3>>, greater<>> pq;

    // (weight, node, parent)
    pq.push({0, 0, -1});

    int mstCost = 0;
    vector<pair<int,int>> mstEdges;

    while(!pq.empty()) {
        auto [wt, u, parent] = pq.top();
        pq.pop();

        if(inMST[u]) continue;

        inMST[u] = true;
        mstCost += wt;

        if(parent != -1) {
            mstEdges.push_back({parent, u});
        }

        for(auto [v, w] : adj[u]) {
            if(!inMST[v]) {
                pq.push({w, v, u});
            }
        }
    }

    cout << "MST Cost: " << mstCost << "\n";
    cout << "Edges in MST:\n";
    for(auto [u, v] : mstEdges) {
        cout << u << " " << v << "\n";
    }

    return 0;
}






8.
Prim’s algorithm runs in O(E log V) using a binary heap, which is simple and efficient for most cases.
With a Fibonacci heap, it can run in O(E + V log V), which is better for dense graphs.
For sparse graphs (E ≈ V), Prim and Kruskal perform similarly, while for dense graphs (E ≈ V²), Prim is usually faster.
The space complexity is O(V).







9.
When the graph is stored a adjacency list then use prims and when want a simple implementation we can go with kruskal also.Use krushkal when the graph is already sorted because then we do not need to use the extra time complexity for priority queue.








10.Prims works better when we want to have it for the specific starting node.



11.
Agar graph disconnected hai, to single MST exist nahi karta.

Is case me result hota hai Minimum Spanning Forest:

har connected component ka apna MST hota hai.

Kruskal’s algorithm automatically is case ko handle kar leta hai:

bas n−1 se kam edges add hongi

har component apna tree bana lega.

Prim’s algorithm sirf starting node ke component ko cover karta hai.

Agar Prim se poora forest chahiye:

Prim ko har component ke ek node se alag-alag run karo.









12.when we want mst for each connected component then the prim's need to be run again and again as it starts from the starting node and hence we need to update that accordingly.
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<bool> visited(n, false);
    priority_queue<
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<>
    > pq;

    vector<tuple<int,int,int>> forest; // edges of spanning forest
    int totalCost = 0;

    // Run Prim from every unvisited node
    for(int start = 0; start < n; start++) {

        if(visited[start]) continue;

        // start a new component
        visited[start] = true;

        for(auto [v, w] : adj[start]) {
            pq.push({w, start, v});
        }

        while(!pq.empty()) {
            auto [w, u, v] = pq.top();
            pq.pop();

            if(visited[v]) continue;

            visited[v] = true;
            forest.push_back({u, v, w});
            totalCost += w;

            for(auto [next, wt] : adj[v]) {
                if(!visited[next]) {
                    pq.push({wt, v, next});
                }
            }
        }
    }

    cout << "Total Cost of Spanning Forest: " << totalCost << "\n";
    cout << "Edges in Spanning Forest:\n";
    for(auto [u, v, w] : forest) {
        cout << u << " " << v << " " << w << "\n";
    }

    return 0;
}







13.We can go with the prims because we have not been edges and they are dense and we can calculate them on the fly
//O(n*n)
#include <bits/stdc++.h>
using namespace std;

int manhattan(vector<int>& a, vector<int>& b) {
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> points(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> points[i][0] >> points[i][1];
    }

    vector<int> minDist(n, INT_MAX);
    vector<bool> inMST(n, false);

    minDist[0] = 0;   // start from point 0
    int totalCost = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;

        // pick closest non-MST point
        for (int j = 0; j < n; j++) {
            if (!inMST[j] && (u == -1 || minDist[j] < minDist[u])) {
                u = j;
            }
        }

        inMST[u] = true;
        totalCost += minDist[u];

        // update distances
        for (int v = 0; v < n; v++) {
            if (!inMST[v]) {
                int cost = manhattan(points[u], points[v]);
                minDist[v] = min(minDist[v], cost);
            }
        }
    }

    cout << totalCost << "\n";
    return 0;
}








14.
Use Prim when the graph is dense or complete and edges are computed on demand.
Use Kruskal when the graph is sparse, edges are explicitly given, or when you need a spanning forest.









15.https://leetcode.com/problems/min-cost-to-connect-all-points/description/
#include <bits/stdc++.h>
using namespace std;

int manhattan(vector<int>& a, vector<int>& b) {
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> points(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> points[i][0] >> points[i][1];
    }

    vector<bool> visited(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    pq.push({0, 0});   // (cost, node)
    int totalCost = 0;

    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;
        totalCost += cost;

        // generate edges on-the-fly
        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                int dist = manhattan(points[u], points[v]);
                pq.push({dist, v});
            }
        }
    }

    cout << totalCost << "\n";
    return 0;
}





16.
MST algorithms also work on complete graphs if you generate edges on demand.

Prim’s algorithm is preferable when creating all edges beforehand is too costly in time or memory.

Compute edge weights on the fly to save memory—this is key for geometric MST problems and is widely used in clustering and network design.







17.Component detection and merging are the core concepts of dsu union find.









18.Distinct weights ⇒ unique MST; equal weights ⇒ MST may not be unique.





19.
#include <bits/stdc++.h>
using namespace std;

/*
 DSU (Disjoint Set Union) / Union-Find
 Used for building the MST with Kruskal's algorithm
*/
struct DSU {
    vector<int> parent, rankv;

    DSU(int n) : parent(n), rankv(n, 0) {
        // initially each node is its own parent
        iota(parent.begin(), parent.end(), 0);
    }

    // find with path compression
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    // union by rank
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;   // already connected

        if (rankv[a] < rankv[b]) swap(a, b);
        parent[b] = a;
        if (rankv[a] == rankv[b]) rankv[a]++;
        return true;
    }
};

/*
 For LCA + max-edge query
 LOG = log2(max nodes)
*/
static const int LOG = 20;

/*
 adj[u] = {v, weight} → MST adjacency list
*/
vector<vector<pair<int,int>>> adj;

/*
 depth[u] = depth of node u in MST tree
 up[k][u] = 2^k-th ancestor of u
 mx[k][u] = maximum edge weight from u to up[k][u]
*/
vector<int> depth;
int up[LOG][100005];
int mx[LOG][100005];

/*
 DFS to initialize:
 - depth
 - immediate parent (up[0])
 - edge weight to parent (mx[0])
*/
void dfs(int u, int parent, int w) {
    up[0][u] = parent;
    mx[0][u] = w;

    for (auto [v, wt] : adj[u]) {
        if (v == parent) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u, wt);
    }
}

/*
 Finds the maximum edge weight on the path between u and v in MST
 Uses binary lifting (LCA technique)
*/
int maxEdgeOnPath(int u, int v) {
    int ans = 0;

    // make u and v at same depth
    if (depth[u] < depth[v]) swap(u, v);

    int diff = depth[u] - depth[v];
    for (int i = 0; i < LOG; i++) {
        if (diff & (1 << i)) {
            ans = max(ans, mx[i][u]);
            u = up[i][u];
        }
    }

    // if same node, done
    if (u == v) return ans;

    // lift both nodes up until LCA
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            ans = max(ans, mx[i][u]);
            ans = max(ans, mx[i][v]);
            u = up[i][u];
            v = up[i][v];
        }
    }

    // last step to LCA
    ans = max(ans, mx[0][u]);
    ans = max(ans, mx[0][v]);

    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;

    /*
     edges[i] = {u, v, w}
    */
    vector<array<int,3>> edges(m);
    for (int i = 0; i < m; i++)
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];

    // sort edges by weight for Kruskal
    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b) {
             return a[2] < b[2];
         });

    DSU dsu(n);
    adj.assign(n, {});

    // marks whether edge is in MST
    vector<bool> inMST(m, false);

    long long mstCost = 0;
    int usedEdges = 0;

    /*
     Step 1: Build MST using Kruskal
    */
    for (int i = 0; i < m; i++) {
        auto [u, v, w] = edges[i];
        if (dsu.unite(u, v)) {
            inMST[i] = true;
            mstCost += w;
            usedEdges++;

            // add edge to MST adjacency list
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }

    // if MST does not exist
    if (usedEdges != n - 1) {
        cout << "No MST exists\n";
        return 0;
    }

    /*
     Step 2: Prepare LCA + max edge tables
    */
    depth.assign(n, 0);
    dfs(0, -1, 0);

    // binary lifting preprocessing
    for (int i = 1; i < LOG; i++) {
        for (int v = 0; v < n; v++) {
            if (up[i-1][v] == -1) {
                up[i][v] = -1;
                mx[i][v] = mx[i-1][v];
            } else {
                up[i][v] = up[i-1][ up[i-1][v] ];
                mx[i][v] = max(mx[i-1][v],
                               mx[i-1][ up[i-1][v] ]);
            }
        }
    }

    /*
     Step 3: Try replacing one MST edge using each non-MST edge
     and compute second best MST
    */
    long long secondBest = LLONG_MAX;

    for (int i = 0; i < m; i++) {
        if (inMST[i]) continue;

        auto [u, v, w] = edges[i];

        // find maximum edge on MST path between u and v
        int maxEdge = maxEdgeOnPath(u, v);

        // candidate MST cost
        long long candidate = mstCost + w - maxEdge;

        if (candidate > mstCost)
            secondBest = min(secondBest, candidate);
    }

    cout << secondBest << "\n";
}














20.O(k · E log E)
#include <bits/stdc++.h>
using namespace std;

/* ---------- DSU ---------- */
struct DSU {
    vector<int> p;
    DSU(int n) : p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        p[b] = a;
        return true;
    }
};

/* ---------- Build MST while skipping forbidden edges ---------- */
long long buildMST(int n, vector<array<int,3>>& edges,
                   set<int>& forbid, vector<int>& used) {
    DSU dsu(n);
    long long cost = 0;
    used.clear();

    for (int i = 0; i < edges.size(); i++) {
        if (forbid.count(i)) continue;
        auto [w,u,v] = edges[i];
        if (dsu.unite(u,v)) {
            cost += w;
            used.push_back(i);
        }
    }
    return (used.size() == n-1 ? cost : LLONG_MAX);
}

/* ---------- k-th MST ---------- */
long long kthMST(int n, vector<array<int,3>> edges, int k) {
    sort(edges.begin(), edges.end());   // by weight

    using State = pair<long long, pair<set<int>, vector<int>>>;
    priority_queue<State, vector<State>, greater<State>> pq;

    set<int> empty;
    vector<int> used;
    long long first = buildMST(n, edges, empty, used);
    if (first == LLONG_MAX) return -1;

    pq.push({first, {empty, used}});

    for (int i = 1; i < k; i++) {
        auto [cost, st] = pq.top(); pq.pop();
        auto forbid = st.first;
        auto mstEdges = st.second;

        for (int e : mstEdges) {
            set<int> nf = forbid;
            nf.insert(e);
            vector<int> nu;
            long long nc = buildMST(n, edges, nf, nu);
            if (nc != LLONG_MAX)
                pq.push({nc, {nf, nu}});
        }
    }
    return pq.top().first;
}

/* ---------- Example ---------- */
int main() {
    int n = 4, k = 3;
    vector<array<int,3>> edges = {
        {1,0,1}, {2,1,2}, {3,2,3}, {4,0,3}, {5,0,2}
    };
    cout << kthMST(n, edges, k) << "\n";
}








21.
MSTs are widely used in network design (roads, cables, pipelines) to connect all nodes at the minimum total cost.

In clustering, cutting the largest-weight edges of an MST helps split data into clusters (single-linkage clustering).

MST algorithms are also used as building blocks in approximation algorithms for NP-hard problems, such as the Traveling Salesman Problem (TSP).










22.Travelling salesman problem is NP-hard.









23.Prims ke liye alag alag component ke liye hamein loop chalana pdega but for the case of the different spanning tree of different connected components krushkal will be beneficial
