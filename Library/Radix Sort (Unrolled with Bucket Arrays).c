#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int n;
unsigned int bucket[4][0x100], ar[MAX + 10], temp[MAX + 10];

void radix_sort(unsigned int* ar, int n){ /// hash = 639510
    int i;
    clr(bucket);
    for (i = 0; i < n; i++){
        bucket[0][ar[i] & 0xFF]++;
        bucket[1][(ar[i] >> 8) & 0xFF]++;
        bucket[2][(ar[i] >> 16) & 0xFF]++;
        bucket[3][(ar[i] >> 24) & 0xFF]++;
    }
    for (i = 1; i < 0x100; i++){
        bucket[0][i] += bucket[0][i - 1];
        bucket[1][i] += bucket[1][i - 1];
        bucket[2][i] += bucket[2][i - 1];
        bucket[3][i] += bucket[3][i - 1];
    }

    for (i = n - 1; i >= 0; i--) temp[--bucket[0][ar[i] & 0xFF]] = ar[i];
    for (i = n - 1; i >= 0; i--) ar[--bucket[1][(temp[i] >> 8) & 0xFF]] = temp[i];
    for (i = n - 1; i >= 0; i--) temp[--bucket[2][(ar[i] >> 16) & 0xFF]] = ar[i];
    for (i = n - 1; i >= 0; i--) ar[--bucket[3][(temp[i] >> 24) & 0xFF]] = temp[i];
}

int main(){
    n = MAX;
    srand(time(0));
    int i, j, k, x, y;

    for (i = 0; i < n; i++) ar[i] = (rand() * rand());
    clock_t start = clock();
    radix_sort(ar, n);
    printf("%0.5f s\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
