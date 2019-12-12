#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(time(NULL));
    int k = 1;
    int n = 100000000;

    cout << k << '\n';
    cout << n << '\n';

    for (int i = 0; i < n; i ++)
        cout << rand() % 10;
    cout << '\n';
}
