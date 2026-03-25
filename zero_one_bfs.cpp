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








Important
simple bfs mein ek level aage jaa rhe hain kyun edge ka weight 1 hi hai isliye answer ho jaata hai ki queue mein daal do aur kyunki sb log order mein traverse ho rhe hain isliye keval current level+1 waalon ki hi daal rhe hain
0/1 mein same level yaani weight 0 bhi aa rhe hain to unko aage daalna hai bs jaise queue mein peeche daalte hain isliye deque ka use krenge







hamein pta hai ki ek node se jitni bhi node zerp distance pe hain unhein ek hi node maan skte hain and rest of th other also and then in the simple bfs when we go from one level to other we are just pushing the next level only and no other level and pehle deque mein to hum zero ko hi traverse kr rhe hain na to maximum ek hi level waale pehle aayenge.
    
We can notice that the difference between the distances between the source s and two other vertices in the queue differs by at most one. Especially, we know that du] ≤ d|u] < du] + 1 for each u E Q. The reason for this is, that we only add vertices with equal distance or with distance plus one to the queue during each iteration. Assuming there exists a u in the queue with du - du > then then u must have been inserted into the queue via a different vertex t with d t ≥ du - 1 > du. However this is impossible, since Dijkstra's algorithm iterates over the vertices in increasing order.
This means, that the order of the queue looks like this:

{dist[u],dist[u],dist[u],dist[u[+1,dist[u]+1}

This structure is so simple, that we don't need an actual priority queue, i.e. using a balanced binary tree would be an overkill. We can
simply use a normal queue, and append new vertices at the beginning if the corresponding edge has weight 0, i.e. if du = du, or
at the end if the edge has weight 1, i.e. if du] = du] + 1. This way the queue still remains sorted at all time.
















//dials algorithm for k buckets where k can be less than or equal 2e5 but the suggestion is to use dijkstra
// Time complexity is Dial = linear in graph + linear in max weight
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n,m;
    cin>>n>>m;

    // adjacency list: {neighbor, weight}
    vector<vector<pair<int,int>>> g(n);

    int maxW = 0; // maximum edge weight

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--,v--;

        g[u].push_back({v,w}); // directed edge u -> v

        // track maximum weight for Dial's algorithm
        maxW = max(maxW, w);
    }

    int src;
    cin>>src;
    src--;

    // distance array
    vector<int> dist(n, INF);
    dist[src] = 0;

    // maximum edge weight
    int C = maxW;

    // buckets: each index represents distance mod (C+1)
    vector<queue<int>> bucket(C + 1);

    // source initially at distance 0 → bucket[0]
    bucket[0].push(src);

    int curr = 0;        // current distance being processed
    int processed = 0;  // number of nodes finalized

    // process until all nodes are handled
    while(processed < n){

        // find next non-empty bucket
        while(bucket[curr % (C+1)].empty()){
            curr++; // move to next distance
        }

        // take node from current bucket
        int u = bucket[curr % (C+1)].front();
        bucket[curr % (C+1)].pop();

        // skip outdated entry
        // (means we already found a better distance for u)
        if(dist[u] < curr) continue;

        // mark this node as processed
        processed++;

        // relax all edges from u
        for(auto [v,w]: g[u]){

            // if shorter path found
            if(dist[v] > dist[u] + w){

                dist[v] = dist[u] + w;

                // push into appropriate bucket
                // modulo ensures circular behavior
                bucket[dist[v] % (C+1)].push(v);
            }
        }
    }

    // print shortest distances
    for(int i=0;i<n;i++){
        cout<<dist[i]<<" ";
    }
}
