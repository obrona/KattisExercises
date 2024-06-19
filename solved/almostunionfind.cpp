#include <vector>
#include <iostream>
using namespace std;

// each node has a dummy mirror of itself. Invariant, all real nodes can only be a child of a dummy, they cannot be a child to a real node
// so that we can do 'move'
// no real node can be a parent of anything

class UnionFindMove {
public:
    vector<int> parent;
    vector<int> count;
    vector<long long> sum;

    UnionFindMove(int s): parent(2 * s + 1, 0), count(2 * s + 1, 1), sum(2 * s + 1, 0LL) {
        for (int i = 1; i < 2 * s + 1; i ++) {
            if (i <= s) {
                parent[i] = i + s;
            } else {
                parent[i] = i;
                sum[i] = i - s;
            }
        } 
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        } else {
            int p = find(parent[x]);
            parent[x] = p;
            return p;
        }
    }

    void move(int p, int q) {
        int pp = find(p);
        int pq = find(q);
        if (pp != pq) {
            parent[p] = pq;
            count[pq] += 1;
            sum[pq] += p;
            count[pp] -= 1;
            sum[pp] -= p;
        }
    }

    void join(int p, int q) {
        int pp = find(p);
        int pq = find(q);
        if (pp != pq) {
            parent[pp] = pq;
            count[pq] += count[pp];
            sum[pq] += sum[pp];
        }
    }

    void printSumWeight(int p) {
        int pp = find(p);
        cout << count[pp] << " " << sum[pp] << '\n';
    }
};

int main() {
    int n, m;
    while (cin >> n >> m) {
        UnionFindMove ufm(n);
        for (int i = 0; i < m; i ++) {
            int inst, p;
            cin >> inst >> p;
            if (inst == 1) {
                int q;
                cin >> q;
                ufm.join(p, q);
            } else if (inst == 2) {
                int q;
                cin >> q;
                ufm.move(p, q);
            } else {
                ufm.printSumWeight(p);
            }
        }
    }
}