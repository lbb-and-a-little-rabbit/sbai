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
    int grid[3][3];
    int currentPlayer; // X: AI, O: human

    Board() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                grid[i][j] = EMPTY;
        currentPlayer = X;
    }

    // 生成所有空格位置
    std::vector<Move> generateMoves() const {
        std::vector<Move> moves;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
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
        // 行
        for (int i = 0; i < 3; i++)
            if (grid[i][0] != EMPTY && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
                return grid[i][0];

        // 列
        for (int j = 0; j < 3; j++)
            if (grid[0][j] != EMPTY && grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j])
                return grid[0][j];

        // 对角线
        if (grid[0][0] != EMPTY && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
            return grid[0][0];

        if (grid[0][2] != EMPTY && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
            return grid[0][2];

        return EMPTY;
    }

    // 是否终局（胜/平）
    bool isTerminal() const {
        if (checkWinner() != EMPTY)
            return true;

        // 无空格则平局
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] == EMPTY)
                    return false;

        return true;
    }

    // 评估函数
    int evaluate() const {
        int winner = checkWinner();
        if (winner == X)  return +100;  // AI 赢
        if (winner == O)  return -100;  // 人类赢
        return 0;                       // 平局/未分胜负
    }

    // 打印棋盘
    void print() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                char c = ' ';
                if (grid[i][j] == X) c = 'X';
                if (grid[i][j] == O) c = 'O';
                std::cout << c;
                if (j < 2) std::cout << " | ";
            }
            std::cout << "\n";
            if (i < 2) std::cout << "---------\n";
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
        std::cout << "\n玩家(O)输入坐标(0~2 0~2):";
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
        Move best = findBestMove(board, 9);
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
