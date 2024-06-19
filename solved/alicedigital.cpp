#include <vector>
#include <iostream>
using namespace std;

class Solver {
public:
    vector<int>* array;
    

    Solver(vector<int>& a) {
        array = &a;
    }

    void p(vector<int> a) {
        for (int i = 0; i < a.size(); i ++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }

    vector<int> findIndexes(int m) {
        vector<int> out;
        out.push_back(-1);
        for (int i = 0; i < array->size(); i ++) {
            //cout << array->at(i) << " " << (array->at(i) == m) << endl;
            if (array->at(i) == m) {
                //cout << i << endl;
                out.push_back(i);
            }
        }
        out.push_back(array->size());
        return out;
    }

    int maxWeight(int m) {
        vector<int>&& indexes = findIndexes(m);
        //p(indexes);
        int maxRes = -1;
        for (int i = 1; i < indexes.size() - 1; i ++) {
            int currI = indexes[i];
            int sum = m;
            for (int a = currI - 1; a > indexes[i - 1]; a --) {
                if (array->at(a) >= m) {
                    sum += array->at(a);
                } else {
                    break;
                }
            }
            for (int a = currI + 1; a < indexes[i + 1]; a ++) {
                if (array->at(a) >= m) {
                    //cout << i << " ";
                    sum += array->at(a);
                } else {
                    break;
                }
            }
            //cout << endl;
            maxRes = max(maxRes, sum);
        }
        return maxRes;
    }

};

int main() {
    int n;
    cin >> n;
    vector<int> res;
    for (int i = 0; i < n; i ++) {
        int s, m;
        cin >> s >> m;
        vector<int> array;
        for (int j = 0; j < s; j ++) {
            int num;
            cin >> num;
            array.push_back(num);
        }
        Solver sol(array);
        res.push_back(sol.maxWeight(m));
    }
    for (int i = 0; i < n; i ++) {
        cout << res[i] << '\n';
    }

}