#include <vector>
#include <iostream>
using namespace std;

// since distance is limited, we need to prune the tree;
// almost same as finding vertex cover of a tree
// state (option to put, node), 0 if have option to put lamp otherwise 1
// start and end at root, so distance travelled must be even

vector<int> lamps;
vector<vector<int*>> adjList;
vector<vector<int>> dp;


int helper(int option, int node, int parent, int dist) {
    // always traverse the edge until dist - 2 * sum of path to this node is <= 0, this means this is the furtherst node
    if (dp[option][node] != -1) {
        return dp[option][node];
    } else if (dist <= 0) {
        if (option == 0) {
            dp[option][node] = 0;
            return 0;
        } else {
            dp[option][node] = (lamps[node]) ? 0 : 1;
            return dp[option][node];
        }
    } else if (option == 1) {
        int place = (lamps[node] == 1) ? 0 : 1;
        vector<int*>& childs = adjList[node];
        for (int* c : childs) {
            if (c[0] != parent) {
                int temp = helper(0, c[0], node, dist - 2 * c[1]);
                place += temp;
            }
        }
        dp[option][node] = place;
        return place;
    } else {
        int putLamp = (lamps[node] == 1) ? 0 : 1;
        vector<int*>& childs = adjList[node];
        for (int* c : childs) {
            if (c[0] != parent) {
                int temp = helper(0, c[0], node, dist - 2 * c[1]);
                putLamp += temp;
            }
        }

        int noLamp = (lamps[node] == 1) ? 999999999 : 0;
        if (lamps[node] == 0) {
            vector<int*>& childs = adjList[node];
            for (int* c : childs) {
                if (c[0] != parent) {
                    int temp = helper(1, c[0], node, dist - 2 * c[1]);
                    noLamp += temp;
                }
            }
        }
        dp[option][node] = min(putLamp, noLamp);
        return dp[option][node];



    }
}

int main() {
    int N, S;
    cin >> N >> S;
    lamps = vector(N + 1, 0);
    dp = vector(2, vector(N + 1, -1));
    adjList = vector(N + 1, vector<int*>());
    for (int i = 0; i < N - 1; i ++) {
        int a, b, s;
        cin >> a >> b >> s;
        int* xx = new int[2] {b, s};
        int* yy = new int[2] {a, s};
        adjList[a].push_back(xx);
        adjList[b].push_back(yy);
    }
    int L;
    cin >> L;
    for (int i = 0; i < L; i ++) {
        int lamp;
        cin >> lamp;
        lamps[lamp] = 1;
    }
    int ans = helper(0, 1, 1, S);
    cout << ans;
}
