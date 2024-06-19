#include <vector>
#include <iostream>
#include <queue>
#include <stdio.h>

using namespace std;


// the correct solution is to start from the back.
// among all vertices with no outdegrees, take the vertex with the smallest weight
// suppose we dont and we get the optimal solution  let vertex with smallest weight be vi, and vertex we chosen to be vj
// meet1, meet2 ... vi a1 a2 ... ak vj
// let ri be the duration of meeting vi, according to that position, likewise for rj
// let rmax be the longest meeting among a1 a2 .. ak
// we reorder to get a1 a2 ... ak vj vi
// we can do this because at this point v1 has no outdegree
// now vi < vj so ri + k < rj
// so ri + k + 1 <= rj
// in permutation a1 a2 ... ak vj vi
// the results are rmax - 1, rj - 1, ri + k + 1
// easy to show that in this order, the maximum length meeting can only decrease


vector<int> outDegSize;
vector<int> duration;
vector<vector<int>> inDegree;
int n;

void print(vector<int> arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}


int minLongestMeeting() {
   
    int prevMeetings = n - 1;
    int longest = 0;
    auto cmp = [] (vector<int>& a, vector<int>& b) -> bool {return a[1] > b[1];};
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
    
    for (int i = 0; i < n; i ++) {
        if (outDegSize[i] == 0) {
            pq.push({i, duration[i]});
        }
    }
    
    while (!pq.empty()) {
        vector<int> next = pq.top();
        pq.pop();
        longest = max(longest, prevMeetings + next[1]);
        prevMeetings --;
        vector<int>& childs = inDegree[next[0]];
        for (int c : childs) {
            outDegSize[c] --;
            if (outDegSize[c] == 0) {
                pq.push({c, duration[c]});
            }
        }
    }
    
    return longest;
}



int main() {
    cin >> n;
    inDegree = vector(n, vector<int>());
    outDegSize = vector(n, 0);
    duration = vector(n, 0);
    for (int i = 0; i < n; i ++) {
        int dur;
        int numChilds;
        cin >> dur >> numChilds;
        duration[i] = dur;
        for (int j = 0; j < numChilds; j ++) {
            int c;
            cin >> c;
            c --;
            
            outDegSize[c] ++;
            inDegree[i].push_back(c);
        }
    }
    int ans = minLongestMeeting();
    cout << ans;
    return 0;
}
