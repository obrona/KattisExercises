#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;
// if k >= 2, we can traverse all edges
// if k = 1, we have to find longest path in tree, using 2 dfs




unordered_map<long long, unordered_map<long long, long long>> map;

vector<vector<vector<long long>>> adjList;

vector<long long> bestScore;

vector<vector<vector<long long>>> best2;



void insert(vector<vector<long long>>& store, vector<long long> score) {
    auto cmp = [](vector<long long>& a, vector<long long>& b) -> bool{return a[1] > b[1];};
    store.push_back(score);
    sort(store.begin(), store.end(), cmp);
    if (store.size() > 2) {
        store.pop_back();
    }
}

long long dfs1(int node, int parent) {
    long long s = 0;
    vector<vector<long long>>& nbrs = adjList[node];
    for (int i = 0; i < nbrs.size(); i ++) {
        long long nbr = nbrs[i][0];
        if (nbr != parent) {
            long long score = map[node][nbr] + dfs1(nbr, node);
            s = max(s, score);
            insert(best2[node], {nbr, score});
        }
    }
    return s;
}

void dfs2(int node, int parent) {
    if (node == parent) {
        vector<vector<long long>>& b2 = best2[node];
        if (b2.size() == 0) {
            bestScore[node] = 0LL;
        } else if (b2.size() == 1) {
            bestScore[node] = b2[0][1];
        } else {
            bestScore[node] = b2[0][1] + b2[1][1];
        }
    } else {
        vector<vector<long long>>& b2 = best2[node];
        long long bScore = 0;
        if (b2.size() == 0) {
            bScore = 0;
        } else if (b2.size() == 1) {
            bScore = b2[0][1];
        } else {
            bScore = b2[0][1] + b2[1][1];
        }
        long long bScoreParent = 0;
        vector<vector<long long>>& b2p = best2[parent];
        long long p1 = (b2.size() == 0) ? 0 : b2[0][1];
        long long p2 = (b2p.size() == 1) ? 0 
                                         : (b2p[0][0] == node) 
                                         ? b2p[1][1]
                                         :b2p[0][1];
        bScoreParent = p1 + p2 + map[node][parent];
        insert(b2, {parent, p2 + map[node][parent]}); // update the top 2 paths, so the childrens' result will be correct
        bestScore[node] = max(bScore, bScoreParent);
    }
    vector<vector<long long>> nbrs = adjList[node];
    for (int i = 0; i < nbrs.size(); i ++) {
        if (nbrs[i][0] != parent) {
            dfs2(nbrs[i][0], node);
        }
    }
}

int main() {
    int n, k;
    long long sumEdges = 0;
    cin >> n >> k;
    adjList = vector<vector<vector<long long>>>(n + 1, vector<vector<long long>>());
    bestScore = vector<long long>(n + 1, 0);
    best2 = vector<vector<vector<long long>>>(n + 1, vector<vector<long long>>());
    //cout << adjList.size() << endl;
    //cout << best2.size() << endl;
    for (int i = 0; i < n - 1; i ++) {
        long long u, v, c;
        cin >> u >> v >> c;
        map[u][v] = c;
        map[v][u] = c;
        sumEdges += c;
        adjList[u].push_back({v, c});
        adjList[v].push_back({u, c});
    }
    if (k >= 2) {
        cout << sumEdges;
        return 0;
    }
    dfs1(1,1);
    dfs2(1,1);
    
    long long m = 0;
    for (long long x : bestScore) {
        //cout << x << endl;
        m = max(x, m);
    }
    cout << m;


}
