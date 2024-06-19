#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> dirs = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

bool valid(int x, int y) {
    return (x < 0 || y < 0 || x >= 10 || y >= 10) ? false : true;
}

bool isBlack(int x, int y, vector<vector<char>>& board) {
    //cout << x << " " << y << endl;
    return (valid(x, y)) ? board[x][y] == 'B' : false;
}

int maxCaptures(int r, int c, vector<vector<char>>& board) {
    int best = 0;
    for (int i = 0; i < 4; i ++) {
        vector<int>& d = dirs[i];
        if (isBlack(r + d[0], c + d[1], board) && valid(r + d[0] * 2, c + d[1] * 2) && board[r + 2 * d[0]][c + 2 * d[1]] == '#') {
            board[r][c] = '#';
            board[r + d[0]][c + d[1]] = '#';
            board[r + 2 * d[0]][c + 2 * d[1]] = 'W';
            int ans = 1 + maxCaptures(r + 2 * d[0], c + 2 * d[1], board);
            best = max(best, ans);
            board[r][c] = 'W';
            board[r + d[0]][c + d[1]] = 'B';
            board[r + 2 * d[0]][c + 2 * d[1]] = '#';
        }
    }
    return best;
}

int findBest(vector<vector<char>> board) {
    int best = 0;
    for (int i = 0; i < 10; i ++) {
        for (int j = 0; j < 10; j ++) {
            if (board[i][j] == 'W') {
                int ans = maxCaptures(i, j, board);
                best = max(best, ans);
            }
        }
    }
    return best;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i ++) {
        vector<vector<char>> grid;
        for (int i = 0; i < 10; i ++) {
            vector<char> row;
            for (int j = 0; j < 10; j ++) {
                char c;
                cin >> c;
                row.push_back(c);
            }
            grid.push_back(row);
        }
        int ans = findBest(grid);
        cout << ans << endl;
    }
    
}

