#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//idea, once a node is a child , then the subtree rooted at the child, disconnected from its parent, cannot be the root
// we remove such subtree, endresult is a tree that is undirected, in which case any node can be the root

vector<vector<int>> adjList;
vector<int> sureParent;
vector<bool> confirmNotRoot;

void confirmNot(int node, int parent) {
    confirmNotRoot[node] = 1;
    vector<int> nbrs = adjList[node];
    for (int i = 0; i < nbrs.size(); i ++) {
        if (nbrs[i] != parent) {
            confirmNot(nbrs[i], node);
        }
        //confirmNot(nbrs[i], node);
    }
}

void findPossibleRoots() {
    for (int i = 0; i < sureParent.size(); i ++) {
        if (sureParent[i] != -1) {
            confirmNot(i, sureParent[i]);
        }
    }
    vector<int> possible;
    for (int i = 0; i < confirmNotRoot.size(); i ++) {
        if (!confirmNotRoot[i]) {
            possible.push_back(i);
        }
    }
    sort(possible.begin(), possible.end());
    for (int i = 0; i < possible.size(); i ++) {
        cout << possible[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    adjList = vector(n, vector<int>());
    sureParent = vector(n, -1);
    confirmNotRoot = vector<bool>(n, 0);
    for (int i = 0; i < n - 1; i ++) {
        int a, c;
        char b;
        cin >> a;
        cin >> b;
        cin >> c;

        adjList[a].push_back(c);
        adjList[c].push_back(a);
        if (b == '>') {
            sureParent[c] = a;
        }
    }
    findPossibleRoots();
}
