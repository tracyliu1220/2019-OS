#pragma GCC optimize("O3")
#include <iostream>
#include <algorithm>
#include <vector>
#include <pthread.h>
using namespace std;

int _L[7];
int _R[7];

struct S {
    pthread_t id1, id2;
};

int n;
vector<int> list;
pthread_t id[7];

/* function definitions */
void *_sort(void* data);
void *_merge(void* data);

int main() {
	/* Use STDIN (e.g. scanf, cin) to take the input */
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tmp;
    while (cin >> tmp) {
        list.push_back(tmp);
    }
    n = list.size();

    _L[0] = 0;
    _L[1] = _R[0] = n / 4;
    _L[2] = _R[1] = n / 2;
    _L[3] = _R[2] = n * 3 / 4;
    _R[3] = n;

    _L[4] = 0;
    _L[5] = _R[4] = n / 2;
    _R[5] = n;

	/* Do the sorting */

    struct S **args = (struct S**)malloc(sizeof(long long) * 7);
    for (int i = 0; i < 7; i ++) {
        args[i] = (struct S*)malloc(sizeof(struct S));
    }

    for (int i = 0; i < 4; i ++) {
        args[i]->id1 = i;
        pthread_create(&id[i], NULL,  _sort, (void*)args[i]);
    }


    args[4]->id1 = 0; args[4]->id2 = 1;
    args[5]->id1 = 2; args[5]->id2 = 3;
    args[6]->id1 = 4; args[6]->id2 = 5;

    for (int i = 4; i < 7; i ++)
        pthread_create(&id[i], NULL, _merge, args[i]);

    pthread_join(id[6], NULL);

	/* Use STDOUT (e.g. printf, cout) to output the sorted array */
    for (int i = 0; i < n; i ++) {
        cout << list[i] << ' ';
    }
    cout << '\n';
    return 0;
}

void *_sort(void* data) {
	/* Sorting algorithm can be brute force methods, e.g., bubble sort */
    S* ptr = (S*)data;
    int L = _L[ptr->id1];
    int R = _R[ptr->id1];
    for (int i = L; i < R; i ++) {
        for (int j = i + 1; j < R; j ++) {
            if (list[i] > list[j]) swap(list[i], list[j]);
        }
    }
}

void *_merge(void* data) {
    S* ptr = (S*)data;
    int id1 = ptr->id1;
    int id2 = ptr->id2;

    pthread_join(id[id1] ,NULL);
    pthread_join(id[id2] ,NULL);
    
    vector<int> sorted;

    int i = _L[id1];
    int j = _L[id2];

    while (i < _R[id1] && j < _R[id2]) {
        if (list[i] < list[j])
            sorted.push_back(list[i++]);
        else
            sorted.push_back(list[j++]);
    }

    while (i < _R[id1])
        sorted.push_back(list[i++]);
    while (j < _R[id2])
        sorted.push_back(list[j++]);

    for (int i = 0; i < _R[id2] - _L[id1]; i ++) {
        list[_L[id1] + i] = sorted[i];
    }
}
