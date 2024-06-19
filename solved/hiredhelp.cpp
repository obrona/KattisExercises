#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// greedy solution, binary search
// suppose we can have k workers, clearly we can have x, x <= k workers
// how to check if can have k workers
// for each day, asign the earliest k remaining task
// why we can do so
// suppose at some step, we do not assign the task ending the earliest, and still result in optimal solution
// case 1, that earliest task is not used in resulting optimal solution
// can switch with the task replacing it
// case 2, that earliest task is used on some subsequent day to some worker
// can switch the 2 task, since this task ends later, can safely switch
// because, let the ealiest task, T,  possible at this step be done at the dth day
// deadline T >= d
// task taken instead, let it be T2, deadline T2 >= deadline T >= d
// so can safely replace

bool canKWorkers(vector<int>& sortedTasks, int numWorkers, int k) {
    if (numWorkers == 0) {
        return true;
    }
    vector<int> completed = vector<int>(numWorkers, 0);
    int day = 1;
    int w = 0;
    for (int i = 0; i < sortedTasks.size(); i ++) {
        int task = sortedTasks[i];
        if (w == numWorkers - 1) {
            if (day <= task) {
                completed[w] += 1;
                day += 1;
                w = 0;
            }
        } else {
            if (day <= task) {
                completed[w] += 1;
                w += 1;
            }
        }
    }
    for (int i = 0; i < completed.size(); i ++) {
        if (completed[i] < k) {
            return false;
        }
    }
    return true;
}

int maxWorkers(vector<int>& sortedTasks, int s, int e, int k) {
    if (s >= e) {
        return s;
    } else {
        int m = ((s + e) % 2 == 0) ? (s + e) / 2 : ((s + e) / 2) + 1;
        bool can = canKWorkers(sortedTasks, m, k);
        if (can) {
            return maxWorkers(sortedTasks, m, e, k);
        } else {
            return maxWorkers(sortedTasks, s, m - 1, k);
        }
    }
}

int main() {
    vector<int> tasks = vector<int>();
    int size, k;
    cin >> size >> k;
    for (int i = 0; i < size; i ++) {
        int task;
        cin >> task;
        tasks.push_back(task);
    }
    sort(tasks.begin(), tasks.end());
    int ans = maxWorkers(tasks, 0, size, k);
    cout << ans;

}