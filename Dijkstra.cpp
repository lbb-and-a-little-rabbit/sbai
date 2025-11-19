#include <bits/stdc++.h>

using namespace std;

struct Edge{
    int to;
    int w;
};

int m,n;
vector<vector<Edge>> adj;
vector<int> dist;

void add(int u,int v,int w){
    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
}

void Dijkstra(int start){
    priority_queue <pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    dist[start]=0;
    pq.push({0,start}); // {dist,ver}

    while(!pq.empty()){
        auto [dis,u]=pq.top();
        pq.pop();

        if(dis>dist[u]) continue;
        for(auto &e:adj[u]){
            int v=e.to;
            int w=e.w;
            if(dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n;
    adj.assign(n,{});
    dist.assign(n,INT32_MAX);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        add(u,v,w);
    }
    Dijkstra(0);
    for(int i=0;i<n;i++){
        cout << dist[i] << '\n';
    }
}

