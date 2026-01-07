/*
WHEN TO USE CENTROID DECOMPOSITION:
- The graph is a tree
- Queries depend on distance (not exact path)
- Typical problems: nearest node, count within distance K

OVERALL TIME COMPLEXITY:
- Preprocessing (building centroid tree): O(N log N)
- Each query / update: O(log N)
*/

struct CentroidDecomposition {
    int n;
    vector<vector<int>> g;

    // sz[v] = size of subtree rooted at v (ignoring removed nodes)
    vector<int> sz;

    // parent[v] = parent of v in centroid tree
    vector<int> parent;

    // removed[v] = whether v is already chosen as a centroid
    vector<bool> removed;

    CentroidDecomposition(int n) : n(n) {
        g.resize(n);
        sz.resize(n);
        parent.assign(n, -1);
        removed.assign(n, false);
    }

    /*
    Add an undirected edge

    Time Complexity:
    - O(1)
    */
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    /*
    DFS to compute subtree sizes

    What it does:
    - Computes sizes only for nodes not yet removed
    - Needed to decide centroid

    Time Complexity:
    - For one call: O(size of current subtree)
    - Over entire decomposition:
      Each level processes all remaining nodes
      Height of centroid tree = O(log N)

    => Total over all calls: O(N log N)
    */
    void dfs_size(int v, int p) {
        sz[v] = 1;

        for (int u : g[v]) {
            if (u == p || removed[u]) continue;
            dfs_size(u, v);
            sz[v] += sz[u];
        }
    }

    /*
    Find centroid of current subtree

    Logic:
    - If a child subtree has more than half the nodes,
      the centroid must lie there
    - Otherwise, current node is centroid

    Time Complexity:
    - Traverses down the subtree
    - Worst case: O(size of subtree)
    */
    int dfs_centroid(int v, int p, int total) {
        for (int u : g[v]) {
            if (u == p || removed[u]) continue;

            if (sz[u] > total / 2)
                return dfs_centroid(u, v, total);
        }
        return v;
    }

    /*
    Build centroid decomposition tree

    Steps:
    1. Compute subtree sizes
    2. Find centroid
    3. Mark centroid as removed
    4. Recurse on remaining subtrees

    Why it is efficient:
    - Each centroid splits the tree into parts of size ≤ N/2
    - Therefore, recursion depth is O(log N)

    Time Complexity:
    - dfs_size: O(size)
    - dfs_centroid: O(size)
    - Recursion depth: O(log N)

    => Total preprocessing complexity: O(N log N)
    */
    void build(int v, int p) {
        dfs_size(v, -1);                     // O(size of subtree)
        int c = dfs_centroid(v, -1, sz[v]);  // O(size of subtree)

        parent[c] = p;      // O(1)
        removed[c] = true;  // O(1)

        // Recurse on remaining subtrees
        for (int u : g[c]) {
            if (!removed[u])
                build(u, c);
        }
    }
};
