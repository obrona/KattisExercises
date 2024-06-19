#include <vector>
#include <iostream>
#include <queue>
using namespace std;

// actually just a bfs/dfs problem. At every time i, we just need to know all sectors mechs can visit.
// Then for godzilla current position, check from godzilla, if there is a sector a mech can visit by that time that can hit godzilla
// for ruined sectors, if when ruined is adjacent to a mech visitable sector, in that turn, when mechs move
// that sector must be mark visited. If not just change grid to '.' and bfs as normal, as mech cant visit that sector at that time anyway
// 
// the bfs queue stores the 'fringe'. After the current elem in queue are pop and new not yet visited sectors are added
// add ruined sector




template <typename T>
void print(vector<vector<T>> arr) {
    for (int i = 0; i < arr.size(); i ++) {
        for (int j = 0; j < arr[j].size(); j ++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}








class Solution {
public:
    vector<vector<int>> DIRS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // N E S W
    vector<vector<char>> grid;
    vector<vector<bool>> mVisited;
    vector<vector<bool>> gVisited;
    vector<vector<int>> initMechs;
    vector<int> initGodzilla;

    Solution(int R, int C) {
        grid = vector(R, vector(C, '.'));
        mVisited = vector(R, vector(C, false));
        gVisited = vector(R, vector(C, false));
        
    }

    bool valid(int r, int c) {
        return (r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size()) ? false : true;
    }

    // check if a ruined sector is adjacent to a sector a mech can visit in the current iteration
    bool isNextToVisited(int r, int c) {
        for (vector<int>& dir : DIRS) {
            int nr = r + dir[0];
            int nc = c + dir[1];
            if (valid(nr, nc) && mVisited[nr][nc]) return true;
        }
        return false;
    }



    // 0th array is new coor of godzilla, arrays afterwards are new ruined sectors
    // will also update grid of residential turned ruined sectors
    vector<vector<int>> godzillaMove(int r, int c) {
        vector<vector<int>> out;
        
        // found a residential sector to destroy
        for (vector<int>& dir : DIRS) {
            int nr = r + dir[0];
            int nc = c + dir[1];
            if (valid(nr, nc) && !gVisited[nr][nc] && grid[nr][nc] == 'R') {
                out.push_back({nr, nc});
                out.push_back({nr, nc});
                gVisited[nr][nc] = true;
                grid[nr][nc] = '.';
                return out;
            }
        }

        // no residential sector, just move to empty sector
        for (vector<int>& dir : DIRS) {
            int nr = r + dir[0];
            int nc = c + dir[1];
            if (valid(nr, nc) && !gVisited[nr][nc]) {
                out.push_back({nr, nc});
                gVisited[nr][nc] = true;
                return out;
            }
        }

        // no move at all
        out.push_back({r, c});
        return out;
    }

    bool checkMech(int r, int c) {
        for (int i = r; i >= 0; i --) {
            if (grid[i][c] == 'R') break;
            if (mVisited[i][c]) return true;
        }
        
        for (int i = r; i < grid.size(); i ++) {
            if (grid[i][c] == 'R') break;
            if (mVisited[i][c]) return true;
        }

        for (int i = c; i >= 0; i --) {
            if (grid[r][i] == 'R') break;
            if (mVisited[r][i]) return true;
        }

        for (int i = c; i < grid[0].size(); i ++) {
            if (grid[r][i] == 'R') break;
            if (mVisited[r][i]) return true;
        }

        return false;
    }

    int findAns() {
        queue<vector<int>> q;
        int destroyed = 0;
        for (vector<int>& mechPos : initMechs) {
            q.push(mechPos);
            mVisited[mechPos[0]][mechPos[1]] = true;
        }
        int cr = initGodzilla[0];
        int cc = initGodzilla[1];
        gVisited[cr][cc] = true;

        while (true) {
            vector<vector<int>> gmove = godzillaMove(cr, cc);
            destroyed += gmove.size() - 1;
            if (gmove.size() > 1 && isNextToVisited(gmove[1][0], gmove[1][1])) {
                mVisited[gmove[1][0]][gmove[1][1]] = true;
                q.push({gmove[1][0], gmove[1][1]});
            }
            cr = gmove[0][0];
            cc = gmove[0][1];
            
            int len = q.size();
            for (int i = 0; i < len; i ++) {
                vector<int> pos = q.front();
                q.pop();
                for (vector<int>& dir : DIRS) {
                    int nr = pos[0] + dir[0];
                    int nc = pos[1] + dir[1];
                    if (valid(nr, nc) && !mVisited[nr][nc] && grid[nr][nc] != 'R') {
                        mVisited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }

            if (gmove.size() > 1 && isNextToVisited(gmove[1][0], gmove[1][1])) {
                q.push({gmove[1][0], gmove[1][1]});
            }

            int canDestroy = checkMech(gmove[0][0], gmove[0][1]);
            if (canDestroy) return destroyed;
        }
        return destroyed;

       



    }
};

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t ++) {
        int L, W;
        cin >> L >> W;
        Solution sol(W, L);
        for (int r = 0; r < W; r ++) {
            for (int c = 0; c < L; c ++) {
                char cha;
                cin >> cha;
                sol.grid[r][c] = cha;
                if (cha == 'M') sol.initMechs.push_back({r, c});
                if (cha == 'G') {
                    sol.initGodzilla.push_back(r);
                    sol.initGodzilla.push_back(c);
                }
            }
        }
        int ans = sol.findAns();
        cout << ans << endl;

    }
}