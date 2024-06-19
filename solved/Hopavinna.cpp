#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> dp;

int helper(int index, int mustTake, vector<int>& nums) {
    if (index == nums.size()) {
        return 0;
    } else if (dp[index][mustTake] != -1) {
        return dp[index][mustTake];
    } else if (mustTake) {
        dp[index][mustTake] = nums[index] + helper(index + 1, 0, nums);
        return dp[index][mustTake];
    } else {
        int option1 = helper(index + 1, 1, nums);
        int option2 = nums[index] + helper(index + 1, 0, nums);
        dp[index][mustTake] = min(option1, option2);
        //cout << index << " " << option1 << " " << option2 << endl;
        return dp[index][mustTake];
    }
}

int main() {
    int n;
    cin >> n;
    dp = vector(n, vector(2, -1));
    vector<int> nums;
    for (int i = 0; i < n; i ++) {
        int a;
        cin >> a;
        nums.push_back(a);
    }
    cout << helper(0, 0, nums);
}