//minimax+alphabeta剪枝实践，五子棋

#include <iostream>
#include <vector>
#include <limits>

const int EMPTY = 0;
const int X = 1;   // AI
const int O = -1;  // 玩家

struct Move {
    int x, y;
};

struct Board {
    int grid[13][13];
    int currentPlayer; // X: AI, O: human

    Board() {
        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 13; j++)
                grid[i][j] = EMPTY;
        currentPlayer = X;
    }

    // 生成所有空格位置
    std::vector<Move> generateMoves() const {
        std::vector<Move> moves;
        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 13; j++)
                if (grid[i][j] == EMPTY)
                    moves.push_back({i, j});
        return moves;
    }

    // 返回打完步后的新棋盘
    Board applyMove(const Move& m) const {
        Board b = *this;
        b.grid[m.x][m.y] = currentPlayer;
        b.currentPlayer = -currentPlayer; // X->O 或 O->X
        return b;
    }

    // 判断是否赢
    int checkWinner() const {
        const int dx[4] = {1, 0, 1, 1};
        const int dy[4] = {0, 1, 1, -1};

        for (int x = 0; x < 13; x++) {
            for (int y = 0; y < 13; y++) {
                if (grid[x][y] == EMPTY) continue;

                int cur = grid[x][y];

                for (int d = 0; d < 4; d++) {
                    int count = 1;
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    while (nx >= 0 && nx < 13 && ny >= 0 && ny < 13 && grid[nx][ny] == cur) {
                        count++;
                        nx += dx[d];
                        ny += dy[d];
                    }

                    if (count >= 5) return cur;
                }
            }
        }
        return EMPTY;
    }


    // 是否终局（胜/平）
    bool isTerminal() const {
        if (checkWinner() != EMPTY)
            return true;

        // 无空格则平局
        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 13; j++)
                if (grid[i][j] == EMPTY)
                    return false;

        return true;
    }

    // 评估函数
int evaluate() const {
    auto patternScore = [&](int count, int block) {
        if (count >= 5) return 1000000;            // 五连
        if (count == 4) return block == 0 ? 100000 : 10000;
        if (count == 3) return block == 0 ? 1000 : 100;
        if (count == 2) return block == 0 ? 10 : 1;
        return 0;
    };

    auto getScore = [&](int player) {
        int score = 0;
        const int dx[4] = {1, 0, 1, 1};
        const int dy[4] = {0, 1, 1, -1};

        for (int x = 0; x < 13; x++) {
            for (int y = 0; y < 13; y++) {
                if (grid[x][y] != player) continue;

                for (int d = 0; d < 4; d++) {
                    int count = 1;
                    int block = 0;

                    // 正方向
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    while (nx >= 0 && nx < 13 && ny >= 0 && ny < 13 && grid[nx][ny] == player) {
                        count++;
                        nx += dx[d];
                        ny += dy[d];
                    }
                    if (!(nx >= 0 && nx < 13 && ny >= 0 && ny < 13) || grid[nx][ny] == -player)
                        block++;

                    // 反方向
                    nx = x - dx[d];
                    ny = y - dy[d];
                    while (nx >= 0 && nx < 13 && ny >= 0 && ny < 13 && grid[nx][ny] == player) {
                        count++;
                        nx -= dx[d];
                        ny -= dy[d];
                    }
                    if (!(nx >= 0 && nx < 13 && ny >= 0 && ny < 13) || grid[nx][ny] == -player)
                        block++;

                    score += patternScore(count, block);
                }
            }
        }
        return score;
    };

    int aiScore = getScore(X);
    int humanScore = getScore(O);

    return aiScore - humanScore * 1.1;   // 略微提高防守权重
}


    // 打印棋盘
// 打印棋盘（列号居中）
void print() const {
    // 打印列号行
    std::cout << "    ";
    for (int j = 0; j < 13; j++) {
        // 把数字居中放在三字符宽度内
        if (j < 10)
            std::cout << " " << j << "  ";
        else
            std::cout << " " << j << " ";  // 10~12 两位数宽度不同
    }
    std::cout << "\n";

    for (int i = 0; i < 13; i++) {
        // 打印行号
        if (i < 10) std::cout << i << "  ";
        else        std::cout << i << " ";

        for (int j = 0; j < 13; j++) {
            char c = ' ';
            if (grid[i][j] == X) c = 'X';
            if (grid[i][j] == O) c = 'O';

            std::cout << " " << c << " ";
            if (j < 12) std::cout << "|";
        }
        std::cout << "\n";

        // 分隔线
        if (i < 12) {
            std::cout << "   ";
            for (int k = 0; k < 13; k++) {
                std::cout << "---";
                if (k < 12) std::cout << "+";
            }
            std::cout << "\n";
        }
    }
}

};

// AlphaBeta 剪枝
int alphaBeta(const Board& board, int depth, int alpha, int beta, bool maximizingPlayer) {
    //TODO
    if(!depth||board.isTerminal()){
        return board.evaluate();
    }

    if(maximizingPlayer){
        int maxvalue=std::numeric_limits<int>::min();

        for(const Move& move:board.generateMoves()){
            maxvalue=std::max(maxvalue,alphaBeta(board.applyMove(move),depth-1,alpha,beta,false));
            alpha=std::max(maxvalue,alpha);

            if(alpha>=beta) break;
        }

        return maxvalue;
    }
    else{
        int minvalue=std::numeric_limits<int>::max();

        for(const Move& move:board.generateMoves()){
            minvalue=std::min(minvalue,alphaBeta(board.applyMove(move),depth-1,alpha,beta,true));
            beta=std::min(minvalue,beta);

            if(alpha>=beta) break;
        }

        return minvalue;
    }
}

// 为 AI 选择最佳走法
Move findBestMove(const Board& board, int depth) {
    int bestValue = std::numeric_limits<int>::min();
    Move bestMove = { -1, -1 };

    for (const Move& m : board.generateMoves()) {
        int value = alphaBeta(board.applyMove(m), depth - 1,
                              std::numeric_limits<int>::min(),
                              std::numeric_limits<int>::max(),
                              false);

        if (value > bestValue) {
            bestValue = value;
            bestMove = m;
        }
    }
    return bestMove;
}

int main() {
    Board board;

    while (!board.isTerminal()) {
        board.print();
        std::cout << "\n玩家(O)输入坐标(0~12 0~12):";
        int x, y;
        std::cin >> x >> y;

        if (board.grid[x][y] != EMPTY) {
            std::cout << "非法位置！重试\n";
            continue;
        }

        // 玩家走
        board.grid[x][y] = O;
        board.currentPlayer = X;

        if (board.isTerminal()) break;

        // AI 走
        Move best = findBestMove(board, 3);
        board = board.applyMove(best);
        std::cout << "AI 落子：" << best.x << ", " << best.y << "\n";
    }

    board.print();
    int w = board.checkWinner();
    if (w == X) std::cout << "AI 赢了！\n";
    else if (w == O) std::cout << "你赢了！\n";
    else std::cout << "平局！\n";

    return 0;
}
