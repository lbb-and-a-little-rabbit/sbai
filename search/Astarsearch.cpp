#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int,int>>> adj;
vector<bool> vis;
vector<int> parent;
vector<int> heuristic;
vector<int> g;
int start,goal;
int m,n;
vector<int> path;

void add(int u,int v,int w){
    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
}

//下面的A*,GBFS实现pq构造依赖外部数组导致pq更新不及时可能会导致bug 

void AStarSearch(){
    g[start]=0;

    auto cmp=[&](int a,int b){
        return g[a]+heuristic[a]>g[b]+heuristic[b];//去掉heuristic即为Dijkstra/UCS
                                                   //return g[a]+w*heuristic[a]>g[b]+w*heuristic[b];加权A*，不保证最优解，更快，w->inf 退化为GBFS
    };
    priority_queue<int,vector<int>,decltype(cmp)> pq(cmp);
    pq.push(start);

    while(!pq.empty()){
        int cur=pq.top();
        pq.pop();

        if(vis[cur]) continue;
        vis[cur]=true;

        if(cur==goal){
            for(int v=cur;v!=-1;v=parent[v]){
                path.push_back(v);
            }
            reverse(path.begin(),path.end());
            return;
        }

        for(auto [v,w]:adj[cur]){
            if(!vis[v]){
                if(g[cur]+w<g[v]){
                    g[v]=g[cur]+w;
                    parent[v]=cur;
                    pq.push(v);
                }
            }
        }
    }
}

//下面给出安全实现：

void AStarSearch_safer() {
    g[start] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({heuristic[start], start}); //(f=h+g,node),此处g=0,省略

    while (!pq.empty()) {
        auto [f, cur] = pq.top();
        pq.pop();

        if (vis[cur]) continue;
        vis[cur] = true;

        if (cur == goal) {
            for (int v = cur; v != -1; v = parent[v])
                path.push_back(v);
            reverse(path.begin(), path.end());
            return;
        }

        for (auto [v, w] : adj[cur]) {
            if (g[cur] + w < g[v]) {
                g[v] = g[cur] + w;
                parent[v] = cur;
                pq.push({g[v] + heuristic[v], v});
            }
        }
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n;
    adj.assign(n,{});
    vis.assign(n,false);
    parent.assign(n,-1);
    heuristic.assign(n,1e9);
    g.assign(n,1e9);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        add(u,v,w);
    }
    for(int i=0;i<n;i++){
        cin >> heuristic[i];
    }
    cin >> start >> goal;
    AStarSearch();
    for(int i=0;i<path.size();i++){
        cout << path[i] << ' ';
    }
    cout << '\n';

    adj.assign(n,{});
    vis.assign(n,false);
    parent.assign(n,-1);
    g.assign(n,1e9);
    AStarSearch_safer();
    for(int i=0;i<path.size();i++){
        cout << path[i] << ' ';
    }
    cout << '\n';
}