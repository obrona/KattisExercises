#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

//vector<int> store;
//unordered_map<int, int>;

int doOp(int a, int b, string op) {
    if (op == "+") {
        return a + b;
    } else if (op == "-") {
        return a - b;
    } else if (op == "*") {
        return a * b;
    } else {
        return a / b;
    }
}

string printRes(vector<string>& store, int res) {
    string s = "";
    for (int i = 0; i < store.size(); i ++) {
        s += store[i];
        s += " ";
    }
    s += "=";
    s += " ";
    s += to_string(res);
    //cout << s << endl;
    return s;
}

void printV(vector<string>& s) {
    for (int i = 0; i < s.size(); i ++) {
        cout << s[i] << " ";
    }
    cout << endl;
}

int eval(vector<string>& store) {
    vector<string> temp = vector<string>();
    temp.push_back(store[0]);
    temp.push_back(store[1]);
    for (int i = 2; i < store.size(); i += 2) {
        temp.push_back(store[i]);
        if (temp.size() != 1 && (temp[temp.size() - 2] == "*" || temp[temp.size() - 2] == "/")) {
            //cout << i << endl;
            int b = stoi(temp.back());
            temp.pop_back();
            string op = temp.back();
            temp.pop_back();
            int a = stoi(temp.back());
            temp.pop_back();
            int res = doOp(a, b, op);
            temp.push_back(to_string(res));
        }
        if (i + 1 < store.size()) {
            temp.push_back(store[i + 1]);
        }
    }
    //printV(temp);
    int ans = stoi(temp[0]);
    for (int i = 1; i < temp.size(); i +=2) {
        string op = temp[i];
        int b = stoi(temp[i + 1]);
        ans = doOp(ans, b, op);
    }
    
    return ans;
}

bool helper(int left, vector<string>& store, int target, vector<string>& operators, vector<string>& output) {
    if (left == 1) {
        store.push_back("4");
        int res = eval(store);
        if (res == target) {
            output.push_back(printRes(store, res));
            return true;
        } else {
            store.pop_back();
            return false;
        }
    } else {
        store.push_back("4");
        for (int i = 0; i < 4; i ++) {
            store.push_back(operators[i]);
            bool ans = helper(left - 1, store, target, operators, output);
            if (ans) {
                return true;
            } else {
                store.pop_back();
            }
        }
        store.pop_back();
        return false;
    }
}

int main() {
  vector<string> ops = {"+", "-", "*", "/"};
  int m;
  cin >> m;
  vector<string> output = vector<string>();
  for (int i = 0; i < m; i ++) {
    vector<string> s = vector<string>();
    int target;
    cin >> target;
    bool ans = helper(4, s, target, ops, output);
    if (!ans) {
        output.push_back("no solution");
    }
  }
  for (int i = 0; i < output.size(); i ++) {
    cout << output[i] << '\n';
  }
}

/*int main() {
    vector<string> s = {"4", "+", "4", "-", "4", "/", "4"};
    cout << eval(s);
}*/

