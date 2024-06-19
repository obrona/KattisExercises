#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>

// tree dp, state is (node, toUse) if toUse = 1, means can use or dont use, your choice
// if use, iterate pairing will the possible children, take best result
// if noUse, iterate on the subtree
// result, store {#pairs, #sum of score}
// maximise pairs first, then maximise score

using namespace std;

template <typename T>
void print(vector<T> a) {
    for (T t : a) {
        cout << t << " ";
    }
    cout << endl;
}

class Pair {
public:
    int c;
    double s;

    Pair() {
        c = -1;
        s = -1.0;
    }
    Pair(int a, double b) {
        c = a;
        s = b;
    }
};

unordered_map<int, unordered_map<string, Pair*>> dp;

unordered_map<string, vector<string>> adjList;

unordered_map<string, double> speed;

Pair* helper(string person, int toUse, string parent) {
    //cout << person << " " << toUse << endl;
    if (dp[toUse][person] != 0) {
        return dp[toUse][person];
    } else if (!toUse) {
        // dont pair the person
        vector<string>& childs = adjList[person];
        int maxCount = 0;
        double maxScore = 0.0;
        for (string& child : childs) {
            if (child != parent) {
                Pair* p = helper(child, 1, person);
                maxCount += p->c;
                maxScore += p->s;
            }
        }
        Pair* pRes = new Pair(maxCount, maxScore);
        dp[toUse][person] = pRes;
        return pRes;
    } else {
        // pair the person with 1 of his subordinates or dont pair at all
        
        // dont pair him at all first
        Pair* p1 = helper(person, 0, parent);
        int maxCountStore = p1->c;
        double maxScoreStore = p1->s;
       
        
        int maxCount = 0;
        double maxScore = 0.0;
        vector<string>& childs = adjList[person];
        for (string& child : childs) {
            // pair person with this child
            if (child != parent) {
                // use the result of not pairing person with anyone to reduce time complexity from O(N) per checking person pair with this child to O(1)
                int m = maxCountStore - helper(child, 1, person)->c + helper(child, 0, person)->c + 1;
                double n = maxScoreStore - helper(child, 1, person)->s + helper(child, 0, person)->s + min(speed[person], speed[child]);

                if (m >= maxCount) {
                    maxCount = max(m, maxCount);
                    maxScore = max(n, maxScore);
                }
            }
        }
        if (maxCount < maxCountStore) {
            maxCount = maxCountStore;
            maxScore = maxScoreStore;
        } else if (maxCount == maxCountStore) {
            maxScore = max(maxScore, maxScoreStore);
        }
        Pair* pRes = new Pair(maxCount, maxScore);
        dp[toUse][person] = pRes;
        return pRes;
    }
}








int main() {
    int numPeople;
    cin >> numPeople;
    string ceo;
    for (int i = 0; i < numPeople; i ++) {
        string name;
        double s;
        string superior;
        cin >> name >> s >> superior;
        //cout << name << " " << s << " " << superior << endl;
        speed[name] = s;
        //adjList[name].push_back(superior);
        if (superior != "CEO") {
            adjList[name].push_back(superior);
            adjList[superior].push_back(name);
        } else {
            ceo = name;
        }
    }
    //cout << adjList[""]
    //print(adjList["Barbara"]);
    //cout << speed["Barbara"] << endl;
    
    //cout << ceo << endl;
    Pair* p1 = helper(ceo, 1, ceo);
    Pair* p2 = helper(ceo, 0, ceo);
    //cout << p2->c << " " << p2->s / p2->c << endl;

    
    //Pair* p4 = helper("Barbara", 1, "Barbara");
    //cout << p4->c << " " << p4-> s << endl;

    
    if (p1->c > p2->c) {
        cout << p1->c << " " << p1->s / p1->c;
    } else if (p2->c > p1->c) {
        cout << p2->c << " " << p2->s / p2->c;
    } else {
        cout << p1->c << " " << max(p2->s, p1->s) / p1->c;
    }
    
}