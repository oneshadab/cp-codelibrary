#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SQR 317
#define LEN 9777
#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))

int p, prime[LEN];
int len, P[50], C[50], d, div[10010];
unsigned int ar[(MAX >> 6) + 5] = {0};

void Sieve(){
    int i, j, k;
    setbit(ar, 0), setbit(ar, 1);

    for (i = 3; i < SQR; i++, i++){
        if (!chkbit(ar, i)){
            k = i << 1;
            for (j = (i * i); j < MAX; j += k) setbit(ar, j);
        }
    }

    p = 0;
    prime[p++] = 2;
    for (i = 3; i < MAX; i++, i++){
        if (isprime(i)) prime[p++] = i;
    }
}

int Factorize(int* P, int* C, int n){
    int i, j, k, x, c;

    len = 0;
    for (i = 0; i < p; i++){
        x = prime[i];
        if ((x * x) > n) break;

        c = 0;
        while (!(n % x)){
            n /= x;
            c++;
        }

        if (c){
            P[len] = x;
            C[len++] = c;
            c = 0;
        }
    }
    if (n > 1){
        P[len] = n;
        C[len++] = 1;
    }

    return len;
}

void backtrack(int i, int j, int x){
    if (i == len){
        div[d++] = x;
        return;
    }

    backtrack(i + 1, 0, x);
    if (j < C[i]) backtrack(i, j + 1, x * P[i]);
}

int Divisors(int n){
    d = 0;
    Factorize(P, C, n);
    backtrack(0, 0, 1);
    return d;
}

int main(){
    Sieve();
    return 0;
}
