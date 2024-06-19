#include <vector>
#include <iostream>
using namespace std;

// if graph is connected and not bipartite, for any 2 vertices a, b there exists a walk of even length. 
// No need to add any edges, except for between 2 connected components
// reason is exist odd cycle -> all vertices in odd cycle can be infected, if vtx a outside cycle and vtx b inside cycle have odd path, 
// start from a vtx adjacennt to the b in the cycle

// if graph is bipartite, add n - 1 edges, where n is the number of connected components, this is minimum, as it is a 'tree'
// if we only add n - 1 edges to make graph connected, resultant graph is still bipartite.
// then add 1 more edge, betweem 2 vtxs in the same side, to create a odd cycle.

class UnionFind {
public:
    vector<int> parents;
    vector<int> weight;

    UnionFind(int n) {
        parents = vector(n, 1);
        weight = vector(n, 1);
        for (int i = 0; i < n; i ++) {
            parents[i] = i;
        }
    }
        
    

    int find(int x) {
        if (parents[x] == x) {
            return x;
        } else {
            parents[x] = find(parents[x]);
            return parents[x];
        }
    }

    void join(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (x != y) {
            if (weight[px] >= weight[py]) {
                parents[py] = px;
                weight[px] += weight[py];
            } else {
                parents[px] = py;
                weight[py] += weight[px];
            }
        }
    }

    int countParent() {
        int sum = 0;
        // start from 1, as nodes are numbered from 1 to N
        for (int i = 1; i < parents.size(); i ++) {
            if (parents[i] == i) {
                sum ++;
            }
        }
        return sum;
    }
};

vector<vector<int>> adjList;

bool checkBipartite(int n, int p, vector<int>& color, int c) {
    if (color[n] != -1) {
        return (color[n] == c) ? true : false;
    } else {
        color[n] = c;
        vector<int>& childs = adjList[n];
        for (int child : childs) {
            if (child != p) {
                bool res = checkBipartite(child, n, color, 1 - c);
                if (!res) {
                    return false;
                }
            }
        }
        return true;
    }
} 

void print(vector<int> a) {
    for (int x : a) {
        cout << x << endl;
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    adjList = vector(n + 1, vector<int>());
    UnionFind uf(n + 1);
    for (int i = 0; i < m; i ++) {
        int x, y;
        cin >> x >> y;
        uf.join(x, y);
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }
    int numCompo = uf.countParent();
    bool bipartite = true;
    vector<int> color = vector(n + 1, -1);
    for (int i = 1; i <= n; i ++) {
        if (color[i] == -1) {
            //cout << i << endl;
            bool temp = checkBipartite(i, i, color, 0);
            bipartite = bipartite && temp;
        }
    }
    //checkBipartite(1, 1, color, 0);
    //print(color);
    //cout << bipartite << " " << numCompo << endl;
    if (!bipartite) {
        cout << numCompo - 1 << endl;
    } else {
        cout << numCompo << endl;
    }
}

