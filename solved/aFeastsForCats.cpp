#include <vector>
#include <queue>
#include <iostream>
using namespace std;

// optimal solution is simply a MST
// Notice that suppose you go from v1 v2 v3 v4 ... vt, then go back to v1 to bring milk to other cats, you only need enough milk
// to go from v1 to vt, so that at vt you have esactly 0 milk left. Then you simply 'teleport' back to v1
// the edges you traverse from a tree, and you traverse each edge exactly once
// obviously best solution is a MST
// milk needed is sum of edges + # of vertices

auto cmp = [](vector<int>& x, vector<int> y) -> bool{return x[1] > y[1];};
vector<vector<int>> adjMatrix;

int primAlgo(vector<vector<int>>& matrix, int n) {
    vector<int> cost = vector(n, -1);
    int sum = 0;
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
    pq.push({0, 0});
    while(!pq.empty()) {
        vector<int> next = pq.top();
        //cout << next[0] << " " << next[1] << endl;
        pq.pop();
        if (cost[next[0]] == -1) {
            sum += next[1];
            cost[next[0]] = next[1];
            for (int i = 0; i < n; i ++) {
                if (i != next[0] && cost[i] == -1) {
                    pq.push({i, matrix[next[0]][i]});
                }
            }
        }
    }
    return sum;
}

int main() {
    int test;
    cin >> test;
    for (int i = 0; i < test; i ++) {
        int M, C;
        cin >> M >> C;
        adjMatrix = vector(C, vector(C, 0));
        for (int i = 0; i < C * (C - 1) / 2; i ++) {
            int x, y, e;
            cin >> x >> y >> e;
            adjMatrix[x][y] = e;
            adjMatrix[y][x] = e;
        }
        int milk = primAlgo(adjMatrix, C) + C;
        //cout << milk << endl;
        if (milk > M) {
            cout << "no" << endl;
        } else {
            cout << "yes" << endl;
        }
    }
}
