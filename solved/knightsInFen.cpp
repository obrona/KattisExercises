#include <string>
#include <vector>
#include <iostream>
using namespace std;

const string FAIL = "Unsolvable in less than 11 move(s).";
const vector<string> final = {"11111", "01111", "00 11", "00001", "00000"};
const vector<vector<int>> dirs = {{-1,-2}, {1,-2}, {2,-1}, {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}};
int blackCorrect = 0;
int whiteCorrect = 0;

//out[0] is black or 1, out[1] is white or 0
int* process(vector<string>& board) {
    int* out = new int[2] {0, 0};
    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 5; j ++) {
            if (board[i][j] == '1' && final[i][j] == '1') {
                //cout << i << " " << j << " " << "B" << endl;
                out[0] ++;
            } else if (board[i][j] == '0' && final[i][j] == '0') {
                //cout << i << " " << j << " " << "W" << endl;
                out[1] ++;
            }
        }
    }
    return out;
}

int* findEmpty(vector<string>& b) {
    int* out = new int[2] {0, 0};
    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 5; j ++) {
            if (b[i][j] == ' ') {
                out[0] = i;
                out[1] = j;
            }
        }
    }
    return out;
}

bool valid(int r, int c) {
    return (r < 0 || c < 0 || r >= 5 || c >= 5) ? false : true;
}

int canSolve(vector<string>& board, int moves, int r, int c, int bCorr, int wCorr) {
    if (moves == 10) {
        if (bCorr == 12 && wCorr == 12) {
            return 10;
        } else {
            return 999999;
        }
    } else if (bCorr == 12 && wCorr == 12) {
        return moves;
    } else {
        int minMoves = 999999;
        for (int i = 0; i < 8; i ++) {
            const vector<int>& dir = dirs[i];
            int nR = r + dir[0];
            int nC = c + dir[1];
            if (valid(nR, nC)) {
                char temp = board[nR][nC];
                board[nR][nC] = ' ';
                board[r][c] = temp;
                int bPlus = 0;
                int wPlus = 0;
                if (temp == '1') {
                    bPlus = - (final[nR][nC] == '1') + (final[r][c] == '1');
                } else if (temp == '0') {
                    wPlus = -(final[nR][nC] == '0') + (final[r][c] == '0');
                }
                int res =  canSolve(board, moves + 1, nR, nC, bCorr + bPlus, wCorr + wPlus);
                minMoves = min(minMoves, res);
                board[r][c] = ' ';
                board[nR][nC] = temp;
            }
        }
        return minMoves;
    }
    
}

/*int main() {
    vector<string> b = {"11111", "01111", "00 11", "00001", "00000"};
    int* res = process(b);
    int* res2 = findEmpty(b);
    cout << res[0] << " " << res[1] << endl;
    cout << res2[0] << " " << res2[1] << endl;
}*/

int main() {
    int M;
    string m;
    getline(cin, m);
    M = stoi(m);
    //cin.ignore();
    for (int i = 0; i < M; i ++) {
        vector<string> b;
        for (int j = 0; j < 5; j ++) {
            
            string s;
            getline(cin , s);
            b.push_back(s);
        }
        
        int* cnt = process(b);
        int* empty = findEmpty(b);
        //cout << cnt[0] << " " << cnt[1] << endl;
        //cout << empty[0] <<" " << empty[1] << endl;
        int ans = canSolve(b, 0, empty[0], empty[1], cnt[0], cnt[1]);
        if (ans >= 999999) {
            cout << FAIL << endl;
        } else {
            cout << "Solvable in " << ans << " move(s)." << endl;
        }
    }
}