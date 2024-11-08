#include <vector>
#include <queue>
#include <tuple>
using std::vector;
using std::queue;
using std::tuple;

int captured(int knight_r, int knight_c, int pawn_r, int pawn_c) {

    if (knight_r == pawn_r && knight_c == pawn_c) return 0;

    vector<vector<int>> dirs = {
        {2,1}, {2,-1}, {-2,1}, {-2,-1},
        {1,2}, {-1,2}, {1,-2}, {-1,-2}
    };

    queue<vector<int>> q;
    [[maybe_unused]] bool visited[8][8] = {false};

    q.push({knight_r, knight_c, 0});
    visited[knight_r][knight_c] = true;

    while (!q.empty()) {
        vector<int> tmp = q.front();
        q.pop();
        int row = tmp[0], col = tmp[1], moves = tmp[2];

        for (const auto& direction : dirs) {
            int dr = direction[0], dc = direction[1];
            int new_row = row + dr, new_col = col + dc;

            if (new_row == pawn_r && new_col == pawn_c) return moves+1;

            if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
                visited[new_row][new_col] = true;
                q.push({new_row, new_col, moves+1});
            }

        }
    }
    return -1;
}
