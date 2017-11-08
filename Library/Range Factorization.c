#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SQR 7071
#define MAX 50000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int L[MAX];
short P[MAX];

/*******************************************************
* P[0] = P[1] = 1, P[p] = 0 if p is a prime
* Otherwise, P[i] = the smallest prime factor if i
* L[0] = L[1] = 1, L[i] = the largest prime factor of i
********************************************************/

void Generate(){
    int i, j, d, x;

    P[0] = P[1] = L[0] = L[1] = 1;
    for (i = 4; i < MAX; i++, i++) P[i] = 2;

    for (i = 3; i < SQR; i++, i++){
        if (!P[i]){
            d = i << 1;
            for (j = (i * i); j < MAX; j += d){
                if (!P[j]) P[j] = i;
            }
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
}

int main(){
}
