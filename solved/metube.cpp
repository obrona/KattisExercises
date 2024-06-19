#include <vector>
#include <iostream>
#include <bitset>
#include <string>
using namespace std;

// state(index, bitmask not taken) : minimum time to watch all remaining categories with videos from index all the way to the end;
// 0 if not taken , 1 if taken
// TC = O(#videos * 2 ^ categories)

vector<vector<int>> dp;
int bm;

int helper(int index, int covered, vector<string>& catergories, vector<int>& time) {
    if (index == catergories.size()) {
        return covered == bm ? 0 : 999999999;
    } else if (dp[index][covered] != -1) {
        return dp[index][covered];
    } else {
        int noUse = helper(index + 1, covered, catergories, time);
        string& cats = catergories[index];
        int newCovered = covered;
        for (int i = 0; i < cats.size(); i ++) {
            newCovered = newCovered | (1 << (cats[i] - 'a'));
        }
        int use = time[index] + helper(index + 1, newCovered, catergories, time);
        dp[index][covered] = min(use, noUse);
        return dp[index][covered];
    }
}

int getCategories(vector<string>& s) {
    int bm = 0;
    for (int i = 0; i < s.size(); i ++) {
        string& cats = s[i];
        for (int j = 0; j < cats.size(); j ++) {
            bm = bm | (1 << (cats[j] - 'a'));
        }
    }
    return bm;
}

int main() {
    int N;
    cin >> N;
    vector<int> time;
    vector<string> cats;
    dp = vector(N, vector((1 << 10), -1));
    for (int i = 0; i < N; i ++) {
        int t;
        string s;
        cin >> t >> s;
        time.push_back(t);
        cats.push_back(s);
    }
    bm = getCategories(cats);
    int ans = helper(0, 0, cats, time);
    cout << ans;
}

/*int main() {
    vector<string> cats = {"a", "bc", "abj"};
    cout << bitset<10>(getCategories(cats));
}*/