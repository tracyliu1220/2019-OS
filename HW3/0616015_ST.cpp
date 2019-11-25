#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

/* function definitions */
void _sort(vector<int> & list);

int main() {
	/* Use STDIN (e.g. scanf, cin) to take the input */
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tmp;
    vector<int> list;
    while (cin >> tmp) {
        list.push_back(tmp);
    }

	/* Do the sorting */
    _sort(list);

	/* Use STDOUT (e.g. printf, cout) to output the sorted array */
    for (int i = 0; i < list.size(); i ++) {
        cout << list[i] << ' ';
    }
    cout << '\n';

    return 0;
}

void _sort(vector<int> & list) {
	/* Sorting algorithm can be brute‐force methods, e.g., bubble sort */
    for (int i = 0; i < list.size(); i ++) {
        for (int j = i; j < list.size(); j ++) {
            if (list[i] > list[j]) swap(list[i], list[j]);
        }
    }
}
