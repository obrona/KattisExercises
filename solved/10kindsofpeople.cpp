#include <vector>
#include <iostream>
using namespace std;

bool valid(int r, int c, vector<vector<int>>& m) {
    return (r < 0 || c < 0 || r >= m.size() || c >= m[0].size()) ? false : true;
}

void floodFill(int x, int y, vector<vector<int>>& matrix, vector<vector<int>>& res, vector<vector<int>>& visited, int label) {
    if (!visited[x][y]) {
        visited[x][y] = 1;
        res[x][y] = label;
        int b = matrix[x][y];
        if (valid(x - 1, y, matrix) && matrix[x - 1][y] == b) {
            floodFill(x - 1, y, matrix, res, visited, label);
        }
        if (valid(x, y + 1, matrix) && matrix[x][y + 1] == b) {
            floodFill(x, y + 1, matrix, res, visited, label);
        }
        if (valid(x + 1, y, matrix) && matrix[x + 1][y] == b) {
            floodFill(x + 1, y, matrix, res, visited, label);
        }
        if (valid(x, y - 1, matrix) && matrix[x][y - 1] == b) {
            floodFill(x, y - 1, matrix, res, visited, label);
        }
    }
}

vector<int> toInt(string bin) {
    vector<int> out;
    for (int i = 0; i < bin.size(); i ++) {
        out.push_back((int) (bin[i] - '0'));
    }
    return out;
}

void print(vector<vector<int>> a) {
    for (int i = 0; i < a.size(); i ++) {
        for (int j = 0; j < a[0].size(); j ++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    
}

int main() {
    int r, c;
    cin >> r >> c;
    vector<vector<int>> matrix;
    vector<vector<int>> res = vector(r, vector(c, -1));
    vector<vector<int>> visited = vector(r, vector(c, 0));
    for (int i = 0; i < r; i ++) {
        string s;
        cin >> s;
        matrix.push_back(toInt(s));
    }
    int label = 1000000;
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            if (!visited[i][j]) {
                //cout << i << " " << j << endl;
                floodFill(i, j, matrix, res, visited, label);
                label += 1;
            }
        }
    }
    //print(res);
    vector<string> out;
    int size;
    cin >> size;
    for (int i = 0; i < size; i ++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        int b = matrix[r1 - 1][c1 - 1];
        int ans = res[r1 - 1][c1 - 1] == res[r2 - 1][c2 - 1] && res[r1 - 1][c1 - 1] != -1;
        if (!ans) {
            out.push_back("neither");
        } else if (b == 0) {
            out.push_back("binary");
        } else {
            out.push_back("decimal");
        }
    }
    for (int i = 0; i < size; i ++) {
        cout << out[i] << '\n';
    }
}