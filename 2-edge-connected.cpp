#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int timer;
    vector<int> tin, low;
    vector<bool> isBridge;
    vector<vector<pair<int,int>>> g; // (to, edge_id)

    void dfs_bridge(int u, int parentEdge) {
        tin[u] = low[u] = timer++;

        for (auto &ed : g[u]) {
            int v = ed.first;
            int id = ed.second;

            if (id == parentEdge) continue;

            if (tin[v] == -1) {
                dfs_bridge(v, id);
                low[u] = min(low[u], low[v]);

                if (low[v] > tin[u]) {
                    isBridge[id] = true;
                }
            } else {
                low[u] = min(low[u], tin[v]);
            }
        }
    }

    void dfs_component(int u, vector<int>& comp, vector<bool>& vis) {
        vis[u] = true;
        comp.push_back(u);

        for (auto &ed : g[u]) {
            int v = ed.first;
            int id = ed.second;

            if (isBridge[id]) continue;
            if (!vis[v]) dfs_component(v, comp, vis);
        }
    }

    vector<vector<int>> twoEdgeConnectedComponents(
            int V, vector<vector<int>>& edges) {

        g.assign(V, {});
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            g[u].push_back({v, i});
            g[v].push_back({u, i});
        }

        tin.assign(V, -1);
        low.assign(V, -1);
        isBridge.assign(edges.size(), false);
        timer = 0;

        // Step 1: find bridges
        for (int i = 0; i < V; i++) {
            if (tin[i] == -1) {
                dfs_bridge(i, -1);
            }
        }

        // Step 2: build 2-edge-connected components
        vector<bool> vis(V, false);
        vector<vector<int>> components;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                vector<int> comp;
                dfs_component(i, comp, vis);
                components.push_back(comp);
            }
        }
        return components;
    }
};
