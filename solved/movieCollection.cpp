#include <vector>
#include <iostream>
using namespace std;
// basically if the take out movies sequence is eg 4 1 3 2 5
// we concat 5 4 3 2 1 4 1 3 2 5
//  iterate from index 5,
// so is 4, let say this is index y
// we find the ealiest index with value 4, iterating from the left, x
// then for index x + 1 to y - 1, (+1)
// then for index y put 0, because it is the 1st book

// the invariant, is that at each update, the first index with the movie id, from the left, has the correct #of books above for that movie
// when we place a movie above, all values from index x + 1 to y - 1, must +1


class SegTree {
public:
    vector<int>* tree;
    vector<int>* accu;
    int size;

    SegTree(int n) {
        tree = new vector(4 * n, 0);
        accu = new vector(4 * n, 0);
        size = n;
    }
    
    ~SegTree() {
        delete tree;
    }

    void update(int p, int s, int e, int l, int r, int add) {
        if (l > r) {
            return;
        }
        
        int m = (s + e) / 2;
        if (s == e) {
            accu->at(p) += add;
            tree->at(p) += add;
        } else if (s == l && e == r) {
            // early termination means lazy propogation
            tree->at(p) += add * (r - l + 1);
            accu->at(p) += add;
        } else if (r <= m) {
            update(2 * p + 1, s, m, l, r, add);
        } else if (l > m) {
            update(2 * p + 2, m + 1, e, l, r, add);
        } else {
            update(2 * p + 1, s, m, l, m, add);
            update(2 * p + 2, m + 1, e, m + 1, r, add);
        }
    }

    int value(int p, int s, int e, int i, int acc) {
        int m = (s + e) / 2;
        if (s == e) {
            return tree->at(p) + acc;
        } else if (i <= m) {
            return value(2 * p + 1, s, m, i, acc + accu->at(p));
        } else {
            return value(2 * p + 2, m + 1, e, i, acc + accu->at(p));
        }
    }

};

void findResult(vector<int>& requests, int n) {
    vector<int> earliest = vector(n + 1, -1);
    SegTree st(requests.size());
    for (int i = 0; i < n; i ++) {
        int m = requests[i];
        int l = earliest[m];
        earliest[m] = i;
        st.update(0, 0, st.size - 1, l + 1, i - 1, 1);
    }
    for (int i = n; i < requests.size(); i ++) {
        int m = requests[i];
        int l = earliest[m];
        earliest[m] = i;
        cout << st.value(0, 0, st.size - 1, l, 0) << " ";
        st.update(0, 0, st.size - 1, l + 1, i - 1, 1);
    }
    cout << '\n';
}

/*int main() {
    SegTree st(5);
    st.update(0, 0, st.size - 1, 1, 3, 10);
    st.update(0, 0, st.size - 1, 2, 4, 20);
    cout << st.value(0, 0, st.size - 1, 2, 0) << endl;
    st.update(0, 0, st.size - 1, 0, 4, 100);
    cout << st.value(0, 0, st.size - 1, 2, 0) << endl;
}*/

int main() {
    
    int testCases;
    cin >> testCases;
    for (int i = 0; i < testCases; i ++) {
        int m, r;
        cin >> m >> r;
        vector<int> req;
        for (int i = m; i >= 1; i --) {
            req.push_back(i);
        }
        for (int i = 0; i < r; i ++) {
            int re;
            cin >> re;
            req.push_back(re);
        }
        findResult(req, m);
    }
}