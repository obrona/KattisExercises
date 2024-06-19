#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <chrono>
using namespace std;

// among all the maximum matching between friends and suggestions, we want to find the maximum matching that results in the
// maximum number of suggestions Khadira implements
// for example in a maximum matching, the suggestions are s1, s2, s3 ... sk, we want this set to result in maximum flow
// if we have a bipartite graph of src -> [s1, s2 ... sk] -> [cat1, cat2 ... catn] where flow from src to si is 1
// flow from si to catj is 1 if si falls under catj
// and flow from catj to sink is the max number of suggestions Khadira wants to implement from catj

// the key here is to realise that suppose a maximal matching between friends and suggestions results in maximum flow from suggestions 
// since is not maximum, there exists an augmenting path
// the key here is that the augmenting path will only add to the suggestions produced
// eg a0 b1a1 b2a2 b3, where a0 is unmatched b1a1 is matched and so on
// we will get a0b1 a1b2  a2b3
// notice that b1 and b2 remain, this means the suggestions produced by the maximal matching
// needed for the maximum flow betweem suggestions and categories can be extended.

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

template <typename T>
void print(vector<T> arr) {
    for (T t : arr) {
        cout << t << " ";
    }
    cout << endl;
}

bool isLetter(char c) {
    int code = c;
    return (48 <= code && code <= 57) || (97 <= code && code <= 122) ? true : false;
}

vector<string> split(string& s, char delimiter) {
    while (!isLetter(s[s.size() - 1])) {
        s.pop_back();
    }
    
    vector<string> out;
    int p = 0;
    while (p < s.size() && s[p] != '\n') {
        int end = p;
        while (end < s.size() && s[end] != delimiter && s[end] != '\n') {
            end ++;
        }
        out.push_back(s.substr(p, end - p));
        p = end + 1;
    }
    return out;
}




int main() {
    unordered_map<string, int> map;
    int F, S, C, N;
    string str;
    getline(cin, str);
    vector<string> values = split(str, ' ');
    F = stoi(values[0]);
    S = stoi(values[1]);
    C = stoi(values[2]);
    N = F + 2 * S + C;
    Edmonds dn(N + 2, N, N + 1);

    for (int i = 0; i < F; i ++) {
        dn.addEdge(N, i, 1);
    }
    
    
    int p = F;
    for (int i = 0; i < F; i ++) {
        string s;
        getline(cin, s);
        vector<string> suggestions = split(s, ' ');
        for (string& suggestion : suggestions) {
            if (map.find(suggestion) == map.end()) {
                map[suggestion] = p;
                dn.addEdge(p, p + S, 1);
                p ++;
            }
            dn.addEdge(i, map[suggestion], 1);
        }
    }

    for (int i = 0; i < C; i ++) {
        int node = F + 2 * S + i;
        string s;
        getline(cin, s);
        vector<string> arr = split(s, ' ');
        int cap = stoi(arr[0]);
        dn.addEdge(node, N + 1, cap);
        for (int i = 1; i < arr.size(); i ++) {
            string& a = arr[i];
            if (map.find(a) == map.end()) {
                map[a] = p;
                dn.addEdge(p, p + S, 1);
                p ++;
            }
            dn.addEdge(map[a] + S, node, 1);
        }
    }

    int ans = dn.maxFlow();
    cout << ans;
}