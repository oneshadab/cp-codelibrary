#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

const unsigned long long base = 1968647011ULL;

int n, ar[MAX];
unsigned long long P[MAX];

void RollingHash(int len, bool gen){
    int i, j;
    unsigned long long h = 0, x;

    if (gen){
        P[0] = 1ULL;
        for (i = 1; i < MAX; i++) P[i] = (P[i - 1] * base);
    }

    for (i = 0; i < len; i++) h = (h * base) + ar[i];
    for (i = 0; (i + len) <= n; i++){
        /* h contains required hash value now */

        x = (h - (P[len - 1] * ar[i]));
        h = (x * base) + ar[i + len];
    }
    return 0;
}

int main(){
}
