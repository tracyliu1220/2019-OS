#include <bits/stdc++.h>
using namespace std;

struct P {
    int id;
    int prior;
    int arrival;
    int burst;
    int last;
    bool operator>(const P & rhs) const {
        return (prior > rhs.prior) || 
               (prior == rhs.prior && last > rhs.last) ||
               (prior == rhs.prior && last == rhs.last && id > rhs.id);
    }
};

int n;
vector<P> process;
vector<int> WT;
vector<int> TRT;

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
    WT.resize(n);
    TRT.resize(n);

    for (int i = 0; i < n; i ++) {
        process[i].id = i;
        cin >> process[i].arrival;
        process[i].last = process[i].arrival;
    }
    for (int i = 0; i < n; i ++)
        cin >> process[i].burst;
    for (int i = 0; i < n; i ++)
        cin >> process[i].prior;

    // sort by time
    sort(process.begin(), process.end(), compareByTime);
    priority_queue<P, vector<P>, greater<P> > q;
    int ptr = 0;

    // simulate
    int timer = 0;
    int totalWT = 0;
    int totalTRT = 0;
    
    // simulate
    while (ptr != n || q.size()) {
        while (process[ptr].arrival <= timer && ptr < n) {
            q.push(process[ptr]);
            ptr ++;
        }
        if (q.size() == 0) {
            timer ++;
            continue;
        }
        P cur = q.top(); q.pop();
        int idx = cur.id;
        WT[idx] += timer - cur.last;

        timer ++;
        cur.last = timer;
        cur.burst --;
        if (cur.burst) {
            q.push(cur);
        } else {
            TRT[idx] = timer - cur.arrival;
        }
    }

    // output
    for (int i = 0; i < n; i ++) {
        cout << WT[i] << ' ' << TRT[i] << '\n';
        totalWT += WT[i];
        totalTRT += TRT[i];
    }

    cout << totalWT << '\n';
    cout << totalTRT << '\n';
}

