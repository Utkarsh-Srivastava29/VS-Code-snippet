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







