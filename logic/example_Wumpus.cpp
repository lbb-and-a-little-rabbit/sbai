#include <bits/stdc++.h>
using namespace std;

/*
   一个“迷你 Wumpus 世界推理器”：
   - 维护格子是否安全
   - 通过 Breeze 推断 Pit 的可能位置
   - 展示 KB 更新过程
*/

struct Cell {
    bool safe = false;         // 推理得到：绝对安全
    bool pit_possible = false; // 推理得到：可能有坑
    bool visited = false;
};

class KB_Wumpus {
public:
    int N = 4; // 4x4 世界
    vector<vector<Cell>> grid;

    KB_Wumpus() {
        grid.assign(N+1, vector<Cell>(N+1)); // 使用 (1,1)~(4,4)
    }

    bool inBounds(int x, int y) {
        return x >= 1 && x <= N && y >= 1 && y <= N;
    }

    vector<pair<int,int>> neighbors(int x, int y) {
        vector<pair<int,int>> neigh;
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        for(int i=0;i<4;i++){
            int nx = x + dx[i], ny = y + dy[i];
            if (inBounds(nx,ny)) neigh.push_back({nx,ny});
        }
        return neigh;
    }

    // 智能体在 (x,y) 感知 Breeze=true/false
    void tellBreeze(int x, int y, bool breeze) {
        grid[x][y].visited = true;

        if (!breeze) {
            // 无 Breeze → 所有邻居绝对安全
            for (auto &nb : neighbors(x,y)) {
                int nx = nb.first, ny = nb.second;
                grid[nx][ny].safe = true;
                grid[nx][ny].pit_possible = false;
            }
        } else {
            // 有 Breeze → 所有未确定安全的邻居可能有坑
            for (auto &nb : neighbors(x,y)) {
                int nx = nb.first, ny = nb.second;
                if (!grid[nx][ny].safe) {
                    grid[nx][ny].pit_possible = true;
                }
            }
        }
    }

    // 判断未访问且安全的格子
    vector<pair<int,int>> getSafeFrontier() {
        vector<pair<int,int>> safeCells;
        for(int x=1; x<=N; x++){
            for(int y=1; y<=N; y++){
                if (!grid[x][y].visited && grid[x][y].safe)
                    safeCells.push_back({x,y});
            }
        }
        return safeCells;
    }

    // 展示当前 KB 推理
    void printKB() {
        cout << "\n=== 当前 KB 状态 ===\n";
        for(int y=N; y>=1; y--) {
            for(int x=1; x<=N; x++) {
                cout << "("<<x<<","<<y<<") ";
                if (grid[x][y].safe) cout << "[Safe] ";
                else if (grid[x][y].pit_possible) cout << "[Pit?] ";
                else cout << "[Unknown] ";
            }
            cout << "\n";
        }
        cout << "===================\n";
    }
};

int main() {
    KB_Wumpus kb;

    cout << "智能体进入 (1,1)：感知 Breeze=FALSE\n";
    kb.tellBreeze(1,1,false);
    kb.printKB();

    cout << "\n智能体移动到 (2,1)：感知 Breeze=FALSE\n";
    kb.tellBreeze(2,1,false);
    kb.printKB();

    cout << "\n智能体移动到 (2,2)：感知 Breeze=TRUE\n";
    kb.tellBreeze(2,2,true);
    kb.printKB();

    cout << "\n可安全探索的格子:\n";
    auto safe = kb.getSafeFrontier();
    for (auto &c : safe)
        cout << "(" << c.first << "," << c.second << ") ";
    cout << "\n";

    return 0;
}
