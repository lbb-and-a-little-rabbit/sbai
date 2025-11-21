/*
    GBFS 不保证找到最短路径
    也可能走弯路
    但搜索速度快
*/

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<bool> vis;
vector<int> parent;
vector<int> heuristic;
int start,goal;
int m,n;
vector<int> path;

void add(int u,int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void GBFS(){
    auto cmp=[&](int a,int b){
        return heuristic[a]>heuristic[b];
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

        for(int v:adj[cur]){
            if(!vis[v]){
                parent[v]=cur;
                pq.push(v);
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
    heuristic.assign(n,INT32_MAX);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
    }
    for(int i=0;i<n;i++){
        cin >> heuristic[i];
    }
    cin >> start >> goal;
    GBFS();
    for(int i=0;i<path.size();i++){
        cout << path[i] << ' ';
    }
    cout << '\n';
}