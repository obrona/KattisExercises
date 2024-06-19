#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

// i think the solution is to sort players in ascending strength, except for dale.
// put dale as players[0]
// if total players are not a power of 2, starting from Dale and the weakest players, add
// dummy players with 0 strength
// eg 5 2 3 3 4 6 become 5 0 2 0 3 3 4 6
// basically we give free passes to Dale, and as many of the weakest players

// beware that 0 / 0 is nan, so instead of putting dummy players of score 0, we put their score as 0.0000001 

int leftOver(int n) {
    return (int) pow(2, ceil(log2(n))) - n;
}

void print(vector<double> arr) {
    for (double x : arr) {
        cout << x << " ";
    }
    cout << endl;
}







class Solution {
public:
    
    // dale is always at players[0], after sorting
    vector<double> players;
    int N;

    Solution(int n) {
        N = n;
    }
    
    // only need to know probabilty of Dale winning
    double helper1(int s, int e) {
        if (s == e) {
            return 1.0;
        } else {
            int m = (s + e) / 2 - ((e - s + 1) % 2);
            double probDale = helper1(s, m);
            vector<double>&& probs = helper2(m + 1, e);
            double sum = 0;
            for (int i = 0; i < probs.size(); i ++) {
                double probWin = probs[i]  / (players[0] + players[m + 1 + i]);
                sum += probWin;
            }
            sum *= (probDale * players[0]);
            return sum;
        }
    }

    // need to know the probability of the player winning, for every player
    vector<double> helper2(int s, int e) {
        if (s == e) {
            return {1.0};
        } else {
            int m = (s + e) / 2;
            vector<double>&& lhs = helper2(s, m);
            vector<double>&& rhs = helper2(m + 1, e);
            vector<double> res;
            for (int i = 0; i < lhs.size(); i ++) {
                double sum = 0;
                for (int j = 0; j < rhs.size(); j ++) {
                    sum += rhs[j] / (players[s + i] + players[m + 1 + j]);
                }
                sum *= (lhs[i] * players[s + i]);
                res.push_back(sum);
            }

            for (int i = 0; i < rhs.size(); i ++) {
                double sum = 0;
                for (int j = 0; j < lhs.size(); j ++) {
                    sum += lhs[j] / (players[m + 1 + i] + players[s + j]);
                }
                sum *= (rhs[i] * players[m + 1 + i]);
                res.push_back(sum);
            }
            //cout << s << " " << e << " ";
            //print(res);
            return res;
        }
    }

    void process() {
        sort(players.begin() + 1, players.end());
        vector<double> temp;
        int remainder = leftOver(N);
        int tempRem = remainder;
        for (int i = 0; i < N; i ++) {
            temp.push_back(players[i]);
            if (remainder > 0) {
                temp.push_back(0.00000001);
                remainder --;
            }
        }
        players = temp;
        N += tempRem;
        
        
    }
};



int main() {
    int N;
    cin >> N;
   
    Solution sol(N);
    for (int i = 0; i < N; i ++) {
        double score;
        cin >> score;
        sol.players.push_back(score);
        
    }
    sol.process();
    //print(sol.players);
    //cout << sol.N << endl;
    cout << fixed << setprecision(10);
    cout << sol.helper1(0, sol.N - 1);
}


