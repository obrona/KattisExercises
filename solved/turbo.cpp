#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class SegTree {
public:
    vector<int> tree;
    int size;

    SegTree(int n) {
        size = n;
        tree = vector(4 * size, 0);


    }

    void addRange(int p, int s, int e, int l, int r, int add) {
        if (s > e) {
            return;
        }
        int m = (s + e) / 2;
        if (s == e) {
            tree[p] += add;
        } else if (s == l && e == r) {
            tree[p] += add;
        } else if (r <= m) {
            addRange(2 * p + 1, s, m, l, r, add);
        } else if (l > m) {
            addRange(2 * p + 2, m + 1, e, l, r, add);
        } else {
            addRange(2 * p + 1, s, m, l, m, add);
            addRange(2 * p + 2, m + 1, e, m + 1, r, add);
        }
    }

    int getSum(int p, int s, int e, int i) {
        int m = (s + e) / 2;
        if (s == e) {
            return tree[p];
        } else if (i <= m) {
            return tree[p] + getSum(2 * p + 1, s, m, i);
        } else {
            return tree[p] + getSum(2 * p + 2, m + 1, e, i);
        }
    }
};

long long swaps(vector<int>& array) {
    unordered_map<int, int> map;
    for (int i = 0; i < array.size(); i ++) {
        map[array[i]] = i;
    }
    SegTree st(array.size());
    //long long count = 0;
    for (int i = 0; i < array.size(); i ++) {
        if (i % 2 == 0) {
            int num = 1 + (i / 2);
            int initpos = map[num];
            int currpos = initpos + st.getSum(0, 0, st.size - 1, initpos);
            int s = currpos - (num - 1);
            cout << s << '\n';

            st.addRange(0, 0, st.size - 1, 0, initpos - 1, 1);
            if (initpos > 22) {
                //cout << "+1" << " " << num << endl;
            }
        } else {
            int num = array.size() - (i / 2);
            int initpos = map[num];
            int currpos = initpos + st.getSum(0, 0, st.size - 1, initpos);
            int s = (num - 1) - currpos;
            if (i == 7) {
                //cout << st.getSum(0, 0, st.size - 1, initpos) << " " << initpos << " " << num << endl;
            }
            cout << s << '\n';
            if (initpos < 22) {
                //cout << "-1" <<" "<< num <<endl;
            }
            st.addRange(0, 0, st.size - 1, initpos + 1, st.size - 1, -1);
        }
    }
    return 0;
}

int main() {
    int n;
    vector<int> a;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        int num;
        cin >> num;
        a.push_back(num);
    }
    swaps(a);
   

}

/*int main() {
    vector<int> a = {10,9,8,7,6,5,4,3,2,1};
    swaps(a);
}*/