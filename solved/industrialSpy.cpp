#include <vector>
#include <iostream>
#include <cmath>
#include <unordered_map>
#include <chrono>
using namespace std;



vector<int> sieve(int n) {
    vector<int> res = vector(n + 1, 1);
    int limit = (int) floor(sqrt(n));
    for (int i = 2; i <= limit; i ++) {
        if (res[i]) {
            for (int j = i * i; j <= n; j += i) {
                res[j] = 0;
            }
        }
    }
    res[1] = 0;
    res[0] = 0;
    return res;
}

vector<int>&& isPrime = sieve(10000000);

int countPrimes(string& digits, int bitMap, int numDigits, int currSum, unordered_map<int, int>& usedPrime) {
    if (numDigits == 0) {
        if (usedPrime[currSum] == 1) {
            return 0;
        } else if (isPrime[currSum]) {
            usedPrime[currSum] = 1;
            //cout << currSum << endl;
            return 1;
        } else {
            return 0;
        }
    } else {
        int sum = 0;
        for (int i = 0; i < digits.size(); i ++) {
            if (((bitMap >> i) & 1) == 0) {
                int d = digits[i] - '0';
                sum += countPrimes(digits, bitMap + (1 << i), numDigits - 1, currSum * 10 + d, usedPrime);
            }
        }
        return sum;
    }
}

int countAllPrimes(string s) {
    int sum = 0;
    unordered_map<int, int> usedPrime;
    for (int i = 1; i <= s.size(); i ++) {
        sum += countPrimes(s, 0, i, 0, usedPrime);
    }
    return sum;
}

int main() {
   int n;
   cin >> n;
   for (int i = 0; i < n; i ++) {
    string s;
    cin >> s;
    cout << countAllPrimes(s) << endl;
   }
	
   
}

