#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;

vector<int> parent;
vector<int> weight;

int find(int x) {
    if (parent[x] == x) return x;
    else {
        int p = find(parent[x]);
        parent[x] = p;
        return p;
    }
}

void join(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) {
        return;
    }
    if (weight[px] < weight[py]) {
        weight[py] += weight[px];
        parent[px] = py;
    } else {
        weight[px] += weight[py];
        parent[py] = px;
    }
}

int main() {
     ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    parent = vector(n, 1);
    for (int i = 0; i < n; i ++) {
        parent[i] = i;
    }
    weight = vector(n, 1);
    for (int i = 0; i < q; i ++) {
        char type;
        int x, y;
        cin >> type >> x >> y;
        if (type == '?') {
           if (find(x) == find(y)) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        } else {
            join(x, y);
        }
    }
}
