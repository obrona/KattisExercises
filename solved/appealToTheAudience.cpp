#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> nodeCount;
vector<vector<int>> adjList;


// we need to maximise the # of times the (node that gets counted the most times, from among the subtree) gets counted, so we let that node win
vector<int> helper(int node, int parent) {
    vector<int>& nbrs = adjList[node];
    if (nbrs.size() == 1 && node != 0) {
        return {node, 0};
    } else {
        int count = -1000;
        int n = -1;
        for (int i = 0; i < nbrs.size(); i ++) {
            if (nbrs[i] != parent) {
                vector<int>&& res = helper(nbrs[i], node);
                nodeCount[res[0]] += 1;
                if (res[1] > count) {
                    n = res[0];
                    count = res[1];
                }
            }
        }
        return {n, count + 1};
    }
}

long long maxHappy(vector<int>& skill) {
    auto cmp = [](int x, int y) -> bool {return x > y;};
    sort(skill.begin(), skill.end(), cmp);
    sort(nodeCount.begin(), nodeCount.end(), cmp);
    long long c = 0LL;
    for (int i = 0; i < skill.size(); i ++) {
        long long a = (long long) skill[i] * (long long) nodeCount[i];
        c += a;
    }
    return c;

}

template <typename T> 
void print(vector<T> a) {
    for (T t : a) {
        cout << t << " ";
    }
    cout << '\n';
}

/*int main() {
    adjList = {{1,2,4},{0,3,10},{0,5,7},{1},{0},{2,6,8,9},{5},{2},{5},{5},{1}};
    nodeCount = vector(11, 0);
    vector<int> skill = {30, 5, 15, 1, 3, 100, 50};
    helper(0, 0);
    print(nodeCount);
    cout << maxHappy(skill) << endl;
}*/

/*int main() {
    adjList = {{1,2},{0,3,4},{0},{1},{1}};
    nodeCount = vector(5, 0);
    helper(0, 0);
    print(nodeCount);
}*/

int main() {
    int n, m;
    cin >> n >> m;
    adjList = vector<vector<int>>(n, vector<int>());
    nodeCount = vector(n, 0);
    vector<int> skill;
    for (int i = 0; i < m; i ++) {
        int s;
        cin >> s;
        skill.push_back(s);
    }
    for (int i = 1; i <= n - 1; i ++) {
        int p;
        cin >> p;
        adjList[i].push_back(p);
        adjList[p].push_back(i);
    }
    helper(0, 0);
    long long ans = maxHappy(skill);
    cout << ans;

}