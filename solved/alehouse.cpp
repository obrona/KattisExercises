// 2 events, visit, and leave
// idea is that the optimal visiting range only starts and ends at an even
// if not, can always shorten, since we do not encounter an event, no change to # of people visiting alehouse in the range
// use sliding window
// visit event cnt ++, leave event cnt --
// sort the events ascending order
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


// {time, type of event}
// 1 for visit, 0 for leave
int maxFriends(vector<vector<int>>& events, int k) {
    int best = 0;
    int curr = 0;
    int s = 0;
    int e = 0;
    while (e < events.size()) {
        if (events[s][0] + k >= events[e][0]) {
            // if event is leave, no need to minus, because s <= time of leave event
            curr = (events[e][1] == 1) ? curr + 1 : curr;
            e ++;
            best = max(best, curr);
        } else {
            // if event is visit, not need to minus
            curr = (events[s][1] == 0) ? curr - 1 : curr;
            s ++;
            best = max(best, curr);
        }
    }
    return best;
}

void print(vector<vector<int>> a) {
    for (int i = 0; i < a.size(); i ++) {
        cout << a[i][0] << " " << a[i][1] << endl;
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> events;
    for (int i = 0; i < n; i ++) {
        int s, e;
        cin >> s >> e;
        events.push_back({s, 1});
        events.push_back({e, 0});
    }
    // visit must come before leave
    sort(events.begin(), events.end(), [](vector<int> a, vector<int> b)->bool{return (a[0] == b[0]) ? a[1] > b[1] : a[0] < b[0];});
    //print(events);
    int ans = maxFriends(events, k);
    cout << ans;
}
