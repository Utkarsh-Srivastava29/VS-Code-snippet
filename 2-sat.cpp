struct TwoSAT {
    /*
        m = number of variables
        n = number of clauses (not strictly needed for logic, but kept)
        
        Each variable xi has two nodes:
        +i  →  i + 100000
        -i  → -i + 100000
    */
    int n, m;

    // g  = implication graph
    // rg = reverse implication graph
    vector<vector<int>> g, rg;

    // vis  = visited array for first DFS (ordering)
    // used = visited array for second DFS (SCC)
    // comp = component id of each node
    vector<int> vis, comp, used;

    // stack to store nodes in order of finishing time
    stack<int> st;

    // constructor
    TwoSAT(int vars, int clauses) {
        m = vars;
        n = clauses;

        // size is large to safely map [-m, m] with offset
        g.assign(m + 200000, {});
        rg.assign(m + 200000, {});
        vis.assign(m + 200000, 0);
        used.assign(m + 200000, 0);
        comp.assign(m + 200000, 0);
    }

    /*
        First DFS of Kosaraju:
        - runs on original graph
        - pushes nodes to stack after exploring all neighbors
    */
    void dfs(int u) {
        vis[u] = 1;
        for (auto &v : g[u]) {
            if (!vis[v]) dfs(v);
        }
        st.push(u);
    }

    /*
        Second DFS of Kosaraju:
        - runs on reversed graph
        - assigns all reachable nodes to the same SCC (component c)
    */
    void dfs_rev(int u, int c) {
        used[u] = 1;
        comp[u] = c;
        for (auto &v : rg[u]) {
            if (!used[v]) dfs_rev(v, c);
        }
    }

    /*
        Adds a clause (x OR y)

        (x OR y)  ≡  (!x → y) and (!y → x)
    */
    void add_clause(int x, int y) {
        // !x -> y
        g[-x + 100000].push_back(y + 100000);
        rg[y + 100000].push_back(-x + 100000);

        // !y -> x
        g[-y + 100000].push_back(x + 100000);
        rg[x + 100000].push_back(-y + 100000);
    }

    /*
        Solves the 2-SAT instance

        ans[i] = '+'  → variable (i+1) is true
        ans[i] = '-'  → variable (i+1) is false
    */
    bool solve(vector<char> &ans) {

        // Step 1: run DFS on all literals to get finishing order
        for (int i = -m; i <= m; i++) {
            if (i != 0 && !vis[i + 100000]) {
                dfs(i + 100000);
            }
        }

        // Step 2: process nodes in reverse finishing order on reverse graph
        int c = 0;
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            if (!used[u]) {
                dfs_rev(u, ++c);
            }
        }

        /*
            Step 3: check validity and extract assignment

            If xi and !xi are in the same SCC → impossible
            Otherwise, the one with higher component number is true
        */
        for (int i = 1; i <= m; i++) {
            if (comp[i + 100000] == comp[-i + 100000])
                return false;

            ans[i - 1] =
                (comp[-i + 100000] > comp[i + 100000]) ? '-' : '+';
        }

        return true;
    }
};
