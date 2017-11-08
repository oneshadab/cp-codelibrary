#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int n;
unsigned int bucket[0x100], ar[MAX + 10], temp[MAX + 10];

void radix_sort(unsigned int* ar, int n){
    int i;
    clr(bucket);
    for (i = 0; i < n; i++) bucket[ar[i] & 0xFF]++;
    for (i = 1; i < 0x100; i++) bucket[i] += bucket[i - 1];
    for (i = n - 1; i >= 0; i--) temp[--bucket[ar[i] & 0xFF]] = ar[i];
    clr(bucket);
    for (i = 0; i < n; i++) bucket[(temp[i] >> 8) & 0xFF]++;
    for (i = 1; i < 0x100; i++) bucket[i] += bucket[i - 1];
    for (i = n - 1; i >= 0; i--) ar[--bucket[(temp[i] >> 8) & 0xFF]] = temp[i];
    clr(bucket);
    for (i = 0; i < n; i++) bucket[(ar[i] >> 16) & 0xFF]++;
    for (i = 1; i < 0x100; i++) bucket[i] += bucket[i - 1];
    for (i = n - 1; i >= 0; i--) temp[--bucket[(ar[i] >> 16) & 0xFF]] = ar[i];
    clr(bucket);
    for (i = 0; i < n; i++) bucket[(temp[i] >> 24) & 0xFF]++;
    for (i = 1; i < 0x100; i++) bucket[i] += bucket[i - 1];
    for (i = n - 1; i >= 0; i--) ar[--bucket[(temp[i] >> 24) & 0xFF]] = temp[i];
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
