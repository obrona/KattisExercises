#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;
using ll = long long;

// simply TSP O(n^2 * 2^n) dp
// only do disjkstra for the shops, we only care about the shortest path between any 2 different shop

vector<ll> dijkstra(int src, int n, vector<unordered_map<int, ll>>& adjList) {
    vector<bool> visited(n, false);
    vector<ll> res(n, -1);
    auto cmp = [](vector<ll>& a, vector<ll>& b) -> bool {return a[1] > b[1];};
    priority_queue<vector<ll>, vector<vector<ll>>, decltype(cmp)> pq(cmp);
    pq.push({src, 0});
    while (!pq.empty()) {
        vector<ll> next = pq.top();
        pq.pop();
        int node = next[0];
        ll dist = next[1];
        if (visited[node]) continue;
        visited[node] = true;
        res[node] = dist;
        for (auto const& [key, value] : adjList[node]) {
            if (!visited[key]) {
                pq.push({key, dist + value});
            }
        }
    }
    return res;
}

unordered_map<int, unordered_map<int, ll>> buildSP(int n, vector<int>& shops, vector<unordered_map<int, ll>>& adjList) {
    unordered_map<int, unordered_map<int, ll>> res;

    /*vector<ll>&& dist = dijkstra(0, n, adjList);
    for (int i = 0; i < shops.size(); i ++) {
        res[0][shops[i]] = dist[shops[i]];
    }*/

    for (int s : shops) {
        vector<ll>&& distS = dijkstra(s, n, adjList);
        for (int i = 0; i < shops.size(); i ++) {
            res[s][shops[i]] = distS[shops[i]];
        }
    }

    return res;
}

vector<vector<ll>> dp;
vector<unordered_map<int, ll>> adjMatrix;
unordered_map<int, unordered_map<int, ll>> APSP;
vector<int> shops;
ll INF = 1000000000000LL;

ll helper(int start, int bitMap, int numShops) {
    int startShop = shops[start];
    if (dp[start][bitMap] != -1) {
        return dp[start][bitMap];
    } else if (bitMap == 0) {
        // already visited all shops, return to home
        dp[start][bitMap] = APSP[startShop][0];
        return dp[start][bitMap];
    } else {
        ll best = INF;
        for (int i = 0; i < numShops; i ++) {
            int shopDone = (bitMap >> i) & 1;
            if (shopDone == 0) continue;
            ll res = APSP[startShop][shops[i]] + helper(i, bitMap - (1 << i), numShops);
            best = min(best, res);
        }
        dp[start][bitMap] = best;
        return best;
    }
}

void print(unordered_map<int, unordered_map<int, ll>> map) {
    for (auto const& [key, value]: map) {
        cout << key << endl;
        for (auto const& [k2, v2]: map[key]) {
            cout << "{" << k2 << " " << v2 << "} ";
        }
        cout << endl;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    adjMatrix = vector(n, unordered_map<int, ll>());
    for (int i = 0; i < m; i ++) {
        int x, y;
        ll d;
        cin >> x >> y >> d;
        if (adjMatrix[x].find(y) == adjMatrix[x].end()) {
            adjMatrix[x][y] = d;
        } else {
            adjMatrix[x][y] = min(adjMatrix[x][y], d);
        }

        if (adjMatrix[y].find(x) == adjMatrix[y].end()) {
            adjMatrix[y][x] = d;
        } else {
            adjMatrix[y][x] = min(adjMatrix[y][x], d);
        }
        
    }
    int s;
    cin >> s;
    dp = vector(s + 1, vector<ll>((1 << s), -1));
    for (int i = 0; i < s; i ++) {
        int shop;
        cin >> shop;
        shops.push_back(shop);
    }
    shops.push_back(0);
    APSP = buildSP(n, shops, adjMatrix);
    //print(APSP);
    ll ans = helper(s,  (1 << s) - 1, s);
  
    cout << ans;
}
