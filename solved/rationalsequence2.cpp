#include <iostream>
#include <vector>
using namespace std;

int findN(long long p, long long q) {
    if (p == 1 && q == 1) {
        return 1;
    } else if (p < q) {
        // parent is a / b, then left child = a / (a + b)
        // b = (a + b) - a
        return 2 * findN(p, q - p);
    } else {
        // parent is a / b, right child is (a + b) / b
        // a = (a + b) - b
        return 2 * findN(p - q, q) + 1;
    }
}

vector<string> splitter(string s) {
    int delimIndex = 0;
    for (int i = 0; i < s.size(); i ++) {
        if (s[i] == '/') {
            delimIndex = i;
            break;
        }
    }
    string num = s.substr(0, delimIndex);
    string denom = s.substr(delimIndex + 1, s.size() - delimIndex - 1);
    return vector<string>({num, denom});
}

int main() {
    int inputSize;
    cin >> inputSize;
    vector<vector<string>> store = vector<vector<string>>();
    for (int i = 0; i < inputSize; i ++) {
        int index;
        cin >> index;
        string fraction;
        cin >> fraction;
        store.push_back(splitter(fraction));
    }
    for (int i = 0; i < store.size(); i ++) {
        vector<string>& frac = store[i];
        long long a = stoll(frac[0]);
        long long b = stoll(frac[1]);
        int ans = findN(a, b);
        cout << i + 1 << " " << ans << '\n';
    }
    //cout << "hello" << endl;
    return 0;
}