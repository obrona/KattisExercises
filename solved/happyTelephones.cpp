#include <vector>
#include <iostream>
using namespace std;

// only linear scan is needed, segment tree is wrong, because we are splitting ranges up, will result in double counting

int helper(vector<vector<int>>& ranges, int s, int e) {
    int count = 0;
    for (int i = 0; i < ranges.size(); i ++) {
        if (e < ranges[i][0] || s > ranges[i][1]) {
            //nothing
        } else {
            count += 1;
        }
    }
    return count;
}

int main() {
    vector<int> out;
    
    while (true) {
        int n, m;
        cin >> n >> m;
        if (!(n == 0 && m == 0)) {
            vector<vector<int>> ranges;
            for (int i = 0; i < n; i ++) {
                int x, y, s, d;
                cin >> x >> y >> s >> d;
                ranges.push_back({s, s + d - 1});
            }
            for (int i = 0; i < m; i ++) {
                int start, dur;
                cin >> start >> dur;
                int ans = helper(ranges, start, start + dur - 1);
                out.push_back(ans);
            }
        } else {
            break;
        }

    }
    for (int x : out) {
        cout << x << '\n';
    }
}