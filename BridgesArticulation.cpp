/*
WHEN TO USE TARJAN (BRIDGES & ARTICULATION POINTS):
- The graph is undirected
- You need to find:
  • critical edges (bridges)
  • critical vertices (articulation points)
- Used in graph reliability / weak points problems

TIME COMPLEXITY:
- Single DFS over the graph
- Overall: O(N + M)
*/

struct Tarjan {
    int n;
    vector<vector<int>>g;

    // tin[v] = time when v is first visited in DFS
    // low[v] = lowest tin reachable from v (including back edges)
    vector<int>tin,low;

    // is_cut[v] = whether v is an articulation point
    vector<bool>is_cut;

    // list of all bridges in the graph
    vector<pair<int,int>>bridges;

    int timer;

    Tarjan(int n):n(n) {
        g.resize(n);
        tin.assign(n,0);
        low.assign(n,0);
        is_cut.assign(n,false);
        timer=0;
    }

    /*
    Add an undirected edge between u and v

    Just updates adjacency list
    Time Complexity: O(1)
    */
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    /*
    DFS traversal (Tarjan's algorithm)

    What happens here:
    - Assign discovery time (tin) to each node
    - Compute low-link values
    - Detect bridges and articulation points

    Why it's efficient:
    - Each node is visited exactly once
    - Each edge is considered at most twice
    - All operations inside DFS are constant time

    Time Complexity:
    => O(N + M)
    */
    void dfs(int v, int p) {
        tin[v]=low[v]=++timer;   // mark discovery time
        int children=0;            // count DFS children (needed for root case)

        for (int u:g[v]) {         // total over full DFS = O(M)
            if (u==p) continue;

            if (tin[u]) {
                // Back edge:
                // update low[v] using discovery time of u
                low[v]=min(low[v], tin[u]);
            } else {
                // Tree edge
                dfs(u,v);

                // propagate low-link value upwards
                low[v]=min(low[v],low[u]);

                // Bridge condition:
                // if u cannot reach an ancestor of v
                if (low[u]>tin[v])
                    bridges.push_back({v,u});

                // Articulation point condition (non-root):
                // removing v disconnects subtree of u
                if (low[u]>=tin[v] and p!=-1)
                    is_cut[v]=true;

                children++;
            }
        }

        // Articulation point condition for root:
        // root is articulation if it has more than one DFS child
        if (p==-1 and children>1)
            is_cut[v] = true;
    }
};
