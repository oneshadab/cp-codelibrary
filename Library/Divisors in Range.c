#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SQR 10001
#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

short P[MAX];
int L[MAX], ar[MAX];

void Generate(){
    int i, j, d, x, y;

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
        if (L[i] == i) ar[i] = 2;
        else{
            x = i, y = 1;
            while (L[x] == L[i]){
                y++;
                x /= L[i];
            }
            ar[i] = (ar[x] * y);
        }
    }
}

int main(){
    Generate();
    int t, n, i, r;
    long long sum = 0;
    return 0;
}
