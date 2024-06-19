#include <vector>
#include <iostream>
#include <queue>
#include <stdio.h>
#define myINF 1000000000
typedef long long ll;

using namespace std;

// model as maxflow problem.
// Sensor capacties are just edges
// queue capactity are vertex capacities, so need to use vertex splitting technique
// queue 1 on downlink 1 can 'pass' some data to queue 1 on downlink 2
// downlink are still vertices, not edges, but no need vertex splitting technique as there is only 1 outward edge for each downlink

// maxflow2.cpp
// Eric K. Zhang; Aug. 7, 2017

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    vector<vector<int>> capacity;
    //vector<vector<int>> flow;
    vector<vector<int>> list;
    int N;
    int S;
    int T;
    int INF = 1000000007;
    int bestFlow;

    Dinic(vector<vector<int>>& matrix, int n, int s, int t) {
        capacity = matrix;
        //flow = vector(n, vector(n, 0));
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
                    list[j].push_back(i); // can later go other way in residual graph
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

    int dfs(vector<vector<int>>* adjList, int v, int minEdge) {
        if (v == S) {
            return minEdge;
        } else {
            while (!(*adjList)[v].empty()) {
                int src = (*adjList)[v].back();
                int ans = dfs(adjList, src, min(minEdge, capacity[src][v]));
                if (ans != INF) {
                    if (ans == capacity[src][v]) (*adjList)[v].pop_back();
                    //flow[src][v] += ans;
                    //flow[v][src] -= ans;
                    capacity[src][v] -= ans;
                    capacity[v][src] += ans;
                    return ans;
                } else {
                    (*adjList)[v].pop_back();
                }
            }
            return INF;
        }
    }

    int maxFlow() {
        bestFlow = 0;
        vector<vector<int>> adjList(N, vector<int>());
        while (true) {
            for (vector<int>& lst : adjList) lst.clear();
            
            bool canReach = bfs(adjList);
            if (!canReach) break;
            while (true) {
                int toAdd = dfs(&adjList, T, INF);
                if (toAdd == INF) break;
                bestFlow += toAdd;
            }
        }
        return bestFlow;
    }
};

class Edmonds {
public:
    vector<vector<int>> adjMatrix;
    vector<vector<int>> flowMatrix;
    vector<vector<int>> list;
    int numVtxs;
    int s;
    int t;
    const int INF = 1000000000;
    int bestflow = 0;

    Edmonds(vector<vector<int>>& matrix, int n, int s, int t) {
        adjMatrix = matrix;
        flowMatrix = vector(n, vector<int>(n, 0));
        numVtxs = n;
        this->s = s;
        this->t = t;
        buildAdjList();
    }

    void buildAdjList() {
        list = vector(numVtxs, vector<int>());
        for (int i = 0; i < numVtxs; i ++) {
            for (int j = 0; j < numVtxs; j ++) {
                if (adjMatrix[i][j] > 0) {
                    list[i].push_back(j);
                    list[j].push_back(i); // can later go other way in residual graph
                }
            }
        }
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
            for (int i : list[vtx]) {
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
                //flowMatrix[parent[vtx]][vtx] += minEdge;
                //flowMatrix[vtx][parent[vtx]] -= minEdge;
            }
            sum += minEdge;
        }
        bestflow = sum;
        return sum;
    }
};




int indexQ(int qid, int whichDay, int days) {
    return days * (qid - 1) + whichDay;
}

int indexD(int did, int queue, int days) {
    return 2 * queue * days + did;
}

int indexQOther(int qid, int whichDay, int days, int queue) {
    return queue * days + days * (qid - 1) + whichDay;
}

int main() {
    
    
    int sumData = 0;
    int n, q, s;
    cin >> n >> q >> s;
    
    int numVtxs = 2 * n * q + n + 2;
    vector<vector<int>> matrix(numVtxs, vector<int>(numVtxs, 0));
    vector<vector<int>> adjList(numVtxs, vector<int>());
    vector<int> sensorToQueue;
    for (int i = 0; i < s; i ++) {
        int qid;
        cin >> qid;
        sensorToQueue.push_back(qid);
    }
    for (int i = 1; i <= q; i ++) {
        int qCap;
        cin >> qCap;
        for (int j = 1; j <= n; j ++) {
            int qid = indexQ(i, j, n);
            int qidP = indexQOther(i, j, n, q);
            matrix[qid][qidP] = qCap;
            adjList[qid].push_back(qidP);
            if (j != n) {
                int qNext = indexQ(i, j + 1, n);
                matrix[qidP][qNext] = myINF;
                adjList[qidP].push_back(qNext);
            }
            int did = indexD(j, q, n);
            matrix[qidP][did] = myINF;
            adjList[qidP].push_back(did);
        }
        
    }
    for (int i = 1; i <= n; i ++) {
        int dId = indexD(i, q, n);
        int dCap;
        cin >> dCap;
        matrix[dId][numVtxs - 1] = dCap;
        adjList[dId].push_back(numVtxs - 1);
        for (int j = 0; j < s; j ++) {
            
            int sCap;
            cin >> sCap;
            sumData += sCap;
            int qid = indexQ(sensorToQueue[j], i, n);
            matrix[0][qid] += sCap;
            adjList[0].push_back(qid);
            
        }

    }

    //Dinic dn(matrix, numVtxs, 0, numVtxs - 1);
    //int ans = dn.maxFlow();
    Edmonds ed(matrix, numVtxs, 0, numVtxs - 1);
    int ans = ed.maxFlow();
    
    
    
    
    
    if (ans == sumData) {
        cout << "possible" << endl;
    } else {
        cout << "impossible" << endl;
    }

}






