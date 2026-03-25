//Minimum number of edge flips to make a node reach all the nodes in a directed acyclic graph
//lekin har edge ek hi baar traverse hua and that is it to answer hoga O(n+m)
agr scc hota to pehle dag mein change kro and then find the answer
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
















https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/description/

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        vector<vector<pair<int,int>>>g(n*m);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int x=i*m+j;
                if(grid[i][j]==1){
                    if(j+1<m){
                        int y=i*m+(j+1);
                        g[x].push_back({y,0});
                    }
                    if(j-1>=0){
                        int y=i*m+(j-1);
                        g[x].push_back({y,1});
                    }
                    if(i+1<n){
                         int y=(i+1)*m+(j);
                         g[x].push_back({y,1});
                    }
                    if(i-1>=0){
                        int y=(i-1)*m+j;
                        g[x].push_back({y,1});
                    }
                }
                if(grid[i][j]==2){
                    if(j+1<m){
                        int y=i*m+(j+1);
                        g[x].push_back({y,1});
                    }
                    if(j-1>=0){
                        int y=i*m+(j-1);
                        g[x].push_back({y,0});
                    }
                    if(i+1<n){
                         int y=(i+1)*m+(j);
                         g[x].push_back({y,1});
                    }
                    if(i-1>=0){
                        int y=(i-1)*m+j;
                        g[x].push_back({y,1});
                    }
                }
                if(grid[i][j]==3){
                    if(j+1<m){
                        int y=i*m+(j+1);
                        g[x].push_back({y,1});
                    }
                    if(j-1>=0){
                        int y=i*m+(j-1);
                        g[x].push_back({y,1});
                    }
                    if(i+1<n){
                         int y=(i+1)*m+(j);
                         g[x].push_back({y,0});
                    }
                    if(i-1>=0){
                        int y=(i-1)*m+j;
                        g[x].push_back({y,1});
                    }
                }
                if(grid[i][j]==4){
                    if(j+1<m){
                        int y=i*m+(j+1);
                        g[x].push_back({y,1});
                    }
                    if(j-1>=0){
                        int y=i*m+(j-1);
                        g[x].push_back({y,1});
                    }
                    if(i+1<n){
                         int y=(i+1)*m+(j);
                         g[x].push_back({y,1});
                    }
                    if(i-1>=0){
                        int y=(i-1)*m+j;
                        g[x].push_back({y,0});
                    }
                }
            }
        }
        /*
        we use distance>dist[src] in dijkstra  continue
        because

            .....\ | /...
                  u
            ..../ | \....

            ismein ye hai ki agr u ke ek taraf 1e4 nodes hain aur dossri taraf bhi 1e5 nodes hain then total will be 1e4*1e5 nodes which will be 1e9 in total 
            because let us say say that the one with the highest weight is updated once then the second highest is updated and 

            like src se saari nodes 1 distance pe hain and then wo saari nodes se u alag alag distance pe hai aur pehle koi bhi aa skta hai and then u apne children ko visit kr rha then we will have the problem
          

        */






        deque<pair<int,int>>dq;
        vector<int>dist(n*m,1e9);
        dist[0]=0;
        dq.push_front({0,0});
        while(!dq.empty()){
            auto [distance,x]=dq.front();
            dq.pop_front();
            if(x==(n-1)*m+m-1) break;
            if(distance>dist[x]) continue;
            for(auto &[child,weight]:g[x]){
                //ek node kyi baar relation ke liye aa skta hai
                //lekin hum kisi bhi node pe bhut logon ke trhough relac krne ki koshish kr skte hain isliye koi source agr visit ho gya hai use dubara visit krne ki zaroorat nahin hai kyunki wo alread shortest path se aa chuka hai
                if(dist[child]>dist[x]+weight){
                    //ye relation ek hi baar lgta hai isliye har edge ke liye ek hi baar check hoga
                    dist[child]=dist[x]+weight;
                    if(weight==0){
                        dq.push_front({dist[child],child});
                    }
                    else{
                        dq.push_back({dist[child],child});
                    }
                }
            }
        }
        return dist[(n-1)*m+m-1];
        
    }
};











hamein pta hai ki ek node se jitni bhi node zerp distance pe hain unhein ek hi node maan skte hain and rest of th other also and then in the simple bfs when we go from one level to other we are just pushing the next level only and no other level and pehle deque mein to hum zero ko hi traverse kr rhe hain na to maximum ek hi level waale pehle aayenge.
    
