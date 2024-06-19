#include <vector>
#include <iostream>
#include <bitset>
using namespace std;


int reverse(int bm, int limit) {
    int res = 0;
    for (int i = 0; i < limit; i ++) {
        res += (1 << (limit - 1 - i)) * ((bm >> i) & 1);
    }
    return res;
}

vector<int> helper(int s, int e, vector<int>& mapping) {
    if (s == e) {
        return {1, mapping[s]};
    } else {
        int mid = (s + e) / 2;
        vector<int>&& l = helper(s, mid, mapping);
        vector<int>&& r = helper(mid + 1, e, mapping);
        if (l[0] == 1 && r[0] == 1 && l[1] == r[1] && l[1] != -1) {
            // can only merge if subtree is of size 1, and the results of evaluation is equal
            return {1, l[1]};
        } else {
            // -1 means the tree needs to split because there are both 0 and 1
            return {l[0] + r[0] + 1, -1};
        }
    }
}

void print(vector<int> a) {
    for (int x : a) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    int limit;
    cin >> limit;
    vector<int> mapping((1 << limit), 0);
    for (int i = 0; i < (1 << limit); i ++) {
        int ans;
        cin >> ans;
        int rev = reverse(i, limit);
        mapping[rev] = ans;
    }
    //print(mapping);
    vector<int> res = helper(0, (1 << limit) - 1, mapping);
    cout << res[0];
}