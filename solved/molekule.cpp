#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

// the graph is a tree
// so if parent node all edges point down, child node all edges point up
// 0 for up 1 for down
vector<vector<int>> adjList;
unordered_map<int, unordered_map<int, int>> map;

void helper(int node, int parent, int dir) {
    vector<int>& nbrs = adjList[node];
    for (int nbr : nbrs) {
        if (nbr != parent) {
            map[min(node, nbr)][max(node, nbr)] = (node < nbr) ? dir : !dir;
            helper(nbr, node, !dir);
        }
    }
}

int main() {
    int n;
    cin >> n;
    adjList = vector(n + 1, vector<int>());
    vector<vector<int>> edges;
    for (int i = 0; i < n - 1; i ++) {
        int x, y;
        cin >> x >> y;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
        edges.push_back({x, y});
    }
    helper(1, 1, 1);
    for (int i = 0; i < n - 1; i ++) {
        vector<int>& edge = edges[i];
        if (edge[0] < edge[1]) {
            int dir = map[edge[0]][edge[1]];
            cout << dir << endl;
        } else {
            int dir = map[edge[1]][edge[0]];
            cout << !dir << endl;
        }
        
    }

}