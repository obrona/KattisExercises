#include <vector>
#include <iostream>
using namespace std;
// O(nlogn) rejected must do bottom up O(n) dp;
vector<long long> dp;

int bSearch(vector<int> array, int key) {
    int s = 0;
    int e = array.size() - 1;
    if (array[e] <= key) return e + 1;
    while (s < e) {
        int m = (s + e) / 2;
        if (array[m] <= key) {
            s = m + 1;
        } else {
            e = m;
        }
    }
    return s;
}

long long helper(int index, vector<int>& array, long long dayPrice, long long passPrice, int dur) {
    if (index == array.size()) {
        return 0L;
    } else if (dp[index] != -1) {
        return dp[index];
    } else {
        long long day = dayPrice + helper(index + 1, array, dayPrice, passPrice, dur);
        int next = bSearch(array, array[index] + dur - 1);
        long long pass = passPrice + helper(next, array, dayPrice, passPrice, dur);
        dp[index] = min(day, pass);
        return dp[index];
    }
}


void bottomUp(vector<int>& array, long long dayPrice, long long passPrice, int dur) {
    dp[array.size()] = 0;
    int j = array.size() - 1;
    for (int i = array.size() - 1; i >= 0; i --) {
        if (array[i] + dur - 1 >= array[array.size() - 1]) {
            dp[i] = min(dayPrice + dp[i + 1], passPrice);
            
        } else {
            // move j to the left until next bus ride just nice right after the pass ends if I buy the pass on day(array[i])
            while (j > i + 1 && array[i] + dur - 1 < array[j - 1]) {
                j --;
            }
            dp[i] = min(dayPrice + dp[i + 1], passPrice + dp[j]);

        }
    }
}

template <typename T>
void print(vector<T> a) {
    for (T x : a) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    long long dayPrice, passPrice;
    int dur, n;
    cin >> dayPrice >> passPrice >> dur >> n;
    vector<int> days;
    for (int i = 0; i < n; i ++) {
        int d;
        cin >> d;
        days.push_back(d + 1);
    }
    //print(days);
    //cout << (days[1] + dur - 1 >= days[days.size() - 1]) << endl;
    //cout << (31 >= 31) << endl;
    dp = vector<long long>(n + 1, -1L);
    bottomUp(days, dayPrice, passPrice, dur);
    //print(dp);
    cout << dp[0];
}