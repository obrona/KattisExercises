#include <vector>
#include <iostream>
using namespace std;
// basically, for each index, find the longest increasing and decreasing subsequence, starting from that index
// ans is longest increas + longest decreasing - 1

vector<int> dpDesc;
vector<int> dpAsc;

int helperAsc(int index, vector<int>& array) {
    if (index == array.size()) {
        return 0;
    } else if (dpAsc[index] != -1) {
        return dpAsc[index];
    } else {
        int maxRes = 1;
        for (int i = index + 1; i < array.size(); i ++) {
            if (array[i] >= array[index]) {
                maxRes = max(maxRes, 1 + helperAsc(i, array));
            }
        }
        dpAsc[index] = maxRes;
        return maxRes;
    }
}

int helperDesc(int index, vector<int>& array) {
    if (index == array.size()) {
        return 0;
    } else if (dpDesc[index] != -1) {
        return dpDesc[index];
    } else {
        int maxRes = 1;
        for (int i = index + 1; i < array.size(); i ++) {
            if (array[i] <= array[index]) {
                maxRes = max(maxRes, 1 + helperDesc(i, array));
            }
        }
        dpDesc[index] = maxRes;
        return maxRes;
    }
}

int main() {
    int n;
    cin >> n;
    dpAsc = vector(n, -1);
    dpDesc = vector(n, -1);
    vector<int> cars;
    for (int i = 0; i < n; i ++) {
        int c;
        cin >> c;
        cars.push_back(c);
    }
    int best = 0;
    for (int i = 0; i < n; i ++) {
        int res = helperAsc(i, cars) + helperDesc(i, cars) - 1;
        best = max(best, res);
    }
    cout << best;
}
