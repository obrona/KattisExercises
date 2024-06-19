#include <iostream>
using namespace std;

// idea: range of values is from 3 to 2n - 1, total of 2n - 3 values
// if n - 1 <= m <= 2n - 3 always possible
// if not, impossible
void print(int n) {
    if (n % 2 == 0) {
        cout << n / 2 - 1 << " " << n / 2 + 1 << '\n';
    } else {
        cout << n / 2 << " " << n / 2 + 1 << '\n';
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    if (m < n - 1 or m > 2 * n - 3) {
        cout << -1 << '\n';
    } else {
        int count = 0;
        while (m > 0) {
            if (count < n - 1) {
                cout << 1 << " " << count + 2 << '\n';
                count += 1;
                m --;
            } else {
                print(count + 3);
                count += 1;
                m --;
            }
        }
    }
    return 0;

}