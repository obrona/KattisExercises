#include <vector>
#include <iostream>
#include <deque>
#include <unordered_map>
#include <algorithm>
using namespace std;

deque<int> eulerianPath (vector<vector<int>>& adjList, int oddDeg) {
    deque<int> store1;
    deque<int> store2;
    store1.push_back(oddDeg);
    while (!store1.empty()) {
        int node = store1.back();
        vector<int>& nbrsLeft = adjList[node];
        if (nbrsLeft.empty()) {
            store2.push_front(node);
            store1.pop_back();
        } else {
            int next = nbrsLeft.back();
            nbrsLeft.pop_back();
            store1.push_back(next);
        }
    }
    return store2;
}

int checkValid(vector<int>& inDeg, vector<int>& outDeg) {
    // 2 cases : all nodes have in_deg == out_deg
    // or 1 node with outdeg = indeg + 1, 1 node with indeg = outdeg + 1, rest all indeg = outdeg
    // return 0 if 1st case, start node if 2nd case, -1 if not valid
    int s;
    int scnt = 0;
    int e;
    int ecnt = 0;
    for (int i = 0; i < inDeg.size(); i ++) {
        if (abs(inDeg[i] - outDeg[i]) > 1) {
            return -1;
        } else if (inDeg[i] == outDeg[i] - 1) {
            s = i;
            scnt ++;
        } else if (inDeg[i] == outDeg[i] + 1) {
            e = i;
            ecnt ++;
        } 
    }
    if (scnt == 0 && ecnt == 0) {
        return 0;
    } else if (scnt == 1 & ecnt == 1) {
        return s;
    } else {
        return -1;
    }

}

int findStart(vector<int>& inDeg, vector<int>& outDeg) {
    int s = -1;
    for (int i = 0; i < inDeg.size(); i ++) {
        if (inDeg[i] == outDeg[i]) {
            // continue
        } else if (inDeg[i] == outDeg[i] - 1) {
            if (s == -1) {
                s = i;
            } else {
                return -1;
            }
        } else {
            // abs(indeg - outdeg) > 1
            return -1;
        }
    }
    return -2;
}

// return -1 if > 1 endpoint, i if 1 endpoint, -2 if no particular endpoint
int findEnd(vector<int>& inDeg, vector<int>& outDeg) {
    int e = -1;
    for (int i = 0; i < inDeg.size(); i ++) {
        if (inDeg[i] == outDeg[i]) {
            // continue
        } else if (inDeg[i] == outDeg[i] + 1) {
            if (e == -1) {
                e = i;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }
    return -2;
}

template <typename T>
void print(deque<T> d) {
    for (int i = 0; i < d.size(); i ++) {
        cout << d[i] << " ";
    }
    cout << endl;
}

template <typename T>
void print(vector<T> d) {
    for (int i = 0; i < d.size(); i ++) {
        cout << d[i] << " ";
    }
    cout << endl;
}



int main() {
    while (1) {
        int n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        } else {
            vector<vector<int>> adjList = vector(n, vector<int>());
            vector<int> inDegree = vector(n, 0);
            vector<int> outDegree = vector(n, 0);
            for (int i = 0; i < m; i ++) {
                int x, y;
                cin >> x >> y;
                adjList[x].push_back(y);
                outDegree[x] ++;
                inDegree[y] ++;
            }
           
            int s = checkValid(inDegree, outDegree);
            if (s != -1) {
                deque<int>&& res = eulerianPath(adjList, s);
                if (res.size() - 1 != m) {
                    cout << "Impossible" << endl;
                } else {
                    print(res);
                }
            } else {
                cout << "Impossible" << endl;
            }
            
        }
    }
}