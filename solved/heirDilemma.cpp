#include <vector>
#include <iostream>
using namespace std;

vector<int> stack;
vector<int> store;

void print() {
    int sum = 0;
    for (int i = 0; i < 6; i ++) {
        sum *= 10;
        sum += stack[i];
    }
    store.push_back(sum);
}

void helper(int left, int used) {
    if (left == 0) {
        print();
    } else {
        for (int i = 1; i <= 9; i ++) {
            if (((used >> i) & 1) == 0) {
                stack.push_back(i);
                helper(left - 1, used + (1 << i));
                stack.pop_back();
            }
        }
    }
}

bool checkDivisible(int x) {
    string s = to_string(x);
    for (int i = 0; i < 6; i ++) {
        int digit = s[i] - '0';
        if (x % digit != 0) {
            return false;
        }
    }
    return true;
}
int countValid(int low, int high) {
    int c = 0;
    for (int x : store) {
        if (low <= x && x <= high && checkDivisible(x)) {
           c ++;
        }
    }
    return c;
}

int main() {
    helper(6, 0);
    int l, h;
    cin >> l >> h;
    cout << countValid(l, h);
}