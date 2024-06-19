#include <queue>
#include <vector>
#include <iostream>
using namespace std;
// in the state for SSSP, include k, the remaining fireworks left
// state + cost = {base I, k, cost}



int dijkstra(vector<vector<int>>& adjMatrix, vector<int>& elevation, int goal, int n, int k) {
    auto cmp = [] (vector<int>& x, vector<int>& y) -> bool {return x[2] > y[2];};
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
    vector<vector<int>> visited = vector(n, vector(k + 1, -1));
    pq.push({0, k, 0});
    while (!pq.empty()) {
        const vector<int>& node = pq.top();
        int base = node[0];
        int fireLeft = node[1];
        int dist = node[2];
        pq.pop();
        if (visited[base][fireLeft] == -1) {
            visited[base][fireLeft] = dist;
            //vector<int>& nbrs = adjMatrix[base];
            for (int i = 0; i < n; i ++) {
                if (i != base) {
                    int fireCost = (elevation[i] - elevation[base] <= 0) ? 0 : elevation[i] - elevation[base];
                    if (fireCost <= fireLeft) {
                        pq.push({i, fireLeft - fireCost, dist + adjMatrix[base][i]});
                    }
                }
            }
        }
    }
    int minTime = 999999999;
    for (int i = 0; i <= k; i ++) {
        minTime = (visited[goal][i] != -1) ? min(minTime, visited[goal][i]) : minTime;
    }
    return (minTime >= 999999999) ? -1 : minTime;
}

/*int main() {
    vector<int> elevation = {3, 6, 2};
    vector<vector<int>> adjMatrix = {{0,1,10}, {10,0,1},{10,10,0}};
    int goal = 2;
    int k = 3;
    int ans = dijkstra(adjMatrix, elevation, goal, 3, 3);
    cout << ans;
}*/

int main() {
    int n, goal, k;
    cin >> n >> goal >> k;
    goal -= 1;
    vector<int> elevation = vector<int>();
    vector<vector<int>> adjMatrix = vector(n, vector(n, 0));
    for (int i = 0; i < n; i ++) {
        int h;
        cin >> h;
        elevation.push_back(h);
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            int time;
            cin >> time;
            adjMatrix[i][j] = time;
        }
    }
    int ans = dijkstra(adjMatrix, elevation, goal, n, k);
    cout << ans;;
    return 0;
}