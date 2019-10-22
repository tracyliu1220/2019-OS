#include <bits/stdc++.h>
using namespace std;

struct P {
    int id;
    int arrival;
    int burst;
    int WT;
    int TRT;
};

int n;
vector<P> process;

bool compareByTime(P & a, P & b) {
    return (a.arrival < b.arrival) || (a.arrival == b.arrival && a.id < b.id);
}

bool compareById(P & a, P & b) {
    return a.id < b.id;
}

int main() {
    // input
    cin >> n;
    process.resize(n);
    for (int i = 0; i < n; i ++) {
        process[i].id = i + 1;
        cin >> process[i].arrival;
    }
    for (int i = 0; i < n; i ++)
        cin >> process[i].burst;

    // sort by time
    sort(process.begin(), process.end(), compareByTime);

    // simulate
    int timer = process[0].arrival;
    int totalWT = 0;
    int totalTRT = 0;
    for (int i = 0; i < n; i ++) {
        if (timer < process[i].arrival) timer = process[i].arrival;
        process[i].WT = timer - process[i].arrival;
        process[i].TRT = process[i].WT + process[i].burst;
        timer += process[i].burst;
        totalWT += process[i].WT;
        totalTRT += process[i].TRT;
    }
    
    sort(process.begin(), process.end(), compareById);

    for (int i = 0; i < n; i ++) {
        cout << process[i].WT << ' ' << process[i].TRT << '\n';
    }

    cout << totalWT << '\n';
    cout << totalTRT << '\n';
}

