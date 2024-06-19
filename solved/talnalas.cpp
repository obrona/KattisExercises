#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
// simple bfs

char prevNum(char c) {
    return c == '0' ? '9' : (char) (c - 1);
}

char nextNum(char c) {
    return c == '9' ? '0' : (char) (c + 1);
}

vector<string> bfs(string start, string end, unordered_map<string, int>& nums) {
    queue<vector<string>> q;
    q.push({start, start});
    unordered_map<string, string> map;
    while (!q.empty()) {
        vector<string>& node = q.front();
        //cout << node[0] << endl;
        if (map.find(node[0]) == map.end()) {
            map[node[0]] = node[1];
            if (node[0] == end) break;
            string s = node[0];
            
            for (int i = 0; i < node[0].size(); i ++) {
                s[i] = prevNum(node[0][i]);
                if (nums.find(s) != nums.end()) {
                    q.push({s, node[0]});
                }
                s[i] = node[0][i];
                s[i] = nextNum(node[0][i]);
                if (nums.find(s) != nums.end()) {
                    q.push({s, node[0]});
                }
                s[i] = node[0][i];
            }
        }
        q.pop();
    }
    if (map.find(end) == map.end()) {
        return {};
    } else {
        vector<string> out;
        string s = end;
        while (s != map[s]) {
            out.push_back(s);
            s = map[s];
        }
        out.push_back(start);
        return out;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    string start, end;
    cin >> start >> end;
    unordered_map<string, int> nums;
    nums[start] = 1;
    nums[end] = 1;
    for (int i = 0; i < m; i ++) {
        string s;
        cin >> s;
        nums[s] = 1;
    }
    vector<string>&& res = bfs(start, end, nums);
    if (res.size() == 0) {
        cout << "Neibb" << endl;
    } else {
        cout << res.size() - 1 << endl;
        for (int i = res.size() - 1; i >= 0; i --) {
            cout << res[i] << endl;
        }
    }
}