#include <vector>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;


// use vertex splitting technique to find min vertex cut
// for each v with capacity, split into vin, vout, connected a DIRECTED edge from vin to vout
// since graph is undirected, we need to split each undirected edge into 2 directed edges of the undirected edge capacity (in this case INF)
// and max flow = min cut
// cut is defined as sum of edges pointing from S to T
// i.e if an edge u->v and u, v are in S, not counted

#define INF 1000000000
vector<vector<int>> DIRS = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

class Edmonds {
public:
    vector<vector<int>> adjList;
    vector<vector<int>> capacties;
    int n;
    int s;
    int t;
    int maxflow = 0;
    
    Edmonds(vector<vector<int>>& adjList, vector<vector<int>>& capacities, int numVtxs, int s, int t) {
        this->adjList = adjList;
        this->capacties = capacities;
        n = numVtxs;
        this->s = s;
        this->t = t;
    }

    
    // remember, parents[s] is -2
    bool bfs(vector<int>& parents) {
        bool canReachT = false;
        queue<int> q;
        fill(parents.begin(), parents.end(), -1);
        parents[s] = -2;
        q.push(s);
        while (!q.empty()) {
            int src = q.front();
            q.pop();
            if (src == t) {
                canReachT = true;
                break;
            }
            vector<int>& next = adjList[src];
            for (int dest: next) {
                if (parents[dest] == -1 && capacties[src][dest] > 0) {
                    parents[dest] = src;
                    q.push(dest);
                }
            }
        }
        return canReachT;
    }

    int augmentPath(vector<int> parents) {
        int minEdge = 999999999;
        int curr = t;
        for (int dest = t; dest != s; dest = parents[dest]) {
            int src = parents[dest];
            minEdge = min(minEdge, capacties[src][dest]);
        }
        for (int dest = t; dest != s; dest = parents[dest]) {
            int src = parents[dest];
            capacties[src][dest] -= minEdge;
            capacties[dest][src] += minEdge;
        }
        return minEdge;
    }

    int maxFlow() {
        vector<int> parents(n, -1);
        while (true) {
            bool canAdd = bfs(parents);
            if (!canAdd) break;
            maxflow += augmentPath(parents);
        }
        return maxflow;
    }

    // minCut = maxflow
    // no need to find minCut set blah blah
};

int coorIn(int r, int c, int Cols, int N) {
    return r * Cols + c;
}

int coorOut(int r, int c, int Cols, int N) {
    return N + coorIn(r, c, Cols, N);
}

bool valid(int r, int c, int Rows, int Cols) {
    return (r >= 0 && r < Rows && c >= 0 && c < Cols);
}

bool isChar(char c) {
    return (c == 'A' || c == 'B');
}

void print(vector<vector<int>> arr) {
    for (int i = 0; i < arr.size(); i ++) {
        for (int j = 0; j < arr[0].size(); j ++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int Rows, Cols, N;
    cin >> Cols >> Rows;
    N = Rows * Cols;
    vector<string> map;
    for (int i = 0; i < Rows; i ++) {
        string s;
        cin >> s;
        map.push_back(s);
    }
    vector<vector<int>> adjList(2 * N + 2, vector<int>());
    vector<vector<int>> capacities(2 * N + 2, vector<int>(2 * N + 2, 0));
    int S = 2 * N;
    int T = 2 * N + 1; 
    for (int r = 0; r < Rows; r ++) {
        for (int c = 0; c < Cols; c ++) {
            int vtxValue = (isChar(map[r][c])) ? INF : map[r][c] - '0';
            int cIn = coorIn(r, c, Cols, N);
            int cOut = coorOut(r, c, Cols, N);
            adjList[cIn].push_back(cOut);
            adjList[cOut].push_back(cIn);
            capacities[cIn][cOut] = vtxValue;

            if (vtxValue == INF) {
                if (map[r][c] =='A') {
                    adjList[S].push_back(cIn);
                    adjList[cIn].push_back(S);
                    capacities[S][cIn] = INF;
                } else {
                    adjList[cOut].push_back(T);
                    adjList[T].push_back(cOut);
                    capacities[cOut][T] = INF;
                }
            }

            for (int i = 0; i < 4; i ++) {
                int rV = r + DIRS[i][0];
                int cV = c + DIRS[i][1];
                if (valid(rV, cV, Rows, Cols)) {
                    int vIn = coorIn(rV, cV, Cols, N);
                    int vOut = coorOut(rV, cV, Cols, N);
                    adjList[cOut].push_back(vIn);
                    adjList[vIn].push_back(cOut);
                    capacities[cOut][vIn] = INF;

                    adjList[vOut].push_back(cIn);
                    adjList[cIn].push_back(vOut);
                    capacities[vOut][cIn] = INF;
                }
            }
        }
    }
    //print(capacities);

    Edmonds ed(adjList, capacities, 2 * N + 2, 2 * N, 2 * N + 1);
    int ans = ed.maxFlow();
    cout << ans;



}