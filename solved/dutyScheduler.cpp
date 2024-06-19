#include <vector>
#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;
// model as bipartite multi matching, i.e vtxs in A can pair up with multiple vtxs in B, but vtxs in B can only pair up
// with 1 vtx in A
// also the vtx representing days, outward edge is 2, as we need 2 people per day. The output edge of the day vts to T is 2 to ensure that 2 people are assigned to each day
// binary seach maximum days, 
// edge from s to vtx representing person is numDays, and we binary search on numDays

class Dinic {
public:
    vector<vector<int>> capacity;
    vector<vector<int>> flow;
    vector<vector<int>> list;
    int N;
    int S;
    int T;
    int INF = 1000000007;
    int bestFlow;

    Dinic(vector<vector<int>>& matrix, int n, int s, int t) {
        capacity = matrix;
        flow = vector(n, vector(n, 0));
        N = n;
        S = s;
        T = t;
        buildAdjList();
    }

    void buildAdjList() {
        list = vector(N, vector<int>());
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j < N; j ++) {
                if (capacity[i][j] > 0) {
                    list[i].push_back(j);
                    list[j].push_back(i);
                }
            }
        }
    }

    bool bfs(vector<vector<int>>& adjList) {
        vector<bool> visited(N, false);
        queue<int> myQ;
        bool canReachT = false;
        myQ.push(S);
        while (!myQ.empty()) {
            int len = myQ.size();
            for (int i = 0; i < len; i ++) {
                int v = myQ.front();
                myQ.pop();
                visited[v] = true;
                myQ.push(v);
                if (v == T) canReachT = true;
            }

            for (int i = 0; i < len; i ++) {
                int v = myQ.front();
                myQ.pop();
                vector<int>& nbrs = list[v];
                for (int i : nbrs) {
                    if (capacity[v][i] > 0 && !visited[i]) {
                        myQ.push(i);
                        adjList[i].push_back(v);
                    }
                }

            }
        }
        return canReachT;
    }

    int dfs(vector<vector<int>>& adjList, int v, int minEdge) {
        if (v == S) {
            return minEdge;
        } else {
            while (!adjList[v].empty()) {
                int src = adjList[v].back();
                int ans = dfs(adjList, src, min(minEdge, capacity[src][v]));
                if (ans != INF) {
                    if (ans == capacity[src][v]) adjList[v].pop_back();
                    flow[src][v] += ans;
                    flow[v][src] -= ans;
                    capacity[src][v] -= ans;
                    capacity[v][src] += ans;
                    return ans;
                } else {
                    adjList[v].pop_back();
                }
            }
            return INF;
        }
    }

    int maxFlow() {
        bestFlow = 0;
        while (true) {
            vector<vector<int>> adjList(N, vector<int>());
            bool canReach = bfs(adjList);
            if (!canReach) break;
            while (true) {
                int toAdd = dfs(adjList, T, INF);
                if (toAdd == INF) break;
                bestFlow += toAdd;
            }
        }
        return bestFlow;
    }
};


Dinic* bestMin(vector<vector<int>>& matrix, int m, int n) {
    int s = 1;
    int e = n;
    while (s < e) {
        int mid = (s + e) / 2;
        for (int i = 1; i <= m; i ++) {
            matrix[0][i] = mid;
        }
        Dinic* sol = new Dinic(matrix, matrix.size(), 0, matrix.size() - 1);
        sol->maxFlow();
        if (sol->bestFlow >= 2 * n) {
            e = mid;
        } else {
            s = mid + 1;
        }
    }
    //cout << s << endl;
    for (int i = 1; i <= m; i ++) {
        matrix[0][i] = s;
    }
    Dinic* sol = new Dinic(matrix, matrix.size(), 0, matrix.size() - 1);
    sol->maxFlow();
    return sol;
}

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> matrix = vector(m + n + 2, vector(m + n + 2, 0));
    vector<string> names;
    for (int i = m + 1; i <= m + n; i ++) {
        matrix[i][m + n + 1] = 2;
    }
    for (int i = 1; i <= m; i ++) {
        string name;
        int d;
        cin >> name >> d;
        names.push_back(name);
        for (int j = 0; j < d; j ++) {
            int day;
            cin >> day;
            matrix[i][m + day] = 1;
        }
    }

    
    
    
    Dinic *sol = bestMin(matrix, m, n);
    int maxDays = -1;
    vector<vector<string>> assigned = vector(n, vector<string>());
    for (int i = 1; i <= m; i ++) {
        int count = 0;
        for (int j = m + 1; j <= m + n; j ++) {
            if (sol->flow[i][j] >= 1) {
                count ++;
                assigned[j - m - 1].push_back(names[i - 1]);
            }
        }
        maxDays = max(maxDays, count);
    }
    cout << maxDays << endl;
    for (int i = 0; i < assigned.size(); i ++) {
        printf("Day %d: %s %s\n", i + 1, assigned[i][0].c_str(), assigned[i][1].c_str());
    }

}



