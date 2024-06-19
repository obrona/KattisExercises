#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <chrono>
using namespace std;


class Dinics {
public:
    int INF = 1000000000;
    vector<unordered_map<int, int>> capacities;
    int n, s, t;

    Dinics(int N, int S, int T) {
        n = N;
        s = S;
        t = T;
        capacities = vector(n, unordered_map<int, int>());
    }

    // construct level graph
    bool bfs(vector<vector<int>>& adjList) {
        queue<int> q;
        vector<bool> visited(n, false);
        q.push(s);
        while (!q.empty()) {
           int len = q.size();
           for (int i = 0; i < len; i ++) {
               int src = q.front(); q.pop();
               if (visited[src]) {
                    len --; // MUST REMEMBER TO MINUS :(((
                    continue;
               }
               visited[src] = true;
               q.push(src);
               if (src == t) {
                    return true;
               }
           }
           
           for (int i = 0; i < len; i ++) {
               int src = q.front(); q.pop();
               for (const auto& [key, value] : capacities[src]) {
                   if (!visited[key] && value > 0) {
                       adjList[key].push_back(src);
                       q.push(key);
                   }
               }
           }
            
        }
        return false;
    }

    int dfs(int dest, vector<vector<int>>& adjList, int minEdge) {
       
        if (dest == s) {
            return minEdge;
            
        } else {
            while (!adjList[dest].empty()) {
                int src = adjList[dest].back();

                int cap = capacities[src][dest];
                int res = dfs(src, adjList, min(minEdge, cap));
                if (res == INF) {
                    adjList[dest].pop_back();
                } else {
                    capacities[src][dest] -= res;
                    capacities[dest][src] += res;
                    if (capacities[src][dest] == 0) adjList[dest].pop_back();
                    return res;
                }
            }

            return INF; // cannot find a way back to src
        }
    }

    int maxFlow() {
        int maxflow = 0;
        while (true) {
            vector<vector<int>> adjList = vector(n, vector<int>());
            bool canReachT = bfs(adjList);
            if (!canReachT) break;
            int flow = 0;
            while (true) {
                int canAdd = dfs(t, adjList, INF);
                if (canAdd == INF) break;
                maxflow += canAdd;
            }
        }
        return maxflow;
    }

    void addEdge(int src, int dest, int c) {
        // this case checks when we have added an edge dest->src previously and later we need to add an edge src->dest
        bool doneBefore = capacities[src].find(dest) != capacities[src].end();
        capacities[src][dest] = c;
        if (!doneBefore) capacities[dest][src] = 0;
    }

    void printCapacities() {
        for (int i = 0; i < n; i ++) {
            for (const auto& [key, value] : capacities[i]) {
                cout << "(" << i << " " << key << " " << value << ") ";
            }
            cout << endl;
        }
    }
};


// reduce the problem to finding a min vertex cover on bipartite graph, which is possible because min vertices to cover = maximum 
// matching of graph. 
// How we do this is by considering where the robots can be placed row facing or col facing
// eg ...#...#... => 000#111#222, meaning that places of interests, P, placed at the respective coor can be watched by robot 0, or 1, or 2
// same with column .  => 3
//                  .     3
//                  #
//                  .     4
//                  .     4
// Now the key insight is that each P can only be adjacent to at most 2 robots nodes, 1 from row and 1 from col, proof is simple 
// just consider transitivity. What happens when P can be seen by 2 row robots, the 2 row robots can be combined to 1 row robot
// since there are no edges between any 2 row robots or 2 col robots, graph is bipartite
// so each P can be modelled as an edge, and the graph is bipartite and we have to find min vertex cover for a bipartite graph 

class Solver {
public:
    vector<vector<char>> grid;
    vector<vector<int>> rowNodes;
    vector<vector<int>> colNodes;
    int A, B, R, C;

    Solver(int r, int c) {
        R = r;
        C = c;
        grid = vector(r, vector(c, '.'));
        rowNodes = vector(r, vector(c, -1));
        colNodes = vector(r, vector(c, -1));
        A = 0;
    }

    void processGraph() {
        int cnt = 0;

        bool prevR = false;
        for (int r = 0; r < R; r ++) {
            for (int c = 0; c < C; c ++) {
                char cha = grid[r][c];
                if (cha == '#') {
                    if (!prevR) {
                        cnt ++;
                        prevR = true;
                    }
                    continue;
                } else {
                    prevR = false;
                    rowNodes[r][c] = cnt;
                    if (c == C - 1) cnt ++;
                }
            }
        }
        A = cnt;

        bool prevC = false;
        for (int c = 0; c < C; c ++) {
            for (int r = 0; r < R; r ++) {
                char cha = grid[r][c];
                if (cha == '#') {
                    if (!prevC) {
                        cnt ++;
                        prevC = true;
                    }
                    continue;
                } else {
                    prevC = false;
                    colNodes[r][c] = cnt;
                    if (r == R - 1) cnt ++;
                }
            }
        }

        B = cnt;
    }

    int findMinVertexCover() {
        Dinics dn(B + 2, B, B + 1);
        for (int r = 0; r < R; r ++) {
            for (int c = 0; c < C; c ++) {
                if (grid[r][c] == '*') {
                    int anode = rowNodes[r][c];
                    int cnode = colNodes[r][c];
                    dn.addEdge(anode, cnode, 1);
                }
            }
        }

        for (int i = 0; i < A; i ++) {
            dn.addEdge(B, i, 1);
        }

        for (int i = A; i < B; i ++) {
            dn.addEdge(i, B + 1, 1);
        }

        int ans = dn.maxFlow();
        return ans;
    }

    template <typename T>
    void printArr(vector<vector<T>> arr) {
        for (int i = 0; i < arr.size(); i ++) {
            for (int j = 0; j < arr[0].size(); j ++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int C;
    cin >> C;
    for (int i = 0; i < C; i ++) {
        int R, C;
        cin >> R >> C;
        Solver sol(R, C);
        
        int P;
        cin >> P;
        for (int i = 0; i < P; i ++) {
            int r, c;
            cin >> r >> c;
            sol.grid[r - 1][c - 1] = '*';
        }

        int W;
        cin >> W;
        for (int i = 0; i < W; i ++) {
            int r, c;
            cin >> r >> c;
            sol.grid[r - 1][c - 1] = '#';
        }

        //sol.printArr(sol.grid);
        sol.processGraph();
        //sol.printArr(sol.rowNodes);
        //sol.printArr(sol.colNodes);
        cout << sol.findMinVertexCover() << '\n';
    }
}