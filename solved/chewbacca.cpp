#include <vector>
#include <iostream>

using namespace std;
// let the branching factor be k, formula to get parent is n + k - 2 / k, if n is not 1

vector<long long> pathToRoot(long long n, long long k) {
    if (n == 1) {
        return {1};
    } else {
        long long parent = (n + k - 2) / k;
        vector<long long>&& wish = pathToRoot(parent, k);
        wish.push_back(n);
        return wish;
    }
}

long long length(long long x, long long y, long long k) {
    if (k == 1) {
        return max(x, y) - min(x, y);
    }
    
    vector<long long>&& px = pathToRoot(x, k);
    vector<long long>&& py = pathToRoot(y, k);
    for (int i = min(px.size() - 1, py.size() - 1); i >= 0; i --) {
        if (px[i] == py[i]) {
            return px.size() - 1 - i + py.size() - 1 - i;
        }
    }
    return -1;
}

template <typename T>
void print(vector<T> a) {
    for (T t : a) {
        cout << t << " ";
    }
    cout << endl;
}

int main() {
    long long N, k, q;
    cin >> N >> k >> q;
    for (int i = 0; i < q; i ++) {
        long long x, y;
        cin >> x >> y;
        cout << length(x, y, k) << '\n';
    }
}