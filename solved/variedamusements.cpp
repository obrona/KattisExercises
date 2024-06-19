#include <vector>
#include <iostream>
using namespace std;

vector<vector<long long>> dp;
long long MOD = 1000000007;
long long A, B, C;

long long helper(int toUse, int n) {
    if (n == 0) {
        return 1;
    } else if (dp[toUse][n] != -1) {
        return dp[toUse][n];
    } else if (toUse == 0) {
        long long bUse = A * helper(1, n - 1);
        long long cUse = (n == 1) ? 0 : A * helper(2, n - 1);
        long long ans = (bUse + cUse) % MOD;
        dp[toUse][n] = ans;
        return ans;
    } else if (toUse == 1) {
        long long aUse = B * helper(0, n - 1);
        long long cUse = (n == 1) ? 0 : B * helper(2, n - 1);
        long long ans = (aUse + cUse) % MOD;
        dp[toUse][n] = ans;
        return ans;
    } else {
        long long aUse = C * helper(0, n - 1);
        long long bUse = (n == 1) ? 0 : C * helper(1, n - 1);
        long long ans = (aUse + bUse) % MOD;
        dp[toUse][n] = ans;
        return ans;
    }
}

int rides(int n, int a, int b, int c) {
    dp = vector(3, vector(n + 1, -1LL));
    A = a;
    B = b;
    C = c;
    long long aa = helper(0, n);
    long long bb = helper(1, n);
    long long cc = helper(2, n);
    //cout << aa << " " << bb << " " << cc << endl;
    return (aa + bb + cc) % MOD;
}

int main() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    cout << rides(n, a, b, c);
}