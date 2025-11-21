#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;
vector<int> vis;
vector<int> dis;

int m,n;

void add(int u,int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void bfs(int root){
    queue<int> q;
    vis[root]=1;
    q.push(root);
    dis[root]=0;

    while(!q.empty()){
        int sz=q.size();
        for(int i=0;i<sz;i++){
            int u=q.front();
            q.pop();
            for(int v:adj[u]){
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
                    dis[v]=dis[u]+1;
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> m >> n;
    adj.assign(n,{});
    vis.assign(n,0);
    dis.assign(n,INT32_MAX);
    int root;
    //cin a tree
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        add(u,v);
    }
    cin >> root;
    bfs(root);
    for(int i=0;i<n;i++){
        cout << dis[i] << '\n';
    }
}