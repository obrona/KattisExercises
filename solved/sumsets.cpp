#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

// basically we store nC2 pairs of possible (a, b), store a + b in a hashmap
// next for all possible 2*nC2 pairs of (-c, d), we find all the pairs of a + b = -c + d
// them we iterate through the indexes till we find one where indexes of (-c, d) and (a, b) do not intersect
// this is actually O(1) and not O(n) because all the numbers are distinct
// suppose indexes for (-c, d) are (i1, j1) and we have a pair (a, b) of index (i1, x1)
// now we cannot have (a, b) pairs of indexes (i1, x1), (i1, x2), (i1, x3) ... all of the same sum this is because all numbers are distinct
// so max we fail 4 times i1 = a1, i1 = b1, j1 = a1, j1 = b2 before we find 1 pair that satid=sfy requirement or fail completely

struct Pair {
    int i, j;
};

//unordered_map<int, vector<Pair>> pairs1;
unordered_map<int, vector<Pair>> pairs2;
vector<int> nums;

/*void process(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i ++) {
        for (int j = i + 1; j < nums.size(); j ++) {
            
            int x = nums[i];
            int y = nums[j];
            pairs1[-x + y].push_back({i, j});
            pairs1[-y + x].push_back({j, i});
            pairs2[x + y].push_back({i, j});
        }
    }
}

int getBestD() {
    int best = -999999999;
    for (auto const& [key, value] : pairs1) {
        for (const Pair& p : value) {
            if (pairs2.find(key) == pairs2.end()) continue;
            vector<Pair>& poss = pairs2[key];
            for (int i = 0; i < poss.size(); i ++) {
                Pair& p2 = poss[i];
                if (p.i == p2.i || p.j == p2.j || p.i == p2.j || p.j == p2.i) continue;
                // can immediately stop after finding the first (a, b) pair satisfying a+b = -c+d
                //cout << "pair 1: " << p.i << " " << p.j << " " << p.d << endl;
                //cout << "pair 2: " << p2.i << " " << p2.j << " " << p.d << endl;
                best = max(best, nums[p.j]);
                break;
            }
        }
    }
    return best;
}*/

void process2() {
    for (int i = 0; i < nums.size(); i ++) {
        for (int j = i + 1; j < nums.size(); j ++) {
            pairs2[nums[i] + nums[j]].push_back({i, j});
        }
    }
}


// x is index for c, y is index for d
// sum = -c+d
bool check(int x, int y) {
    int sum = -nums[x] + nums[y];
    if (pairs2.find(sum) == pairs2.end()) return false;
    vector<Pair>& poss = pairs2[sum];
    for (int k = 0; k < poss.size(); k ++) {
        Pair& p2 = poss[k];
        if (x == p2.i || x == p2.j || y == p2.i || y == p2.j) continue;

        //cout << "pair 1: " << x << " " << y << " " << sum << endl;
        //cout << "pair 2: " << p2.i << " " << p2.j << " " << sum << endl;
        return true;
    }
    return false;
}

int getBestD2() {
    int best = -999999999;
    for (int i = 0; i < nums.size(); i ++) {
        for (int j = i + 1; j < nums.size(); j ++) {
            //int sum1 = -nums[i] + nums[j];
            if (check(i, j)) best = max(best, nums[j]);
            if (check(j, i)) best = max(best, nums[i]);
        }
    }
    return best;
}


int main() {
    //vector<int> nums;
    int n;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    process2();
    int res = getBestD2();
    if (res <= -999999999) {
        cout << "no solution" << endl;
    } else {
        cout << res << endl;
    }
    
}