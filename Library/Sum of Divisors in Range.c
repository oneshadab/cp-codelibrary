#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SQR 10001
#define MAX 100000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

short P[MAX];
int L[MAX], ar[MAX];

void Generate(){
    int i, j, k, l, d, x, y, z, p;

    P[0] = P[1] = L[0] = L[1] = 1;
    for (i = 4; i < MAX; i++, i++) P[i] = 2;

    for (i = 3; i < SQR; i++, i++){
        if (!P[i]){
            d = i << 1;
            for (j = (i * i); j < MAX; j += d) P[j] = i;
        }
    }

    for (i = 2; i < MAX; i++){
        if (!P[i]) L[i] = i;
        else{
            L[i] = P[i];
            x = L[i /P[i]];
            if (x > L[i]) L[i] = x;
        }
    }

    ar[0] = 0, ar[1] = 1;
    for (i = 2; i < MAX; i++){
        if (L[i] == i) ar[i] = i + 1;
        else{
            x = i, y = 1, p = L[i];
            while (L[x] == L[i]){
                y += p;
                x /= L[i], p *= L[i];
            }
            ar[i] = (ar[x] * y);
        }
    }
}

int main(){
    Generate();
    int t, n, i, r;
    return 0;
}
