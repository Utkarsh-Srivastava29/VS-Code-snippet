/*
WHEN TO USE HLD:
- The graph is a tree
- Queries are on paths between two nodes (u ->v)
- The query can be answered using a range data structure
  (segment tree / BIT / RMQ)

TIME COMPLEXITY:
- Preprocessing (DFS + decomposition): O(N)
- One path query: O(log^2 N)
- Total: O((N + Q) * log^2 N)
*/

struct HLD {
    int n;
    vector<vector<int>>g;

    // basic tree info
    vector<int>parent,depth,sz;

    // HLD-specific arrays
    vector<int>heavy;   // heavy child of each node
    vector<int>head;    // head of the current chain
    vector<int>pos;     // position of node in linearized array
    int cur_pos;

    HLD(int n) : n(n) {
        g.resize(n);
        parent.resize(n);
        depth.resize(n);
        sz.resize(n);
        heavy.assign(n, -1);
        head.resize(n);
        pos.resize(n);
        cur_pos=0;
    }

    // Adds an undirected edge
    // Time: O(1)
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    /*
    First DFS:
    - sets parent of each node
    - computes depth
    - computes subtree size
    - selects heavy child (child with max subtree size)

    Why it works:
    - every node is visited once
    - every edge is used twice (u -> v, v -> u)

    Time Complexity: O(N)
    */
    int dfs(int v, int p) {
        parent[v]=p;
        sz[v]=1;
        int max_subtree=0;

        for (int u:g[v]) {     // overall across DFS: O(N)
            if (u==p) continue;

            depth[u]=depth[v]+1;
            int sub=dfs(u,v);
            sz[v]+=sub;

            // pick the child with the largest subtree
            if (sub>max_subtree){
                max_subtree=sub;
                heavy[v]=u;
            }
        }
        return sz[v];
    }

    /*
    Second DFS (decomposition):
    - assigns each node to a chain
    - assigns a position in the base array

    Key idea:
    - heavy edge continues the same chain
    - light edges start new chains

    Each node is processed exactly once
    => Time Complexity: O(N)
    */
    void decompose(int v,int h) {
        head[v]=h;          // head of current chain
        pos[v]=cur_pos++;  // assign position in base array

        // continue along heavy edge (if it exists)
        if (heavy[v]!=-1)
            decompose(heavy[v],h);

        // start new chains for light children
        for (int u:g[v]) {
            if (u!=parent[v] and u!=heavy[v])
                decompose(u,u);
        }
    }

    /*
    Query on path u -> v

    Logic:
    - while nodes are in different chains,
      move the deeper chain upwards
    - each move jumps one full chain

    Why it's fast:
    - number of chains crossed ≤ O(log N)
    - each chain corresponds to a segment query

    Time Complexity per query:
    O(log N) chain jumps
    × O(log N) segment query
    = O(log^2 N)
    */
    void query_path(int u,int v){
        while (head[u]!=head[v]){   // at most log N iterations
            if (depth[head[u]]<depth[head[v]])
                swap(u,v);

            // query range: [pos[head[u]],pos[u]]
            u=parent[head[u]];
        }

        // now both nodes are in the same chain
        if (depth[u]>depth[v]) swap(u,v);

        // query range: [pos[u], pos[v]]
    }
};
