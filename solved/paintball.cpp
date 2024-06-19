#include <vector>
#include <iostream>
using namespace std;

// model as finding maximum matching on a bipartite graph

vector<vector<int>> adjMatrix;
vector<int> shootWho;
int n;
int m;

void process(vector<vector<int>> canSee) {
    adjMatrix = vector(2 * n + 2, vector(2 * n + 2, 0));
    shootWho = vector(n + 1, -1);
    for (int i = 1; i <= n; i ++) {
        adjMatrix[0][i] = 1;
        adjMatrix[n + i][2 * n + 1] = 1;
    }
    for (int i = 0; i < canSee.size(); i ++) {
        vector<int>& pair = canSee[i];
        adjMatrix[pair[0]][n + pair[1]] = 1;
        adjMatrix[pair[1]][n + pair[0]] = 1;
    }
}

bool isValidPair(int x, int y) {
    return (1 <= x && x <= n && n + 1 <= y && y <= 2 * n);
}

bool undoPair(int x, int y) {
    return isValidPair(y, x);
}

bool dfs(int node, vector<bool>& visited, int goal) {
    if (visited[node]) {
        return false;
    } else if (node == goal) {
        return true;
    } else {
        visited[node] = true;
        for (int i = 0; i < adjMatrix[0].size(); i ++) {
            if (adjMatrix[node][i] == 1) {
                adjMatrix[node][i] = 0;
                adjMatrix[i][node] = 1;
                bool ans = dfs(i, visited, goal);
                if (!ans) {
                    adjMatrix[node][i] = 1;
                    adjMatrix[i][node] = 0;
                    
                } else {
                    return true;
                }
            }
        }
        return false;
    }
}

int fordFulkerson() {
    int maxPair = 0;
    while (1) {
        vector<bool> visited = vector(2 * n + 2, false);
        bool canExtend = dfs(0, visited, 2 * n + 1);
        if (canExtend) {
            maxPair ++;
        } else {
            break;
        }
    }
    return maxPair;
}

void printShoot() {
    for (int i = 1; i <= n; i ++) {
        for (int j = n + 1; j <= 2 * n; j ++) {
            if (adjMatrix[j][i] == 1) {
                cout << j - n << endl;
                break;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    vector<vector<int>> pairs;
    for (int i = 0; i < m; i ++) {
        int x, y;
        cin >> x >> y;
        pairs.push_back({x, y});
    }
    process(pairs);
    int numPairs = fordFulkerson();
    if (numPairs < n) {
        cout << "Impossible" << endl;
    } else {
        printShoot();
    }

}

