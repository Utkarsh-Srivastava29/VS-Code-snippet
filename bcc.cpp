#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<pair<int,int>>> bcc;   // all biconnected components
    vector<pair<int,int>> st;             // edge stack
    int timer;

    void dfs(int u, int parentEdge,
             vector<int>& vis,
             vector<int>& tin,
             vector<int>& low,
             vector<vector<pair<int,int>>>& g) {

        vis[u] = 1;
        tin[u] = low[u] = timer++;

        for (auto &ed : g[u]) {
            int v = ed.first;
            int id = ed.second;

            if (id == parentEdge) continue;

            if (!vis[v]) {
                // tree edge
                st.push_back({u, v});
                dfs(v, id, vis, tin, low, g);

                low[u] = min(low[u], low[v]);

                // biconnected component found
                if (low[v] >= tin[u]) {
                    vector<pair<int,int>> comp;
                    while (true) {
                        auto e = st.back();
                        st.pop_back();
                        comp.push_back(e);
                        if (e.first == u && e.second == v) break;
                    }
                    bcc.push_back(comp);
                }
            }
            else if (tin[v] < tin[u]) {
                // back edge
                low[u] = min(low[u], tin[v]);
                st.push_back({u, v});
            }
        }
    }

    vector<vector<pair<int,int>>> biconnectedComponents(
            int V, vector<vector<int>>& edges) {

        vector<vector<pair<int,int>>> g(V);
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            g[u].push_back({v, i});
            g[v].push_back({u, i});
        }

        vector<int> vis(V, 0), tin(V, -1), low(V, -1);
        timer = 0;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, -1, vis, tin, low, g);

                // leftover edges
                if (!st.empty()) {
                    bcc.push_back(st);
                    st.clear();
                }
            }
        }
        return bcc;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;

    vector<vector<int>> edges;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
    }

    Solution sol;
    auto bccs = sol.biconnectedComponents(V, edges);

    cout << "Number of biconnected components: " << bccs.size() << "\n";

    int idx = 1;
    for (auto &comp : bccs) {
        cout << "Component " << idx++ << ": ";
        for (auto &e : comp) {
            cout << "(" << e.first << "," << e.second << ") ";
        }
        cout << "\n";
    }

    return 0;
}
