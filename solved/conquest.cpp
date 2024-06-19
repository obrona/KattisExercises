#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int maxSize(vector<vector<int>>& adjList, vector<int> armySize, int n) {
    int currSize = armySize[0];
    auto cmp = [](vector<int>& x, vector<int>& y) -> bool {return x[1] > y[1];};
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
    vector<bool> invaded = vector(n, false);
    invaded[0] = true;
    vector<int>& nbrs = adjList[0];
    for (int i = 0; i < nbrs.size(); i ++) {
        pq.push({nbrs[i], armySize[nbrs[i]]});
    }
    while (!pq.empty()) {
        const vector<int>& next = pq.top();
        int node = next[0];
        int size = next[1];
        pq.pop();
        if (!invaded[node] && size < currSize) {
            invaded[node] = true;
            currSize += size;
            vector<int>& nbrs = adjList[node];
            for (int i = 0; i < nbrs.size(); i ++) {
                int nbr = nbrs[i];
                if (!invaded[nbr]) {
                    pq.push({nbr, armySize[nbr]});
                }
            }
        }
    }
    
    return currSize;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adjList = vector(n, vector<int>());
    vector<int> armySize = vector<int>();
    for (int i = 0; i < m; i ++) {
        int x, y;
        cin >> x >> y;
        adjList[x - 1].push_back(y - 1);
        adjList[y - 1].push_back(x - 1);
    }
    for (int i = 0; i < n; i ++) {
        int size;
        cin >> size;
        armySize.push_back(size);
    }
    int ans = maxSize(adjList, armySize, n);
    //cout << "hello";
    cout << ans;
    return 0;
}