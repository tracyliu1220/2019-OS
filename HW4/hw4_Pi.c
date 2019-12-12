#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

#define MAX 100000000
#define INTERVAL 100000L
typedef long long LL;
LL n, k;

sem_t sem;

pthread_t id[10];
LL cnt[10] = {0};
LL total = 0;

void *count(void* data) {
    LL x = (LL)data;

    unsigned int seed = time(NULL) + x * x * 100000;
    double rand_x;
    double rand_y;
    LL _cnt = 0;

    LL _sample = n / k;
    while (_sample --) {
        rand_x = (double)(rand_r(&seed) % (INTERVAL + 1)) / INTERVAL;
        rand_y = (double)(rand_r(&seed) % (INTERVAL + 1)) / INTERVAL;
        if (rand_x * rand_x + rand_y * rand_y < 1)
            _cnt ++;
    }

    cnt[x] = _cnt;

    sem_wait(&sem);
    total += _cnt;
    sem_post(&sem);

    pthread_exit(NULL);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << "0616015" << endl;
    cin >> k >> n;
    
    sem_init(&sem, 0, 1);

    for (LL i = 0; i < k; i ++) {
        pthread_create(&id[i], NULL, count, (void*) i);
    }

    for (LL i = 0; i < k; i ++) {
        pthread_join(id[i], NULL);
    }

    LL _total = 0;
    for (LL i = 0; i < k; i ++) {
        cout << "Thread " << i << ", There are " << cnt[i] << " points in the circle\n";
        _total += cnt[i];
    }
    // printf("Pi : %lf\n", (double)(total * 4) / n);
    cout << "Pi : " << fixed << setprecision(6) << (double)(total * 4) / n << '\n';

    return 0;
}
