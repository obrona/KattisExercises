#include <vector>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

// basically, starting from 0th index, greedily take A, B, C, in any order, until they form ABC
// eg ABACBCAACCBB, take 0, 1, 3 index
// if there is some subseqeucne with endpoint lesser than the start point of the newly form, ABC subseqeunce, no need to increase num 
// of sequence
// else need to increase the number of sequence

// to proof greedy works, need to use swapping arguement, quite difficult
// consider         A          B             C ...
//                       B             B       ...
// A is the very 1st character
// in the 1st line we do not take the 1st available B
// case 1 : ABC of 1st B in 2nd line ends after B of 1st line, or ABC of 2nd B in 2nd line starts after 1st line B, 
// simpl swap the 1st line B with 2nd line B

/*
case2 :  A            B             C
            C A  B  A    B     C
now we simply cant sway 2nd line 1st B and 1st line B,
but we take 1st B, C from 2nd line, put 2nd A of 2nd line to 1st line to get
        A   C    B  A B             C
              A          B     C
see that we can do some modification such that we take the 1st available B
case3 :  A            B             CB ...
            C A  B  C   B              A
now we cannot move 2nd line 2nd A to the 1st line, or other words, do something similar to case2
but notice 2nd line 2nd C is before 1st line C
swap to get
        A           C B              B...
            C A  B      B           C  A
now that the 2nd line 2nd B begins after 1st line B falls back to case1.
either way we can make thius arguement to see why we can greedily take the earliest available A B C subsequence and recurse
*/

auto cmp = [] (int a, int b) -> bool {return a > b;};
typedef priority_queue<int, vector<int>, decltype(cmp)> pqInt;

int* helper(pqInt& A, pqInt& B, pqInt& C) {
    if (A.empty()) {
        return nullptr;
    } else {
        int a = A.top();
        int b = B.top();
        int c = C.top();
        //used[a] = 1;
        //used[b] = 1;
        //used[c] = 1;
        int* out = new int[2];
        out[0] = min(a, min(b, c));
        out[1] = max(a, max(b, c));
        A.pop();
        B.pop();
        C.pop();
        return out;
    }
}

void process(string& s, pqInt& A, pqInt& B, pqInt& C) {
    for (int i = 0; i < s.size(); i ++) {
        if (s[i] == 'A') {
            A.push(i);
        } else if (s[i] == 'B') {
            B.push(i);
        } else {
            C.push(i);
        }
    }
}

int numSequences(string& s) {
    //vector<int> used = vector(s.size(), 0);
    pqInt A(cmp);
    pqInt B(cmp);
    pqInt C(cmp);
    process(s, A, B, C);
    pqInt endpoint(cmp);
    int cnt = 0;
    while (true) {
        // no need to track used, the min from the 3 priority queues automatically 
        // give the next element to be paired in ABC
        int* res = helper(A, B, C);
        if (res == nullptr) break;
        else {
            if (endpoint.empty()) {
                cnt += 1;
                endpoint.push(res[1]);
            } else if (endpoint.top() <= res[0]) {
                endpoint.pop();
                endpoint.push(res[1]);
            } else {
                cnt += 1;
                endpoint.push(res[1]);
            }
        }
            
        
    }
    return cnt;

}

int main() {
    string s;
    cin >> s;
    cout << numSequences(s);
}