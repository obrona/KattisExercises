#include <vector>
#include <queue>
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

// greedy start from back

// {time, money}
int mostMoney(int n, vector<vector<int>> deposits) {
    priority_queue<int> pq;
    sort(deposits.begin(), deposits.end(), [] (vector<int>& a, vector<int>& b) -> bool {return a[0] < b[0];});
    int p = deposits.size() - 1;
    int sum = 0;
    for (int i = n - 1; i >= 0; i --) {
        while (p >= 0) {
            if (deposits[p][0] >= i) {
                pq.push(deposits[p][1]);
                p --;
            } else {
                break;
            }
            
            
        }
        if (!pq.empty()) {
            int best = pq.top();
            pq.pop();
            sum += best;
        }
    }
    return sum;
}
int main() {
    int numPeople, time;
    
    cin >> numPeople >> time;
    vector<vector<int>> deposits;
    for (int i = 0; i < numPeople; i ++) {
        int money;
        int t;
        cin >> money >> t;
        deposits.push_back({t, money});
    }
    int ans = mostMoney(time, deposits);
    cout << ans;

}