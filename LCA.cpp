#include <bits/stdc++.h>
using namespace std;

/* ===== LCA STRUCT (UNCHANGED) ===== */
struct LCA {
    int n, LOG;
    vector<vector<pair<int,int>>> g;
    vector<vector<int>> up;
    vector<int> depth;

    vector<vector<long long>> mx, mn, sm, xr, gc;

    LCA(int n) : n(n) {
        LOG = 20;
        g.resize(n + 1);
        depth.resize(n + 1);

        up.assign(n + 1, vector<int>(LOG));
        mx.assign(n + 1, vector<long long>(LOG, 0));
        mn.assign(n + 1, vector<long long>(LOG, LLONG_MAX));
        sm.assign(n + 1, vector<long long>(LOG, 0));
        xr.assign(n + 1, vector<long long>(LOG, 0));
        gc.assign(n + 1, vector<long long>(LOG, 0));
    }

    void add_edge(int u, int v, int w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    void dfs(int v, int p, int w) {
        up[v][0] = p;
        mx[v][0] = w;
        mn[v][0] = w;
        sm[v][0] = w;
        xr[v][0] = w;
        gc[v][0] = w;

        for (auto [u, wt] : g[v]) {
            if (u == p) continue;
            depth[u] = depth[v] + 1;
            dfs(u, v, wt);
        }
    }

    void build(int root = 1) {
        dfs(root, 0, 0);

        for (int k = 1; k < LOG; k++) {
            for (int v = 1; v <= n; v++) {
                int mid = up[v][k-1];
                up[v][k] = up[mid][k-1];

                mx[v][k] = max(mx[v][k-1], mx[mid][k-1]);
                mn[v][k] = min(mn[v][k-1], mn[mid][k-1]);
                sm[v][k] = sm[v][k-1] + sm[mid][k-1];
                xr[v][k] = xr[v][k-1] ^ xr[mid][k-1];
                gc[v][k] = std::gcd(gc[v][k-1], gc[mid][k-1]);
            }
        }
    }

    struct Answer {
        long long mx, mn, sm, xr, gc;
    };

    Answer query(int u, int v) {
        Answer res;
        res.mx = 0;
        res.mn = LLONG_MAX;
        res.sm = 0;
        res.xr = 0;
        res.gc = 0;

        auto merge = [&](int node, int k) {
            res.mx = max(res.mx, mx[node][k]);
            res.mn = min(res.mn, mn[node][k]);
            res.sm += sm[node][k];
            res.xr ^= xr[node][k];
            res.gc = std::gcd(res.gc, gc[node][k]);
        };

        if (depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];
        for (int k = 0; k < LOG; k++) {
            if (diff & (1 << k)) {
                merge(u, k);
                u = up[u][k];
            }
        }

        if (u == v) return res;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[u][k] != up[v][k]) {
                merge(u, k);
                merge(v, k);
                u = up[u][k];
                v = up[v][k];
            }
        }

        merge(u, 0);
        merge(v, 0);

        return res;
    }
};
/* ===== END OF LCA STRUCT ===== */


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    LCA lca(n);

    // input edges
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        lca.add_edge(u, v, w);
    }

    // preprocess LCA tables
    lca.build(1);   // root the tree at node 1
    //keeping the code as one based indexing

    int q;
    cin >> q;

    while (q--) {
        int u, v;
        cin >> u >> v;

        auto ans = lca.query(u, v);

        // print all aggregates on path u -> v
        cout << ans.mx << " "
             << ans.mn << " "
             << ans.sm << " "
             << ans.xr << " "
             << ans.gc << "\n";
    }

    return 0;
}
