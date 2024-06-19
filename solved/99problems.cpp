#include <iostream>
#include <string>
using namespace std;

int lower99(string& n) {
    string temp = n;
    if (n[n.size() - 3] == '0') {
        string s = n.substr(n.size() - 2, 2);
        int sub = stoi(s) + 100;
        int x = stoi(n);
        return x - sub + 99;
        
    } else {
        temp[temp.size() - 3] = (char) (n[n.size() - 3] - 1);
        temp[temp.size() - 2] = '9';
        temp[temp.size() - 1] = '9';
        return stoi(temp);
    }
}

int higher99(string& n) {
    
        string temp = n;
        temp[temp.size() - 3] = (char) (n[n.size() - 3]);
        temp[temp.size() - 2] = '9';
        temp[temp.size() - 1] = '9';
        return stoi(temp);
    
}

int closest99(string& n) {
    if (n.size() <= 2) {
        return 99;
    } else {
        int l = lower99(n);
        int h = higher99(n);
        //cout << l << " " << h << '\n';
        if (stoi(n) - l < h - stoi(n)) {
            return l;
        } else {
            return h;
        }
    }
}

int main() {
   string n;
   cin >> n;
   cout << closest99(n) << '\n';
}