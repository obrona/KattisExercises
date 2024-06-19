#include <vector>
#include <queue>
#include <stdio.h>
#include <iostream>
using namespace std;

//SSSP from house, node 2. Only go from A to B if dist(B, house) < dist(A, house)
vector<vector<int>> adjMatrix;
vector<int> dist;
vector<int> dp;

void dijkstra(int start) {
    auto cmp = [](vector<int>& a, vector<int>& b) -> bool {return a[1] > b[1];};
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
    pq.push({start, 0});
    while(!pq.empty()) {
        vector<int> next = pq.top();
        pq.pop();
        int node = next[0];
        int dst = next[1];
        
        if (dist[node] == -1) {
            dist[node] = dst;
            for (int i = 1; i < adjMatrix[0].size(); i ++) {
                if (adjMatrix[node][i] != -1 && dist[i] == -1) {
                    pq.push({i, dst + adjMatrix[node][i]});
                }
            }
        }
    }
}

int countWays(int node) {
    if (dp[node] != -1) {
        return dp[node];
    } else if (dist[node] == 0) {
        return 1;
    } else {
        int sum = 0;
        for (int i = 1; i < adjMatrix[0].size(); i ++) {
            if (adjMatrix[node][i] != -1 && dist[i] < dist[node]) {
                sum += countWays(i);
            }
        }
        dp[node] = sum;
        return sum;
    }
}

void print(vector<int> arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    while (true) {
        int N, M;
        cin >> N;
        if (N == 0) {
            return 0;
        }
        cin >> M;
        adjMatrix = vector(N + 1, vector(N + 1, -1));
        dist = vector(N + 1, -1);
        dp = vector(N + 1, -1);
        for (int i = 0; i < M; i ++) {
            int s, e, len;
            cin >> s >> e >> len;
            adjMatrix[s][e] = len;
            adjMatrix[e][s] = len;
        }
        dijkstra(2);
        //print(dist);
        int ans = countWays(1);
        //print(dp);
        cout << ans << endl;
    }
}