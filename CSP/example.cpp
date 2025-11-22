/*
    CSP = 变量（Variables） + 域（Domains） + 约束（Constraints）

    典型问题：

        地图着色（Map Coloring）

        数独（Sudoku）

        N 皇后（N-Queens）

        课程安排 (Scheduling)

        图着色 (Graph Coloring)

    求解方法：
        1. 回溯搜索（Backtracking）（最基本）

            DFS + 回溯，逐个尝试变量赋值。

            缺点：无优化时非常慢。

        2. 常用优化技术（让回溯更快）
            ✔（1）MRV（最少剩余值，Minimum Remaining Values）

            优先选择可选值最少的变量（最难的先解决）。

            ✔（2）Degree Heuristic（度启发式）

            优先选择与最多变量有约束的变量。

            ✔（3）LCV（最少约束值，Least Constraining Value）

            选择最不限制其他变量的值。

            ✔（4）前向检查（Forward Checking）

            当变量赋值后，立即检查其他未赋值变量是否仍有合法值。

            ✔（5）AC-3（弧一致性）

            进一步剪枝，使所有二元约束都满足一致性。
*/

//CSP + 回溯 + MRV + 前向检查 示例：

#include <bits/stdc++.h>
using namespace std;

class CSP {
public:
    int n;                              // 节点数
    vector<vector<int>> adj;            // 图的邻接表
    vector<int> colors;                 // 已分配颜色
    vector<vector<int>> domain;         // 每个变量的域

    CSP(int n) : n(n) {
        adj.assign(n, {});
        colors.assign(n, 0);
        domain.assign(n, {1,2,3});       // 3 种颜色
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 判断变量是否可以使用该颜色
    bool isValid(int node, int color) {
        for(int nei : adj[node])
            if(colors[nei] == color)
                return false;
        return true;
    }

    // MRV：选择域最小的未赋值变量
    int selectMRV() {
        int best = -1, minSize = 1e9;
        for(int i=0;i<n;i++) {
            if(colors[i] == 0) {
                if(domain[i].size() < minSize) {
                    minSize = domain[i].size();
                    best = i;
                }
            }
        }
        return best;
    }

    // 前向检查：赋值后删除邻居域中冲突值
    bool forwardCheck(int node, int color, vector<vector<int>>& backup) {
        backup = domain;  // 备份（用于回溯）
        for(int nei : adj[node]) {
            if(colors[nei] == 0) {
                auto &dom = domain[nei];
                dom.erase(remove(dom.begin(), dom.end(), color), dom.end());
                if(dom.empty()) return false;  // 失败：某邻居无可用颜色
            }
        }
        return true;
    }

    bool solve() {
        int node = selectMRV();
        if(node == -1) return true;  // 所有变量赋值完毕

        for(int color : domain[node]) {
            if(isValid(node, color)) {
                colors[node] = color;

                vector<vector<int>> backup;
                if(forwardCheck(node, color, backup)) {
                    if(solve()) return true;
                }
                domain = backup;      // 回溯域
                colors[node] = 0;     // 回溯颜色
            }
        }
        return false;
    }
};

int main() {
    CSP csp(4);
    csp.addEdge(0,1);
    csp.addEdge(1,2);
    csp.addEdge(2,3);
    csp.addEdge(3,0);

    if(csp.solve()) {
        cout << "找到一个解：" << endl;
        for(int i=0;i<4;i++)
            cout << "节点 " << i << " 颜色：" << csp.colors[i] << endl;
    } else {
        cout << "无解" << endl;
    }
}
