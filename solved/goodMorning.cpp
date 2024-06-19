#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

vector<vector<int>> board = {{1,2,3},{4,5,6},{7,8,9},{-1,0,-1}};

// returns the closest integer you can get
int closest(int r, int c, int target, int curr) {
    if (curr > 2000) {
        return 999999999;
    } else if (r == 4) {
        return curr;
    } else if (c == 3) {
        return closest(r + 1, c, target, curr);
    } else {
        // take curr number
        int take;
        if (board[r][c] == -1) {
            take = 999999999;
        } else {
            int newCurr = curr * 10 + board[r][c];
            int option1 = closest(r + 1, c, target, newCurr);
            int option2 = closest(r, c + 1, target, newCurr);
            int option3 = (curr == 0 && board[r][c] == 0) ? 999999999 : closest(r, c, target, newCurr);
            int res1 = abs(target - option1);
            int res2 = abs(target - option2);
            int res3 = abs(target - option3);
            if (res1 <= res2 && res1 <= res3) {
                take = option1;
            } else if (res2 <= res1 && res2 <= res3) {
                take = option2;
            } else {
                take = option3;
            }
        }
        
        int noTake;
        int option1 = closest(r + 1, c, target, curr);
        int option2 = closest(r, c + 1, target, curr);
        if (abs(target - option1) < abs(target - option2)) {
            noTake = option1;
        } else {
            noTake = option2; 
        }
        
        if (abs(target - take) < abs(target - noTake)) {
            return take;
        } else {
            return noTake;
        }
    }
}

int main() {
    int k;
    cin >> k;
    for (int i = 0; i < k; i ++) {
        int m;
        cin >> m;
        cout << closest(0, 0, m, 0) << '\n';
    }
}