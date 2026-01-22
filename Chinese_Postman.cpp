//centroid decomposition ek divide and conquer on trees technique hai jisme tree ko recursively centroid nodes pe divide kiya jata hai.
/* 
Each path passes through at least one centroid in the decomposition, so you count paths at each centroid and combine results. If a problem involves path properties (length, sum, XOR) affecting the whole tree, centroid decomposition might be your solution.
*/


//paths pass through the centoids and not through all the nodes direcly
/*
Every path in the tree passes through some centroid in the decomposition. This is the key key idea: process paths through centroids, not all paths directly.
*/ 

/*
These properties of all the paths passing through centroids and not direcly make our approach O(nlogn) instead of O(n^2) which would be directly if we do not solve the problem directly
*/

/*
The centroid tree formed after first taking the first centroid as the root and then recursively finding the centroids further on and then forming the trees will just generate the result 
The original tree do not matter after we have formed the centroid tree
The centroid tree has a depth of logn and each level we are doing O(n) work so overall complexity is O(nlogn)
*/


#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main() {
    int n, m;
    cin >> n >> m;   // n = number of vertices, m = number of edges

    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<int> degree(n, 0);

    int totalWeight = 0;

    // Initialize distances
    for (int i = 0; i < n; i++)
        dist[i][i] = 0;

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;   // make 0-based if input is 1-based

        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);

        degree[u]++;
        degree[v]++;
        totalWeight += w;
    }

    // Step 1: Find odd-degree vertices
    vector<int> odd;
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 == 1)
            odd.push_back(i);
    }

    // Step 2: Floyd–Warshall (all-pairs shortest paths)
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    int k = odd.size();

    // Step 3: DP to find minimum perfect matching on odd vertices
    // dp[mask] = minimum cost to pair vertices represented by mask
    vector<int> dp(1 << k, INF);
    dp[0] = 0;

    for (int mask = 0; mask < (1 << k); mask++) {
        int cnt = __builtin_popcount(mask);
        if (cnt % 2 != 0) continue;

        int first = -1;
        for (int i = 0; i < k; i++) {
            if (!(mask & (1 << i))) {
                first = i;
                break;
            }
        }

        if (first == -1) continue;

        for (int j = first + 1; j < k; j++) {
            if (!(mask & (1 << j))) {
                int newMask = mask | (1 << first) | (1 << j);
                dp[newMask] = min(
                    dp[newMask],
                    dp[mask] + dist[odd[first]][odd[j]]
                );
            }
        }
    }

    // Step 4: Total minimum cost
    int result = totalWeight + dp[(1 << k) - 1];

    cout << "Minimum Chinese Postman Tour Cost = " << result << "\n";
    return 0;
}


