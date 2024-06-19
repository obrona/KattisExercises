#include <iostream>
#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <queue>
using namespace std;

// key idea is the if person 1 takes a minutes, p2 takes b minutes a != b, then p1, p2 can never meet if they reach the same intersection
// suppose so, since shortest time from that intersection is fixed, this means p1, p2 take the same minimum time should they meet at some intersection at the same time
// but if p1, p2 take the same amount of time, they will meet if they reach the same intersection at the same time
// group commuters according to the time taken to reach downtown, do max flow for each group

// just use Ford Fulkerson, because capacity is very low at 1000
// time complexity will be O(EC)

// Heads Up : Ford Fulkerson > Edmonds > Dinics (got MLE for Dinics)


#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <chrono>
using namespace std;

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


class Dinics {
public:
    int INF = 1000000000;
    vector<unordered_map<int, int>> capacities;
    int n, s, t;

    Dinics(int N, int S, int T) {
        n = N;
        s = S;
        t = T;
        capacities = vector(n, unordered_map<int, int>());
    }

    // construct level graph
    bool bfs(vector<vector<int>>& adjList) {
        queue<int> q;
        vector<bool> visited(n, false);
        q.push(s);
        while (!q.empty()) {
           int len = q.size();
           for (int i = 0; i < len; i ++) {
               int src = q.front(); q.pop();
               if (visited[src]) {
                    len --; // MUST REMEMBER TO MINUS :(((
                    continue;
               }
               visited[src] = true;
               q.push(src);
               if (src == t) {
                    return true;
               }
           }
           
           for (int i = 0; i < len; i ++) {
               int src = q.front(); q.pop();
               for (const auto& [key, value] : capacities[src]) {
                   if (!visited[key] && value > 0) {
                       adjList[key].push_back(src);
                       q.push(key);
                   }
               }
           }
            
        }
        return false;
    }

    int dfs(int dest, vector<vector<int>>& adjList, int minEdge) {
       
        if (dest == s) {
            return minEdge;
            
        } else {
            while (!adjList[dest].empty()) {
                int src = adjList[dest].back();

                int cap = capacities[src][dest];
                int res = dfs(src, adjList, min(minEdge, cap));
                if (res == INF) {
                    adjList[dest].pop_back();
                } else {
                    capacities[src][dest] -= res;
                    capacities[dest][src] += res;
                    if (capacities[src][dest] == 0) adjList[dest].pop_back();
                    return res;
                }
            }

            return INF; // cannot find a way back to src
        }
    }

    int maxFlow() {
        int maxflow = 0;
        while (true) {
            vector<vector<int>> adjList = vector(n, vector<int>());
            bool canReachT = bfs(adjList);
            if (!canReachT) break;
            int flow = 0;
            while (true) {
                int canAdd = dfs(t, adjList, INF);
                if (canAdd == INF) break;
                maxflow += canAdd;
            }
        }
        return maxflow;
    }

    void addEdge(int src, int dest, int c) {
        // this case checks when we have added an edge dest->src previously and later we need to add an edge src->dest
        bool doneBefore = capacities[src].find(dest) != capacities[src].end();
        capacities[src][dest] = c;
        if (!doneBefore) capacities[dest][src] = 0;
    }

    void printCapacities() {
        for (int i = 0; i < n; i ++) {
            for (const auto& [key, value] : capacities[i]) {
                cout << "(" << i << " " << key << " " << value << ") ";
            }
            cout << endl;
        }
    }
};



class Solution {
public:
    int n;
    vector<vector<vector<int>>> adjList;
    vector<int> distance;
    vector<unordered_map<int, int>> capacities;
    unordered_map<int, int> numCommuters;
    unordered_map<int, vector<int>> group;
    vector<unordered_map<int, int>> flowGraph;
    
    int INF = 1000000000;

    Solution(int n) {
        this->n = n;
        adjList = vector(n + 1, vector<vector<int>>());
        distance = vector(n + 1, -1);
        capacities = vector(n + 1, unordered_map<int, int>());
        
    }

    void dijkstra() {
        //distance[start] = 0;
        auto cmp = [] (vector<int>& a, vector<int>& b) -> bool {return a[1] > b[1];};
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        pq.push({1, 0});
        while (!pq.empty()) {
            vector<int> next = pq.top();
            pq.pop();
            
            int vtx = next[0];
            int dist = next[1];
            if (distance[vtx] != -1) continue;
            distance[vtx] = dist;
            if (numCommuters.find(vtx) != numCommuters.end()) {
                group[dist].push_back(vtx);
            }
            for (vector<int>& child : adjList[vtx]) {
                if (distance[child[0]] == -1) {
                    pq.push({child[0], dist + child[1]});
                }
            }
        }
    }

    // build the DAG
    void buildCapacity() {
        for (int i = 1; i <= n; i ++) {
            for (vector<int>& child : adjList[i]) {
                if (distance[child[0]] + child[1] == distance[i]) {
                    capacities[i][child[0]] += 1; // need to account for multiple edges between 2 vertices
                    capacities[child[0]][i] = 0; // no need to worry about potentially 'resetting the backward edge, because is DAG
                }
            }
        }
    }

    int ff(int src, int minEdge, vector<bool>& visited) {
        if (visited[src]) {
            return INF;
        }
        visited[src] = true;
        if (src == 1) {
            return minEdge;
        } else {
            for (const auto& [dest, value] : flowGraph[src]) {
                if (value <= 0) continue;
                int res = ff(dest, min(value, minEdge), visited);
                if (res == INF) continue;
                flowGraph[src][dest] -= res;
                flowGraph[dest][src] += res;
                return res;
            }
            return INF;
        }
    }



    int findAns() {
        int sum = 0;
        
        for (const auto& [key, value] : group) {
            // reset outward edges from src to commuter nodes
            for (const auto& [key2, value2] : numCommuters) {
                capacities[0][key2] = 0;
                capacities[key2][0] = 0;
            }
            for (int v : value) {
                capacities[0][v] = numCommuters[v];
            }
            Edmonds dn(n + 1, 0, 1);
            dn.adjList = capacities;
            sum += dn.maxFlow();
            
            /*flowGraph = capacities;
            while (true) {
                vector<bool> visited(n + 1, false);
                int add = ff(0, INF, visited);
                
                if (add != INF) {
                    sum += add;
                    //cout << add << endl;
                } else {
                    break;
                }
            }*/
           
        }
        return sum;

    }

};





int main() {
    int n, m, c;
    cin >> n >> m >> c;
    Solution sol(n);
    for (int i = 0; i < m; i ++) {
        int x, y, t;
        cin >> x >> y >> t;
        sol.adjList[x].push_back({y, t});
        sol.adjList[y].push_back({x, t});
    }
    for (int i = 0; i < c; i ++) {
        int city;
        cin >> city;
        sol.numCommuters[city] += 1;
    }
    sol.dijkstra();
    sol.buildCapacity();
    cout << sol.findAns() << endl;
    
}