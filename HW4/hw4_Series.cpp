#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define MAX 100000000
typedef long long LL;
LL n, k;

sem_t sem[10];

struct S {
    LL x;
};
char* input = (char*)malloc(sizeof(char) * MAX + 5);
pthread_t id[10];
LL cnt[10] = {0};

void *count(void* data) {
    LL x = (LL)data;
    LL L = n * (x / (double)k);
    LL R = n * ((x + 1) / (double)k);

    // cout << L << ' ' << R << endl;

    for (LL i = L; i < R; i ++) {
        LL num = (int)(input[i] - '0');
        sem_wait(&sem[num]);
        cnt[num] ++;
        sem_post(&sem[num]);
    }
    pthread_exit(NULL);
}


int main() {
    cout << "0616015\n";
    cin >> k >> n;
    cin >> input;
    
    for (LL i = 0; i < 10; i ++)
        sem_init(&sem[i], 0, 1);

    for (LL i = 0; i < k; i ++) {
        pthread_create(&id[i], NULL, count, (void*) i);
    }

    for (LL i = 0; i < k; i ++) {
        pthread_join(id[i], NULL);
    }

    for (LL i = 0; i < 10; i ++) {
        cout << "The total number of " << i << " : " << cnt[i] << '\n';
    }
    return 0;
}
