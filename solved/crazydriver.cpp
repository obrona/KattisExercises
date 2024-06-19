#include <vector>
#include <iostream>
using namespace std;
// suppose we know the cheapest cost to pass the ith gate. To pass the (i + 1)th gate, we waste time at the cheapest edge
// from gate 0 to gate i + 1
// this is the cheapest solution
// for the cheapest solution, we also need the time needed
// suppose for the ith gate, there is a solution where the time reached is longer (hence need to waste less time), but cost is more expensive
// however, for that cost to the least expensive, it must still waste time at the cheapest edge between gate 0 and gate i
// obviously the cost of that gate is >= cheapest gate between 0 and i + 1

void print(vector<long long> a) {
    for (int i = 0; i < a.size(); i ++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

vector<long long> minEdge(vector<long long>& gates, int n) {
    vector<long long> out = vector(n, 0LL);
    out[0] = 999999;
    for (int i = 1; i < n; i ++) {
        out[i] = min(gates[i - 1], out[i - 1]);
    }
    return out;
}

long long minCost(vector<long long>& toll, vector<long long>& time, int n) {
    vector<long long>&& minEdges = minEdge(toll, n);
    //print(minEdges);
    vector<long long> timeNeeded = vector(n, 0LL);
    vector<long long> minCosts = vector(n, 0LL);
    for (int i = 1; i < n; i ++) {
        long long prevGateTime = timeNeeded[i - 1];
        long long prevGateCost = minCosts[i - 1];
        //cout << prevGateTime << endl;
        if (prevGateTime >= time[i] - 1) {
            timeNeeded[i] = prevGateTime + 1;
            minCosts[i] = prevGateCost + toll[i - 1];
        } else {
            long long diff = time[i] - prevGateTime;
            timeNeeded[i] = (diff % 2 == 0) ? time[i] + 1 : time[i];
            diff -= (diff % 2 == 0) ? 0 : 1;
            minCosts[i] = minEdges[i] * diff + toll[i - 1] + prevGateCost;
        }
    }
    //print(minCosts);
    //print(timeNeeded);
    return minCosts[n - 1];
}

int main() {
    int n;
    cin >> n;
    vector<long long> toll = vector<long long>();
    vector<long long> time = vector<long long>();
    for (int i = 0; i < n - 1; i ++) {
        int t;
        cin >> t;
        toll.push_back(t);
    }
    for (int i = 0; i < n; i ++) {
        int ti;
        cin >> ti;
        time.push_back(ti);
    }
    //print(toll);
    //print(time);
    long long ans = minCost(toll, time, n);
    cout << ans;
}