#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;

//vector<vector<string>> begin;
vector<vector<string>> start;

string bestWord(string word) {
    vector<string>& next = start[word[word.size() - 1] - 'a'];
    if (next.empty()) {
        return "?";
    } else {
        for (string& s : next) {
            vector<string>& a = start[s[s.size() - 1] - 'a'];
            if (a.empty() || (a.size() == 1 && a[0] == s)) {
                return s + "!";
            } 
        }
        return next[0];
    }
}

int main() {
    start = vector(26, vector<string>());
    string word;
    cin >> word;
    int n;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        string s;
        cin >> s;
        start[s[0] - 'a'].push_back(s);
    }
    //cout << word + "!" << endl;
    string&& res = bestWord(word);
    cout << res;
}