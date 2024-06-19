#include <iostream>
#include <vector>
#include "AVLnode.hpp"

using namespace std;

// solution is simply to find the LIS in the permuation sequence
// eg 4 2 6 3 1 5
// i.e 1 paired to 4, 2, paired to 2, 3 paired to 6 etc
// best solution is 2 3 5



int main() {
    int n;
    cin >> n;
    vector<int> store;
    for (int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        store.push_back(x);
    }
    AVLnode* root = nullptr;
    int best = 0;
    for (int i = n - 1; i >= 0; i --) {
        int res = 1 + (int) AVLnode::getMaxPairForKeysGeq(root, (long long) store[i]);
        best = max(best, res);
        root = AVLnode::insert(root, store[i], res);
    }
    cout << best << endl;


}

