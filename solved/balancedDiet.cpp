#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// have to use meet in the middle complete search
// split into 2 arrays, generate all possibilities, then for each sum, in 1st array, find highest num in 2nd array s.t sum + num <= (sum of calories) / 2

void generate(int index, vector<int>& food, vector<int>& store, int currSum) {
    if (index == food.size()) {
        store.push_back(currSum);
    } else {
        generate(index + 1, food, store, currSum);
        generate(index + 1, food, store, currSum + food[index]);
    }
}

void print(vector<int> a) {
    for (int x : a) {
        cout << x << " ";
    }
    cout << endl;
}

int sum(vector<int>& food) {
    int s = 0;
    for (int f : food) {
        s += f;
    }
    return s;
}

vector<vector<int>> split(vector<int>& a) {
    vector<int> a1;
    vector<int> a2;
    for (int i = 0; i < a.size() / 2; i ++) {
        a1.push_back(a[i]);
    }
    for (int i = a.size() / 2; i < a.size(); i ++) {
        a2.push_back(a[i]);
    }
    return {a1, a2};
}

int binarySearch(vector<int>& a, int key) {
    int s = 0;
    int e = a.size() - 1;
    while (e - s >= 1) {
        int m = (s + e) / 2 + (s + e) % 2;
        int mid = a[m];
        if (mid <= key) {
            s = m;
        } else {
            e = m - 1;
        }
    }
    return a[s];
}

void printRes(vector<int>& res1, vector<int>& res2, int sum) {
    sort(res1.begin(), res1.end());
    sort(res2.begin(), res2.end());
    int best = 0;
    for (int i = 0; i < res1.size(); i ++) {
        int curr = res1[i];
        int pair = binarySearch(res2, sum / 2 - curr);
        if (curr + pair > best && curr + pair <= sum / 2) {
            best = curr + pair;
        }
    }
    cout << sum - best << " " << best << endl;;
}
int main() {
    while (true) {
        vector<int> food;
        int n;
        cin >> n;
        if (n == 0) {
            break;
        }
        for (int i = 0; i < n; i ++) {
            int f;
            cin >> f;
            food.push_back(f);
        }
        vector<int> s1;
        vector<int> s2;
        vector<vector<int>>&& as = split(food);
        generate(0, as[0], s1, 0);
        generate(0, as[1], s2, 0);
        printRes(s1, s2, sum(food));
    }


}
