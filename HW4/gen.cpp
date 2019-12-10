#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 100000000;
    int k = 4;
    cout << k << '\n';
    cout << n << '\n';

    for (int i = 0; i < n; i ++)
        cout << rand() % 10;
    cout << '\n';
}
