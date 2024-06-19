#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;

vector<vector<int>> DIRS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
vector<vector<int>> DIRS2 = {{-1,0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
vector<vector<string>> sets;
vector<vector<string>> setBounds;

void printGrid(vector<string> as) {
    for (string s : as) {
        cout << s << endl;
    }
}

bool valid(int r, int c, vector<string>& grid) {
    return !(r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size());
}

bool onBorder(int r, int c, vector<string>& grid) {
    return (r == 0 || c == 0 || r == grid.size() - 1 || c == grid[0].size() - 1);
}

int* findSet(char c, vector<string>& grid) {
    for (int i = 0; i < grid.size(); i ++) {
        for (int j = 0; j < grid[0].size(); j ++) {
            if (grid[i][j] == c) return new int[2] {i, j};
        }
    }
    return nullptr;
}

void markBound(int r, int c, int pr, int pc, bool start, vector<string>& grid, char set) {
    if (start) {
        sets[set - 'A'][r][c] = set;
        for (vector<int>& d : DIRS) {
            int nr = r + d[0];
            int nc = c + d[1];
            if (valid(nr, nc, grid) && grid[nr][nc] == 'X') {
                markBound(nr, nc, r, c, 0, grid, set);
                break;
            }
        }
    } else {
        if (grid[r][c] == set) return;
        else {
            sets[set - 'A'][r][c] = set;
            int cnt = 0;
            vector<vector<int>> nexts;
            for (vector<int>& d : DIRS) {
                int nr = r + d[0];
                int nc = c + d[1];
                if (valid(nr, nc, grid) && (grid[nr][nc] == 'X' || grid[nr][nc] == set)) {
                    if (nr != pr || nc != pc) nexts.push_back({nr, nc});
                    cnt ++;
                }
            }
            if (cnt == 2) {
                markBound(nexts[0][0], nexts[0][1], r, c, start, grid, set);
            } else {
                if (r == pr) {
                    // horizontal;
                    for (int i = 0; i < nexts.size(); i ++) {
                        if (nexts[i][0] == r) {
                            markBound(nexts[i][0], nexts[i][1], r, c, start, grid, set);
                            break;
                        }
                    }
                } else if (c == pc) {
                    for (int i = 0; i < nexts.size(); i ++) {
                        if (nexts[i][1] == c) {
                            markBound(nexts[i][0], nexts[i][1], r, c, start, grid, set);
                            break;
                        }
                    }
                }
            }
        }
    }
}

bool isOutside(int r, int c, vector<vector<bool>>& visited, vector<string>& grid) {
    if (visited[r][c]) return false;
    else {
        visited[r][c] = true;
        if (onBorder(r, c, grid)) return true;
        else {
            for (vector<int>& d : DIRS) {
                int nr = r + d[0];
                int nc = c + d[1];
                if (valid(nr, nc, grid) && grid[nr][nc] == '.') {
                    bool ans = isOutside(nr, nc, visited, grid);
                    if (ans) return true;   
                }
            }
            return false;
        }
    }
}

void floodfill(int r, int c, vector<string>& grid, char set) {
    if (grid[r][c] != '.') return;
    else {
        grid[r][c] = 'X';
        for (vector<int> d : DIRS) {
            int nr = r + d[0];
            int nc = c + d[1];
            if (valid(nr, nc, grid) && grid[nr][nc] != set) {
                floodfill(nr, nc, grid, set);
            }
        }
    }
}

void fillSets(int r, int c, char set) {
    // find inside
    int nr, nc;
    for (vector<int>& d : DIRS2) {
        vector<vector<bool>> visited(sets[0].size(), vector(sets[0][0].size(), false));
        int rr = r + d[0];
        int cc = c + d[1];
        if (valid(rr, cc, sets[0]) && sets[set - 'A'][rr][cc] == '.' && !isOutside(rr, cc, visited, sets[set - 'A'])) {
            nr = rr;
            nc = cc;
        }
    }
    floodfill(nr, nc, sets[set - 'A'], 'A');
}

int main() {
    int r, c;
    cin >> r >> c;
    vector<string> grid;
    sets = vector(2, vector(r, string(c, '.')));
    setBounds = vector(2, vector(r, string(c, '.')));
    for (int i = 0; i < r; i ++) {
        string s;
        cin >> s;
        grid.push_back(s);

    }
    int* a = findSet('A', grid);
    markBound(a[0], a[1], 0, 0, 1, grid, 'A');
    fillSets(a[0], a[1], 'A');
    //printGrid(sets[0]);
    
    int* b = findSet('B', grid);
    markBound(b[0], b[1], 0, 0, 1, grid, 'B');
    //printGrid(sets[1]);
    fillSets(b[0], b[1], 'B');
    //printGrid(sets[1]);

    int acnt = 0;
    int bcnt = 0;
    int abcnt = 0;
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            bool inA = false;
            bool inB = false;
            if (sets[0][i][j] == 'X' && sets[1][i][j] != 'B') {
                acnt ++;
                inA = true;
            }
            if (sets[1][i][j] == 'X' && sets[0][i][j] != 'A') {
                bcnt ++;
                inB = true;
            }
            if (inA && inB) {
                abcnt ++;
            }
        }
    }
    printf("%d %d %d", acnt - abcnt, bcnt - abcnt, abcnt);
}




