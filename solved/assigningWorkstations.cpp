#include <map>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

// greedy problem, sort the jobs in ascending order, for each job find the earliest job that can remain unlock, if cannot 
// add 1 to unlock count
// i.e ealiest job that ends before the arrival of new job, and remains unlocked when the new job arrives
// if found the job to takeover, must pop it, otherwise other jobs may again takeover from that job
// never define interval !!!

// t[0] is start time, t[1] is end time

auto cmp = [](vector<int>& a, vector<int>& b) -> bool {return a[0] < b[0];};

int minUnlocks(vector<vector<int>>& times, long long k) {
    priority_queue<int, vector<int>, greater<int>> pq;
    int cnt = 0;
    for (int i = 0; i < times.size(); i ++) {
        vector<int>& t = times[i];
        if (pq.empty()) {
            cnt ++;
            pq.push(t[1]);
        } else {
            while (!pq.empty() && pq.top() + k + 1 < t[0]) {
                pq.pop();
            }
            if (pq.empty() || pq.top() >= t[0]) cnt ++;
            else pq.pop();
            pq.push(t[1]);
        }
    }
    return cnt;
}

void print(vector<vector<int>> a) {
    for (vector<int> x : a) {
        cout << x[0] << " " << x[1] << endl;
    }
}

int main() {
   int n, k;
   cin >> n >> k;
   vector<vector<int>> times;
   for (int i = 0; i < n; i ++) {
    int s, e;
    cin >> s >> e;
    times.push_back({s, s + e - 1});
   }
   sort(times.begin(), times.end(), cmp);
   //print(times);
   int ans = minUnlocks(times, k);
   cout << n - ans;


}