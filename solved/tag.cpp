#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    unordered_map<string, int> store;
    unordered_map<string, int> cheat;
    vector<string> cheater;
    int N, M;
    cin >> N >> M;
    string hunter;
    cin >> hunter;
    store[hunter] = 1;

    string temp;
    for (int i = 1; i < N; i ++) cin >> temp;

    for (int i = 0; i < M; i ++) {
        string x, y;
        cin >> x;
        cin >> y;
        cin >> y;
        if (store[x] == 0 && cheat[x] == 0) {
            cheater.push_back(x);
            cheat[x] = 1;
        }
        store[x] = 0;
        store[y] = 1;
    }
    sort(cheater.begin(), cheater.end());
    cout << cheater.size() << endl;
    for (string& c : cheater) {
        cout << c << " ";
    }

}