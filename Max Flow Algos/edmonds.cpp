#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Edmonds {
public:
    // adjList[u][v] returns capacity c;
    // can iterate through hashmaps
    vector<unordered_map<int, int>> adjList;
    int N, S, T, maxflow;

    Edmonds(int n, int s, int t) {
        N = n;
        S = s;
        T = t;
        adjList = vector(N, unordered_map<int, int>());
    }

    void addEdge(int u, int v, int c) {
        if (adjList[u].find(v) != adjList[u].end()) {
            adjList[u][v] = c;
        } else {
            adjList[u][v] = c;
            adjList[v][u] = 0;
        }
    }

    bool bfs(vector<int>& parents) {
        bool canReachT = false;
        fill(parents.begin(), parents.end(), -1);
        queue<int> q;
        q.push(S);
        parents[S] = -1;
        while (!q.empty()) {
            int src = q.front();
            q.pop();
            if (src == T) {
                canReachT = true;
                break;
            }
            unordered_map<int, int>& childs = adjList[src];
            for (const auto& [key, value] : childs) {
                if (parents[key] == -1 && value > 0) {
                    parents[key] = src;
                    q.push(key);
                }
            } 
        }
        return canReachT;
    }

    int augmentPath(vector<int>& parents) {
        int minEdge = 1000000000;
        for (int dest = T; dest != S; dest = parents[dest]) {
            int src = parents[dest];
            minEdge = min(minEdge, adjList[src][dest]);
        }
        for (int dest = T; dest != S; dest = parents[dest]) {
            int src = parents[dest];
            adjList[src][dest] -= minEdge;
            adjList[dest][src] += minEdge;
        }
        return minEdge;
    }

    int maxFlow() {
        maxflow = 0;
        vector<int> parents(N, -1);
        while (true) {
            bool canAdd = bfs(parents);
            if (!canAdd) break;
            maxflow += augmentPath(parents);
        }
        return maxflow;
    }
};

int main() {
    int n, s, t, e;
    cin >> n >> s >> t >> e;
    Edmonds ed(n, s, t);
    for (int i = 0; i < e; i ++) {
        int src, dest, c;
        cin >> src >> dest >> c;
        ed.addEdge(src, dest, c);
    }
    cout << ed.maxFlow() << endl;
}