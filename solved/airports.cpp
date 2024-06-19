#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// basically we construct the DAG from the flights Fi
// Fi -> Fj if a plane can do Fi, then Fj
// so problem becomes finding minimum paths to cover all vertices of a DAG
// convert to a bipartite graph and find maximum matching m, minimum number of paths is n - m, n: # vertices in DAG
// for each node in DAG, convert to 2 nodes uout, vin
// so if n1 -> n2, in bipartite graph u1 -> v2 so taking u1 - v2 as a matching means after F1 do F2
// since no cyles, can never have a cycle in bipartite graph too


void print(vector<vector<int>> arr) {
    for (int i = 0; i < arr.size(); i ++) {
        for (int j = 0; j < arr[0].size(); j ++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}


class FloydWarshall {
public:
    vector<vector<vector<int>>> dp;
    // currSide is the side we are going to update, this means 1 - currSide contains the correct data once we are done with Floyd Warshall
    int currSide = 0;
    int n;

    FloydWarshall(vector<vector<int>>& adjMatrix, vector<int>& inspectTime) {
        //this->adjMatrix = adjMatrix;
        //this->inspectTime = inspectTime;
        this->n = inspectTime.size();
        dp = vector(2, vector(n, vector(n, 0)));
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                if (i == j) continue;
                dp[currSide][i][j] = adjMatrix[i][j] + inspectTime[j];
            }
        }
        currSide = 1 - currSide;

        // invariant is that dp[1 - currSide][i][j] contains time needed to go from i to j and be availble to fly again, i.e j inspect time is taken into account already
        for (int c = 0; c < n; c ++) {
            for (int i = 0; i < n; i ++) {
                for (int j = 0; j < n; j ++) {
                    if (i == j) continue;
                    dp[currSide][i][j] = min(dp[1 - currSide][i][j], dp[1 - currSide][i][c] +  dp[1 - currSide][c][j]);
                }
            }
            currSide = 1 - currSide;
        }
    }
};

class Solver {
public:
    // s is 2n, t is 2n + 1
    //vector<vector<int>> shortestTime;
    vector<unordered_map<int, int>> capacities;
    int n;
    int s;
    int t;


    // the airports index MUST be 0 indexed, so -1 from I/O
    Solver(vector<int>& inspectTime, vector<vector<int>>& adjMatrix, vector<vector<int>>& flights, vector<vector<int>>& shortestTime) {
        n = flights.size();
        capacities = vector(2 * n + 2, unordered_map<int, int>());
        s = 2 * n;
        t = s + 1;
        
        for (int i = 0; i < n; i ++) {
            int start = flights[i][1];
            int endTime = flights[i][2] + adjMatrix[flights[i][0]][flights[i][1]] + inspectTime[flights[i][1]];
            for (int j = 0; j < n; j ++) {
                if (i == j) continue;
                int end = flights[j][0];
                int startTime = flights[j][2];
                int nextAvailableTime = (start == end) ? endTime : endTime + shortestTime[start][end];
                if (nextAvailableTime <= startTime) {
                    int uout = i;
                    int vin = n + j;
                    //cout << uout << " " << vin << endl;
                    capacities[uout][vin] = 1;   
                    capacities[vin][uout] = 0;             
                }
            }
        }

        // connect source and sink
        for (int i = 0; i < n; i ++) {
            capacities[s][i] = 1;
            capacities[i][s] = 0;
            capacities[i + n][t] = 1;
            capacities[t][i + n] = 0;
        }

        
    }

    bool dfs(int src, vector<bool>& visited) {
        visited[src] = true;
        if (src == t) {
            return true;
        } else {
            for (const auto& [key, value] : capacities[src]) {
                if (value > 0 && !visited[key]) {
                    bool res = dfs(key, visited);
                    if (!res) continue;
                    capacities[src][key] = 0;
                    capacities[key][src] = 1;
                    return true;
                }
            }
            return false;
        }
    }

    int findMininumPathToCover() {
        int sum = 0;
        while (true) {
            vector<bool> visited = vector(2 * n + 2, false);
            bool canAdd = dfs(s, visited);
            if (!canAdd) break;
            sum += 1;
        }
        return n - sum;
    }
};



int main() {
    int n, m;
    cin >> n >> m;
    vector<int> inspectTime;
    vector<vector<int>> adjMatrix(n, vector(n, 0));
    vector<vector<int>> flights;

    for (int i = 0; i < n; i ++) {
        int time;
        cin >> time;
        inspectTime.push_back(time);
    }
    
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            int dist;
            cin >> dist;
            adjMatrix[i][j] = dist;
        }
    }

    

    for (int i = 0; i < m; i ++) {
        int s;
        int f;
        int t;
        cin >> s >> f >> t;
        s --; f --;
        flights.push_back({s, f, t});
    }

    FloydWarshall fw(adjMatrix, inspectTime);
    //print(fw.dp[1 - fw.currSide]);
    Solver sol(inspectTime, adjMatrix, flights, fw.dp[1 - fw.currSide]);
    int ans = sol.findMininumPathToCover();
    cout << ans;

}

