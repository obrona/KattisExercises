#include <iostream>
#include <vector>
using namespace std;

bool valid(int r, int c, vector<vector<char>>& matrix) {
    return (r < 0 || c < 0 || r >= matrix.size() || c >= matrix[0].size()) ? false : true;
}

void dfs(int r, int c, vector<vector<char>>& matrix, vector<vector<bool>>& visited) {
    if (!visited[r][c]) {
        visited[r][c] = true;
        if (valid(r + 1, c, matrix) && matrix[r + 1][c] == '#') {
            if (valid(r, c - 1, matrix) && matrix[r][c - 1] == '.') {
                matrix[r][c - 1] = 'V';
                dfs(r, c - 1, matrix, visited);
            }
            if (valid(r, c + 1, matrix) && matrix[r][c + 1] == '.') {
                matrix[r][c + 1] = 'V';
                dfs(r, c + 1, matrix, visited);
            }
        } else {
            if (valid(r + 1, c, matrix)) {
                matrix[r + 1][c] = 'V';
                dfs(r + 1, c, matrix, visited);
            }
        }
    }
}

template <typename T>
void print(vector<vector<T>>& res) {
    for (int i = 0; i < res.size(); i ++) {
        for (int j = 0; j < res[0].size(); j ++) {
            cout << res[i][j];
        }
        cout << '\n';
    }
}

vector<char> stringToArray(string& s) {
    vector<char> out = vector(s.size(), '.');
    for (int i = 0; i < s.size(); i ++) {
        out[i] = s[i];
    }
    //cout << out.size() << endl;
    return out;
}

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore();
    vector<vector<char>> matrix = vector<vector<char>>();
    //vector<vector<char>> res = vector(n, vector(m, '.'));
    vector<vector<bool>> visited = vector(n, vector(m, false));
    for (int i = 0; i < n; i ++) {
        string line;
        getline(cin, line);
        //cout << line << endl;
        vector<char>&& a = stringToArray(line);
        matrix.push_back(a);
        //cout << line << endl;
        //matrix.push_back(stringToArray(line));
    }
    //print(matrix);
    //cout << (matrix[0][3] == 'V') << endl;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            if (matrix[i][j] == 'V') {
                dfs(i, j, matrix, visited);
            }
            //dfs(i, j, matrix, visited);
        }
    }
    print(matrix);
}