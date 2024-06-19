#include <vector>
#include <iostream>
#include <queue>
#include <stdio.h>
typedef long long int;
using namespace std;

// the problem with this question is that there can be edges u->v and v->u and this has to be accounted for

template <typename T>
void print(vector<vector<T>> arr) {
    for (vector<T> a : arr) {
        for (T x : a) {
            cout << x << " ";
        }
        cout << endl;
    }
}

template <typename T>
void print(vector<T> arr) {
    for(T x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

class Dinic {
public:
    vector<vector<int>> capacity;
    vector<vector<int>> flow;
    int numVtxs;
    int s;
    int t;
    const int INF = (int)1 << 60;
    int bestFlow = 0;

    Dinic(vector<vector<int>>& matrix, int n, int s, int t) {
        capacity = matrix;
        flow = vector(n, vector<int>(n, 0));
        numVtxs = n;
        this->s = s;
        this->t = t;
    }

    // builds the level DAG. There are only edges from vtx of level i to vtx of level i + 1
    // returns true if t can be reached i.e exist augmenting path
    bool bfs(vector<vector<int>>& adjList, int s) {
        queue<int> myQ;
        vector<bool> visited(numVtxs, false);
        bool canReachT = false;
        myQ.push(s);
    
        while (!myQ.empty()) {
            int len = myQ.size(); // currently all vtxs in queue are from the same level;
            vector<int> temp;
            for (int i = 0; i < len; i ++) {
                int vtx = myQ.front();
                myQ.pop();
                visited[vtx] = true;
                temp.push_back(vtx);
            }
            for (int vtx : temp) {
                if (vtx == t) canReachT = true;
                vector<int>& nexts = capacity[vtx];
                for (int i = 0; i < numVtxs; i ++) {
                    if (visited[i] == false && capacity[vtx][i] > 0LL) {
                        adjList[i].push_back(vtx);
                        myQ.push(i);
                    }
                }
            }
        }
        return canReachT;
    }

   

    int dfs(vector<vector<int>>& adjList, int vtx, int minEdge) {
        if (vtx == s) {
            return minEdge;
        } else {
            // remember src is next, dest is vtx
            while (!adjList[vtx].empty()) {
                int next = adjList[vtx].back();
                int ans = dfs(adjList, next, min(minEdge, capacity[next][vtx]));
                if (ans != INF) {
                    capacity[next][vtx] -= ans;
                    capacity[vtx][next] += ans;
                    flow[next][vtx] += ans;
                    flow[vtx][next] -= ans;
                    if (capacity[next][vtx] == 0) adjList[vtx].pop_back();
                    return ans;
                } else {
                    adjList[vtx].pop_back();
                }
            }
            return INF;

        }
    }

    int maxFlow() {
        int sum = 0;
        while (true) {
            vector<vector<int>> adjList = vector(numVtxs, vector<int>());
            bool can = bfs(adjList, s);
            if (!can) break;
            while (true) {
                int canAdd = dfs(adjList, t, INF);
                //cout << canAdd << endl;
                if (canAdd != INF) {
                    sum += canAdd;
                } else {
                    break;
                }
            }
        }
        bestFlow = sum;
        return sum;
    }

};

class Edmonds {
public:
    vector<vector<int>> adjMatrix;
    vector<vector<int>> flowMatrix;
    int numVtxs;
    int s;
    int t;
    const int INF = (int)1 << 60;
    int bestflow = 0;

    Edmonds(vector<vector<int>>& matrix, int n, int s, int t) {
        adjMatrix = matrix;
        flowMatrix = vector(n, vector<int>(n, 0));
        numVtxs = n;
        this->s = s;
        this->t = t;
    }

    // parent have to initliased to -1;
    bool bfs(vector<int>& parent) {
        queue<int> myQ;
        bool canReachT = false;
        myQ.push(s);
        parent[s] = s;
        while (!myQ.empty()) {
            int vtx = myQ.front();
            myQ.pop();
            for (int i = 0; i < numVtxs; i ++) {
                if (parent[i] == -1 && adjMatrix[vtx][i] > 0) {
                    parent[i] = vtx;
                    myQ.push(i);
                    if (i == t) canReachT = true;
                }
            }
        }
        return canReachT;
    }

    int maxFlow() {
        int sum = 0;
        while (true) {
            vector<int> parent(numVtxs, -1);
            bool can = bfs(parent);
            //print(parent);
            if (!can) break;
            int minEdge = INF;
            for (int vtx = t; vtx != s; vtx = parent[vtx]) {
                minEdge = min(minEdge, adjMatrix[parent[vtx]][vtx]);
            }
            for (int vtx = t; vtx != s; vtx = parent[vtx]) {
                adjMatrix[parent[vtx]][vtx] -= minEdge;
                adjMatrix[vtx][parent[vtx]] += minEdge;
                flowMatrix[parent[vtx]][vtx] += minEdge;
                flowMatrix[vtx][parent[vtx]] -= minEdge;
            }
            sum += minEdge;
        }
        bestflow = sum;
        return sum;
    }
};



int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (int i = 0; i < m; i ++) {
        int u, v;
        int c;
        cin >> u >> v >> c;
        matrix[u][v] = c;
    }
    Dinic dn(matrix, n, s, t);
    dn.maxFlow();
    vector<vector<int>> storeEdges;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (dn.flow[i][j] > 0) {
                storeEdges.push_back({i, j, dn.flow[i][j]});
            }
        }
    }
    //printf("%d", ed.bestflow);
    cout << n << " " << dn.bestFlow << " " << storeEdges.size() << endl;
    for (vector<int>& e : storeEdges) {
        cout << e[0] << " " << e[1] << " " << e[2] << endl;
    }
}
