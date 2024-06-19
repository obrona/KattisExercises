#include <vector>
#include <iostream>
using namespace std;

// suppose, for this node's parent, you know the least amount of water needed to breach the giant camp
// for this node, the amount of rain needed is simple right .... not trivial hehe
// dp store min amount of rain needed at this node, so that giant camp will be washed away

vector<int> parents;
vector<long long> dp;
vector<vector<long long>> info; // 0: curr water, 1: capacity or limit

long long helper(int node) {
    if (node == 0) {
        return info[0][1];
    } else if (dp[node] != -1) {
        return dp[node];
    } else {
        long long needed = helper(parents[node]);
        vector<long long> infoNode = info[node];
        if (needed <= infoNode[1]) {
            // parent needed min water is lesser that the dam limit, so only rain needed is the water required to push dam to limit
            dp[node] = infoNode[1] - infoNode[0];
            return dp[node];
        } else {
            // parent needed is much more tha dam limit, so need to add more rain
            dp[node] = needed - infoNode[0];
            return dp[node];
        }
    }
}

int main() {
    long long n, w;
    cin >> n >> w;
    parents = vector(n + 1, -1);
    dp = vector<long long>(n + 1, -1L);
    info.push_back({0L, w});
    for (int i = 1; i <= n; i ++) {
        long long p, l, c;
        cin >> p >> l >> c;
        parents[i] = p;
        info.push_back({c, l});
    }
    long long best = 2000000000;
    for (int i = 0; i <= n; i ++) {
        long long res = helper(i);
        best = min(best, res);
    }
    cout << best;
}
