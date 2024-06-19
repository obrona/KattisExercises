#include <vector>
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

// simply a problem on finding the maximum matching on a bipartite graph, use max flow to solve

vector<vector<int>> adjMatrix;
vector<vector<double>> gopher;
vector<vector<double>> holes;

void print(vector<int> arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

void process(vector<vector<double>>& gopher, vector<vector<double>>& holes, double s, double v) {
    int n = gopher.size();
    int m = holes.size();
    adjMatrix = vector(n + m + 2, vector(n + m + 2, 0));
    for (int i = 1; i <= n; i ++) {
        adjMatrix[0][i] = 1;
    }
    for (int i = 1; i <= m; i ++) {
        adjMatrix[n + i][n + m + 1] = 1;
    }
    for (int i = 0; i < n; i ++) {
        vector<double>& coor = gopher[i];
        for (int j = 0; j < m; j ++) {
            vector<double>& coorH = holes[j];
            double dist = sqrt(pow(coor[0] - coorH[0], 2) + pow(coor[1] - coorH[1], 2));
            if (dist / v <= s + 0.000001) {
                adjMatrix[i + 1][n + j + 1] = 1;
            }
        }
    }
}

bool dfs(int vtx, vector<bool>& visited, int goal) {
    if (visited[vtx]) {
        return false;
    } else if (vtx == goal) {
        return true;
    } else {
        visited[vtx] = true;
        for (int i = 0; i < adjMatrix[0].size(); i ++) {
            if (adjMatrix[vtx][i] == 1) {
                adjMatrix[vtx][i] = 0;
                adjMatrix[i][vtx] = 1;
                bool ans = dfs(i, visited, goal);
                if (ans) {
                    return true;
                } else {
                    adjMatrix[vtx][i] = 1;
                    adjMatrix[i][vtx] = 0;
                }
            }
        }
        return false;
    }
}

int fordFulkerson() {
    int best = 0;
    while (true) {
        vector<bool> visited(adjMatrix.size(), false);
        bool canExtend = dfs(0, visited, adjMatrix.size() - 1);
        if (canExtend) {
            best++;
        } else {
            break;
        }
    }
    return best;

}

int main() {
    int n, m;
    double s, v;
    while (cin >> n) {
        cin >> m >> s >> v;
        gopher.clear();
        holes.clear();


        for (int i = 0; i < n; i ++) {
            double x, y;
            cin >> x >> y;
            gopher.push_back({x, y});
        }
        for (int i = 0; i < m; i ++) {
            double x, y;
            cin >> x >> y;
            holes.push_back({x, y});
        }
        process(gopher, holes, s, v);
        
        int ans = fordFulkerson();
        cout << n - ans << "\n";
    }
}
    

    