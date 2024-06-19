#include <vector>
#include <iostream>
using namespace std;

// generate all possible subsets, for each farmer, check if there is a bean a farmer can give that is not in the subset
// i.e farmer 1, subset 0, use bit operations for O(1) checks
// for a subset, if every farmer has a seed not in this subset, he can choose to give that seed all the time, meaning jack will never a get a seed in that subset
// choose the most expensive subset among all subset that satisfy the above property

bool possible(vector<int>& farmers, int subset) {
    for (int i = 0; i < farmers.size(); i ++) {
        int f = farmers[i];
        if ((f & ~subset) == 0) return false; // there is no seed a farmer has that is not in subset
    }
    return true;
}

int cowsNeeded(int subset, vector<int>& seeds, int n) {
    int sum = 0;
    for (int i = 0; i < n; i ++) {
        int x = (subset >> i) & 1;
        sum += seeds[i] * x;
    }
    return sum;
}

int findMax(vector<int>& farmers, vector<int>& seeds, int n) {
    int maxCows = 0;
    for (int i = 0; i < (1 << n); i ++) {
        if (possible(farmers, i)) {
            maxCows = max(maxCows, cowsNeeded(i, seeds, n));
        }
    }
    return maxCows;
}

void print(vector<int> a) {
    for (int x : a) {
        std::cout << x << " ";
    }
    std::cout << endl;
}

int main() {
    int n;
    cin >> n;
    vector<int> seeds;
    for (int i = 0; i < n; i ++) {
        int s;
        cin >> s;
        seeds.push_back(s);
    }
    //print(seeds);
    int f;
    cin >> f;
    vector<int> farmers;
    for (int i = 0; i < f; i ++) {
        int num;
        cin >> num;
        int v = 0;
        for (int j = 0; j < num; j ++) {
            int type;
            cin >> type;
            v += (1 << (type - 1));
        }
        farmers.push_back(v);
    }
    //print(farmers);
    int ans = findMax(farmers, seeds, n);
    std::cout << ans;
}