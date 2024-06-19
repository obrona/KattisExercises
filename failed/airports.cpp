#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// we can binary search the number of planes needed, since if x planes can satisfy all flights, clearly x + 1, x + 2 ... can satisfy all flights too
// we greedily find the earliest plane available to take the next flight
// we store the plane end times in a vector, we need to iterate all planes to get the earliest plane available
// can prove that for each flight, just need to consider the earliest plane available
// sorry this is wrong :(
int findEarliest(vector<vector<int>>& flightTime, vector<int>& inspect, vector<vector<int>>& queue, int airport, int time) {
    int index = -1;
    int t = 999999999;
    for (int i = 0; i < queue.size(); i ++) {
        // next available time + flightTime to next airport + inspect time
        int availableT = (queue[i][0] != airport) ? queue[i][1] + flightTime[queue[i][0]][airport] + inspect[airport] :
            queue[i][1];
        if (availableT <= time && availableT < t) {
            index = i;
            t = availableT;
        }
    }
    return index;
}

bool canSatisfy(vector<vector<int>>& flightTime, vector<int>& inspectTime, vector<vector<int>>& sortedFlights, int planes) {
    
    vector<vector<int>> queue;
    vector<int>& first = sortedFlights[0];
    planes -= 1;
    int finish = first[2] + flightTime[first[0]][first[1]] + inspectTime[first[1]];
    queue.push_back({first[1], finish});
    for (int i = 1; i < sortedFlights.size(); i ++) {
        vector<int>& f = sortedFlights[i];
        int s = f[0];
        int e = f[1];
        int t = f[2];
        int earliest = findEarliest(flightTime, inspectTime, queue, s, t);
        //cout << earliest << endl;
        if (earliest == -1) {
            if (planes == 0) {
                return false;
            } else {
                planes -= 1;
                int finish = t + flightTime[s][e] + inspectTime[e];
                queue.push_back({e, finish});
            }
        } else {
            queue.erase(queue.begin() + earliest);
            int finish = t + flightTime[s][e] + inspectTime[e];
            queue.push_back({e, finish});
        }
    }
    return true;
}

int binarySearch(vector<vector<int>>& fT, vector<int>& inspect, vector<vector<int>>& flights, int s, int e) {
    if (s >= e) {
        return s;
    } else {
        int m = (s + e) / 2;
        bool res = canSatisfy(fT, inspect, flights, m);
        if (res) {
            return binarySearch(fT, inspect, flights, s, m);
        } else {
            return binarySearch(fT, inspect, flights, m + 1, e);
        }
    }
}

int main() {
    vector<vector<int>> flightTime = {
        
        {0, 443, 912, 226, 714},
        {18, 0, 776, 347, 810},
        {707, 60, 0, 48, 923},
        {933, 373, 881, 0, 329},
        {39, 511, 151, 364, 0}
    };
    vector<int> inspect = {72, 54, 71, 94, 23};
    vector<vector<int>> flights = {
        {3, 2, 151},
        {3, 1, 174},
        {1, 0, 583},
        {0, 3, 841},
        {3, 2, 993}
    };
    bool ans = canSatisfy(flightTime, inspect, flights, 3);
    cout << ans; 
}

/*int main() {
    int n, m;
    cin >> n >> m;
    vector<int> inspect = vector<int>();
    for (int i = 0; i < n; i ++) {
        int t;
        cin >> t;
        inspect.push_back(t);
    }
    vector<vector<int>> fT = vector(n, vector(n, 0));
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            int t;
            cin >> t;
            fT[i][j] = t;
        }
    }
    vector<vector<int>> flights = vector<vector<int>>();
    for (int i = 0; i < m; i ++) {
        int s, e, t;
        cin >> s >> e >> t;
        vector<int> f = {s - 1, e - 1, t};
        flights.push_back(f);
    }
    auto cmp = [](vector<int>& x, vector<int>& y) -> bool {return x[2] < y[2];};
    sort(flights.begin(), flights.end(), cmp);
    int ans = binarySearch(fT, inspect, flights, 1, m);
    cout << ans;
    
}*/