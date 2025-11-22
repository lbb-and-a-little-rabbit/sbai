#include <bits/stdc++.h>

using namespace std;

class Solution {
    bool line[9][10]={false};
    bool col[9][10]={false};
    bool box[3][3][10]={false};
    vector<pair<int,int>> space;
    bool solved=false;

    void bt(vector<vector<char>>& board,int idx){
        if(idx==space.size()){
            solved=true;
            return;
        }

        if(solved) return;
        int x=space[idx].first,y=space[idx].second;
        for(int i=1;i<=9;i++){
            if(!line[x][i]&&!col[y][i]&&!box[x/3][y/3][i]){
                line[x][i]=col[y][i]=box[x/3][y/3][i]=true;
                board[x][y]=i+'0';
                bt(board,idx+1);
                if(solved) return;
                line[x][i]=col[y][i]=box[x/3][y/3][i]=false;
            }
        }
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[i][j]=='.') space.push_back({i,j});
                else{
                    int x=board[i][j]-'0';
                    line[i][x]=true;
                    col[j][x]=true;
                    box[i/3][j/3][x]=true;
                }
            }
        }
        bt(board,0);
    }
};

/*
    位运算优化：
class Solution {
private:
    int line[9];
    int column[9];
    int block[3][3];
    bool valid;
    vector<pair<int, int>> spaces;

public:
    void flip(int i, int j, int digit) {
        line[i] ^= (1 << digit);
        column[j] ^= (1 << digit);
        block[i / 3][j / 3] ^= (1 << digit);
    }

    void dfs(vector<vector<char>>& board, int pos) {
        if (pos == spaces.size()) {
            valid = true;
            return;
        }

        auto [i, j] = spaces[pos];
        int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & 0x1ff;
        for (; mask && !valid; mask &= (mask - 1)) {
            int digitMask = mask & (-mask);
            int digit = __builtin_ctz(digitMask);
            flip(i, j, digit);
            board[i][j] = digit + '0' + 1;
            dfs(board, pos + 1);
            flip(i, j, digit);
        }
    }

    void solveSudoku(vector<vector<char>>& board) {
        memset(line, 0, sizeof(line));
        memset(column, 0, sizeof(column));
        memset(block, 0, sizeof(block));
        valid = false;

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    spaces.emplace_back(i, j);
                }
                else {
                    int digit = board[i][j] - '0' - 1;
                    flip(i, j, digit);
                }
            }
        }

        dfs(board, 0);
    }
};

*/