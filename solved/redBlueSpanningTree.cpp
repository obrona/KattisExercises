#include <vector>
#include <iostream>
using namespace std;

// basically first we the make spanning forest using red edges only, so that we minimise the blue edges needed
// next we remove redudant blue edges, i.e blue edges that when added creates a cycle of blue edges only
// next the edges connecting different components in the red edges forest is blue edges only, and the graph is connected
// add the required blue edges
// if have not add k, add blue edges if available. During this step, adding a blue edge creates a cycle that contains a red edge
// if not this means a blue edge only cycle is created which is impossible

// if this algo fails, not possible to create spanning tree of k blue edges only
// if algo fails when adding blue edges to connect the red edges component, ed we hav 10 components after adding red edges only, and
// k = 5. obviously we cannot create a spanning tree
// if algo fails at the step when we add blue edges into the already spanning tree, this means we do not have enough blue edges, no spanning tree 
// with k blue edges can exist

// also must realise that number of blue edges after removing redundant blue edges is fixed. Number of blue edges to join red edges component is fixed
// which is number of red components - 1
// hence number of blue edges leftover to satsify k blue edges needed is fixed, no matter the order of how blue edges are processed using union find

struct Edge {
    int x, y;
};

class UnionFind {
public:
    vector<int> parents;
    vector<int> weights;

    UnionFind(int n) {
        parents = vector(n, 0);
        weights = vector(n, 1);
        for (int i = 0; i < parents.size(); i ++) {
            parents[i] = i;
        }
    }

    int find(int x) {
        if (x == parents[x]) return x;
        int p = find(parents[x]);
        parents[x] = p;
        return p;
    }

    void join(int x, int y) {
        int pX = find(x);
        int pY = find(y);
        if (x == y) return;
        if (weights[pX] >= weights[pY]) {
            weights[pX] += weights[pY];
            parents[pY] = pX;
        } else {
            weights[pY] += weights[pX];
            parents[pX] = pY;
        }
    }

    int howManyParents() {
        int cnt = 0;
        for (int i = 0; i < parents.size(); i ++) {
            if (parents[i] == i) cnt ++;
        }
        return cnt;
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    //vector<Edge> red;
    vector<Edge> blue;
    UnionFind ufRed(n);
    UnionFind ufBlue(n);

    for (int i = 0; i < m; i ++) {
        char color;
        int x, y;
        cin >> color >> x >> y;
        x --;
        y --;
        if (color == 'R') {
            if (ufRed.find(x) != ufRed.find(y)) {
                ufRed.join(x, y);
            } 
        } else {
            if (ufBlue.find(x) != ufBlue.find(y)) {
                ufBlue.join(x, y);
                blue.push_back({x, y});
            }
        }
    }

    int limit = blue.size();
    int edgesUsed = 0;
    for (Edge& e : blue) {
        if (ufRed.find(e.x) != ufRed.find(e.y)) {
            ufRed.join(e.x, e.y);
            edgesUsed ++;
        }
    }
    int neededLeft = k - edgesUsed;
    if (neededLeft < 0 || neededLeft > limit - edgesUsed) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
    }

    
}