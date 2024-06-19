#include <vector>
#include <iostream>
using namespace std;

// basically, to know the amount of water to breach the node, which is the root of the subtree
// check the amount of water needed to breach its subchilds, and the resultant water
// top up to the amount if needed
// if 2 children return the same amount of water needed, must take the one that results in larger water in the end
vector<vector<int>> adjList;
vector<vector<int>*> dp;
vector<vector<int>> info;

// index 0 : minimum water needed to breach, index 1 : the resulting water
vector<int>* helper(int node, int parent) {
    if (dp[node] != NULL) {
        return dp[node];
    } else {
        int limit = info[node][0];
        int curr = info[node][1];
        int req = limit - curr;
        
        int best = 2000000000;
        int result = 0;
        vector<int>& childs = adjList[node];
        for (int child : childs) {
            if (child != parent) {
                vector<int>* c = helper(child, node);
                int a = c->at(0);
                int b = c->at(1);
                if (b < req) {
                    a += req - b;
                    b = limit;
                } else {
                    b += curr;
                }
                if (b >= best) {
                    result = max(b, result);
                } else {
                    best = b;
                }
                
            }
        }
    }
}