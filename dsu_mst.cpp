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




