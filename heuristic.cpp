#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;
};

class heuristic {
public:
    heuristic() {}

    // 曼哈顿距离（4方向）
    int Manhattan_Distance(const Node& a, const Node& b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    }

    // 欧几里得距离（任意方向）
    double Euclidean_Distance(const Node& a, const Node& b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return sqrt(dx * dx + dy * dy);
    }

    // 切比雪夫距离（8方向，直走与斜走代价相同）
    int Chebyshev_Distance(const Node& a, const Node& b) {
        return max(abs(a.x - b.x), abs(a.y - b.y));
    }

    // 对角距离（8方向，直走=1，斜走=√2）
    double Diagonal_Distance(const Node& a, const Node& b) {
        int dx = abs(a.x - b.x);
        int dy = abs(a.y - b.y);
        const double D  = 1.0;       // straight
        const double D2 = 1.414213;  // diagonal (≈ sqrt(2))
        return D * (dx + dy) + (D2 - 2 * D) * min(dx, dy);
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    heuristic h;
    Node a{0, 0}, b{3, 4};

    cout << h.Manhattan_Distance(a, b) << "\n";
    cout << h.Euclidean_Distance(a, b) << "\n";
    cout << h.Chebyshev_Distance(a, b) << "\n";
    cout << h.Diagonal_Distance(a, b) << "\n";
}