// basically, when we are deciding the ith string which starts at k we check the previous settled string
// we only need to care, among the previously settled string, the rightmost ending string, whether it is reversed or not. Call this string the dominating string
// because only that string will determine if reversing or not reversing this string will 'fit'
// if there is not previous string with right end >= k, then we can a free option

// so for each string, we find, among the previous strings, the 'dominating' string. If dont have, any previous string can be the dominating string.
// dp is (dir of dominating string, index of string) eg (0, 5) or (1, 5)


#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Pair {
    int start;
    string str;
};

vector<Pair> strings;
vector<int> dominater;
vector<vector<int>> dp;
vector<vector<int>> whatDir;

vector<int> stack;




void findDominating() {
    dominater.push_back(-1);
    int rightMost = strings[0].start + strings[0].str.size() - 1;
    int index = 0;
    for (int i = 1; i < strings.size(); i ++) {
        dominater.push_back(index);
        int rightEnd = strings[i].start + strings[i].str.size() - 1;
        if (rightEnd > rightMost) {
            index = i;
            rightMost = rightEnd;
        }
    }
}

// 0 means not reversed, 1 means reversed
bool possibleToConcat(int index, int dir, int domI, int domDir) {
    if (strings[domI].str.size() + strings[domI].start - 1 < strings[index].start) return true;
    string s = strings[index].str;
    string domS = strings[domI].str;
    int sStart = strings[index].start;
    int domStart = strings[domI].start;
    if (dir) reverse(s.begin(), s.end());
    if (domDir) reverse(domS.begin(), domS.end());
    
    for (int i = 0; i < min(s.size(), domS.size() - (sStart - domStart)); i ++) {
        if (s[i] != domS[i + (sStart - domStart)]) {
            return false;
        }
    }
    return true;
}

bool canMakeString(int index) {
    if (index == strings.size()) {
        return true;
    } else if (index == 0) {
        stack.push_back(0);
        bool res1 = canMakeString(index + 1);
        if (res1) return true;
        
        stack.pop_back();
        stack.push_back(1);
        bool res2 = canMakeString(index + 1);
        if (res2) return true;
        
        stack.pop_back();
        return false;
    } else {
        int domI = dominater[index];
        if (dp[stack[domI]][index] != -1) {
            if (dp[stack[domI]][index]) {
                stack.push_back(whatDir[stack[domI]][index]);
                return canMakeString(index + 1);
            } else {
                return false;
            }
        } else {
            if (possibleToConcat(index, 0, domI, stack[domI])) {
                stack.push_back(0);
                bool res1 = canMakeString(index + 1);
                if (res1) {
                    dp[stack[domI]][index] = 1;
                    whatDir[stack[domI]][index] = 0;
                    return true;
                } 
                stack.pop_back();
            }

            if (possibleToConcat(index, 1, domI, stack[domI])) {
                stack.push_back(1);
                bool res2 = canMakeString(index + 1);
                if (res2) {
                    dp[stack[domI]][index] = 1;
                    whatDir[stack[domI]][index] = 1;
                    return true;
                }
                stack.pop_back();
            }
            dp[stack[domI]][index] = 0;
            return false;
        }

    }
}

string reconStruct(vector<int>& stack, int len) {
    string out = "";
    int end = 0;
    for (int i = 0; i < stack.size(); i ++) {
        if (stack[i] == 1) reverse(strings[i].str.begin(), strings[i].str.end());
        while (end < strings[i].start) {
            out.push_back('A');
            end ++;
        }
        while (end < strings[i].start + strings[i].str.size()) {
            out.push_back(strings[i].str[end - strings[i].start]);
            end ++;
        }
    }
    while (end < len) {
        out.push_back('A');
        end ++;
    }
    return out;
   
}


void print(vector<int>& s) {
    for (int i : s) {
        cout << i << " ";
    }
    cout << endl;
}
int main() {
    int N, M;
    cin >> N >> M;
    dp = vector(2, vector(M, -1));
    whatDir = vector(2, vector(M, -1));
    for (int i = 0; i < M; i ++) {
        int start;
        string str;
        cin >> start >> str;
        strings.push_back({start - 1, str});
    }
    sort(strings.begin(), strings.end(), [](Pair& a, Pair& b) -> bool {return a.start < b.start;});
    findDominating();
    bool ans = canMakeString(0);
    if (ans) {
        //print(stack);
        cout << reconStruct(stack, N);
    } else {
        cout << "Villa";
    }

}

