#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

vector<vector<vector<int>>> dp;
vector<int> calorielvl;
int maxlvl;

int maxLevel(int calorie) {
    return (int) ceil(log(calorie) / log(1.5));
}

int getCalorie(int calorie, int lvl) {
    return calorielvl[lvl];
}

int calculateCalorie(int m) {
    while (m != 0) {
        calorielvl.push_back(m);
        m = (int) floor(m * 2.0 / 3.0);
    }
    return calorielvl.size();
}

void print(vector<int> a) {
    for (int x : a) {
        cout << x << " ";
    }
    cout << endl;
}

int helper(int index, int level, int atePrev, vector<int>& foods, int calorie) {
    if (index == foods.size()) {
        return 0;
    } else if (dp[level][atePrev][index] != -1) {
        return dp[level][atePrev][index];
    } else if (level == maxlvl) {
        // calorie allowed is 0, cannot eat anything
        if (atePrev == 0) {
            dp[level][atePrev][index] = helper(index + 1, 0, 0, foods, calorie);
        } else {
            dp[level][atePrev][index] = helper(index + 1, level - 1, 0, foods, calorie);
        }
        return dp[level][atePrev][index];
    } else if (atePrev == 0) {
        int a1 = min(getCalorie(calorie, level), foods[index]) + helper(index + 1, level + 1, 1, foods, calorie);
        int a2 = helper(index + 1, 0, 0, foods, calorie);
        dp[level][atePrev][index] = max(a1, a2);
        return max(a1, a2);
    } else {
        int a1 = min(getCalorie(calorie, level), foods[index]) + helper(index + 1, level + 1, 1, foods, calorie);
        int a2 = helper(index + 1, level - 1, 0, foods, calorie);
        dp[level][atePrev][index] = max(a1, a2);
        return max(a1, a2);
    }
}

int main() {
    calorielvl = vector<int>();
    int n, m;
    cin >> n >> m;
    maxlvl = calculateCalorie(m);
    //print(calorielvl);
    dp = vector(m + 1, vector(2, vector(n, -1)));
    vector<int> foods;
    for (int i = 0; i < n; i ++) {
        int f;
        cin >> f;
        foods.push_back(f);
    }
    //cout << getCalorie(m, 3) << endl;
    //cout << maxlvl << endl;
    cout << helper(0, 0, 0, foods, m);
    
    
}