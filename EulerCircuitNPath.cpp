struct EulerCircuit {
    int n, m;
    vector<vector<pair<int,int>>> g;
    vector<int> used;
    vector<int> circuit;

    EulerCircuit(int n) : n(n) {
        g.assign(n+1, {});
        m = 0;
    }

    // Adds an undirected edge
    void add_edge(int u, int v) {
        g[u].push_back({v, m});
        g[v].push_back({u, m});
        m++;
    }

    // Hierholzer DFS
    // Builds circuit in reverse order
    void dfs(int u) {
        while (!g[u].empty()) {
            auto [v, id] = g[u].back();
            g[u].pop_back();

            if (used[id]) continue;
            used[id] = 1;

            dfs(v);
        }
        circuit.push_back(u);                   // push when no edges left
    }

    // Returns Euler Circuit
    // start can be any vertex with edges
    vector<int> get_circuit(int start) {
        used.assign(m, 0);
        circuit.clear();
        dfs(start);
        reverse(circuit.begin(), circuit.end());
        return circuit;
    }
};
