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

void dls(int root,int limit){
    stack<int> st;
    vis[root]=1;
    st.push(root);
    dis[root]=0;

    while(!st.empty()){
        int u=st.top();
        st.pop();
        for(int v:adj[u]){
            if(!vis[v]&&dis[u]<limit){
                vis[v]=1;
                dis[v]=dis[u]+1;
                st.push(v);
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
    dls(root,2);
    for(int i=0;i<n;i++){
        cout << dis[i] << '\n';
    }
}

/*
    ids(problem):
        for depth in 0 to inf do:
            res <- dls(problem,depth)
            if(res) return res
*/
