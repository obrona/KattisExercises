#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> dp;
vector<int> note = {100, 200, 500};
vector<int> exact;

int helper(int fare) {
    if (fare < 0) {
        return 9999;
    } else if (fare == 0) {
        return 0;
    } else if (dp[fare] != -1) {
        return dp[fare];
    } else {
        int smallest = 999999;
        for (int i = 0; i < 3; i ++) {
            int res = 1 + helper(fare - note[i]);
            smallest = min(smallest, res);
        }
        dp[fare] = smallest;
        if (smallest < 9999) {
            exact.push_back(fare);
        }
        return smallest;
    }
}

int bSearch(int fare) {
    int s = 0;
    int e = exact.size() - 1;
    while (s < e) {
        int m = (e + s) / 2;
        if (exact[m] < fare) {
            s = m + 1;
        } else {
            e = m;
        }
    }
    return exact[s];
}

int main() {
    dp = vector(15001, -1);
    for (int i = 1; i <= 15001; i ++) {
        helper(i);
    }
    sort(exact.begin(), exact.end());
    int f;
    cin >> f;
    int closest = bSearch(f);
    int ans = dp[closest];
    cout << ans;
}