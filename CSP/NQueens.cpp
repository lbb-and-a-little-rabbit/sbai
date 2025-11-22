#include <bits/stdc++.h>

using namespace std;

class Solution {
    vector<vector<string>> ans;
    vector<string> tem;

    void bt(int n,int idx){
        if(idx==n){
            ans.push_back(tem);
            return;
        }

        for(int j=0;j<n;j++){
            bool valid=true;
            for(int i=0;i<idx;i++){
                if(tem[i][j]=='Q'){
                    valid=false;
                    break;
                } 
            }
            if(valid){
                int x=idx-1,y=j-1;
                while(x>=0&&y>=0){
                    if(tem[x][y]=='Q'){
                        valid=false;
                        break;
                    }
                    x--;
                    y--;
                }
                x=idx-1,y=j+1;
                while(valid&&x>=0&&y<n){
                    if(tem[x][y]=='Q'){
                        valid=false;
                        break;
                    }
                    x--;
                    y++;
                }
            }
            if(valid){
                tem[idx][j]='Q';
                bt(n,idx+1);
                tem[idx][j]='.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        string line;
        for(int i=0;i<n;i++) line.push_back('.');
        tem.assign(n,line);
        bt(n,0);
        return ans;
    }
};