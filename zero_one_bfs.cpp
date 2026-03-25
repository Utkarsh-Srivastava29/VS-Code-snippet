//Minimum number of edge flips to make a node reach all the nodes in a directed acyclic graph
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin>>n>>m;

    vector<vector<pair<int,int>>> g(n);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;

        g[u].push_back({v,0});
        g[v].push_back({u,1});
    }

    int ans = INF;

    for(int src=0;src<n;src++){
        deque<int> dq;
        vector<int> dist(n, INF);

        dist[src]=0;
        dq.push_front(src);

        while(!dq.empty()){
            int u = dq.front(); dq.pop_front();

            for(auto [v,w]: g[u]){
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    if(w==0) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }

        // count number of reversals used
        int cur = 0;
        bool ok = true;

        for(int i=0;i<n;i++){
            if(dist[i]==INF){
                ok=false;
                break;
            }
        }

        if(!ok) continue;

        // count edges used in shortest tree
        for(int u=0;u<n;u++){
            for(auto [v,w]: g[u]){
                if(dist[v] == dist[u] + w && w==1){
                    cur++;
                }
            }
        }

        ans = min(ans, cur);
    }

    if(ans==INF) cout<<-1<<"\n";
    else cout<<ans<<"\n";
}
