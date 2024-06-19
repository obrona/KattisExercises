#include <vector>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

// remember -1 < s.size() is false, this is because size return unsigned type, -1 will be converted to unsigned type
string s; // the string you input eg *a*a.c
vector<string> store;

int canMatch(string& s2, int i, int j, vector<vector<int>>& dp) {
    
    if (j == s2.size()) {
        if (i == s.size()) {
            return 1;
        } else if (i == s.size() - 1 && s[i] == '*') {
            return 1;
        } else {
            return 0;
        }
    } else if (i == s.size()) {
        return (j == s2.size()) ? 1 : 0;
    } else if (dp[i][j] != -1) {
        return dp[i][j];
    } else if (s[i] == '*') {
        
        int ans = 0;
        for (int k = j - 1; k < (int) s2.size(); k ++) {
           
            int res = canMatch(s2, i + 1, k + 1, dp);
           
            ans = ans || res;
        }
        dp[i][j] = ans;
        //if (i == 0 && j == 0) cout << ans << endl;
        return ans;
    } else {
        if (s[i] == s2[j]) {
            int ans = canMatch(s2, i + 1, j + 1, dp);
            dp[i][j] = ans;
            return ans;
        } else {
            dp[i][j] = 0;
            return 0;
        }
    }
}

int main() {
    cin >> s;
    int N;
    cin >> N;
    for (int i = 0; i < N; i ++) {
        string s2;
        cin >> s2;
        //cout << s2 << endl;
        //printf("%s\n", s2.c_str());
        store.push_back(s2);
    }
    
    for (string s2 : store) {
        vector<vector<int>> dp = vector(s.size(), vector(s2.size(), -1));
        
        int ans = canMatch(s2, 0, 0, dp);
       
        if (ans == 1) {
            cout << s2 << endl;
        }
    }
}