#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 2510
#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int S[MAX][MAX], inv[MAX], factorial[MAX], bernoulli[MAX];

int expo(long long x, int n){
    x %= MOD;
    long long res = 1;

    while (n){
        if (n & 1) res = (res * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }

    return (res % MOD);
}

void Generate(){
    int i, j;
    long long x, y, z, lim = (long long)MOD * MOD;

    factorial[0] = 1;
    for (i = 1; i < MAX; i++){
        factorial[i] = ((long long) factorial[i - 1] * i) % MOD;
    }
    for (i = 0; i < MAX; i++) inv[i] = expo(i, MOD - 2);

    S[0][0] = 1;
    for (i = 1; i < MAX; i++){
        S[i][0] = 0;
        for (j = 1; j <= i; j++){
            S[i][j] = ( ((long long)S[i - 1][j] * j) + S[i - 1][j - 1]) % MOD;
        }
    }

    bernoulli[0] = 1;
    for (i = 1; (i + 1) < MAX; i++){
        if ((i & 1) && i > 1) bernoulli[i] = 0;
        else{
            x = 0, y = 0;

            for (j = 0; j <= i; j++){
                z = ((long long) factorial[j] * inv[j + 1]) % MOD;
                z = (z * S[i][j]) % MOD;
                if (j & 1) y += z;
                else x += z;
            }
            bernoulli[i] = (lim + x - y) % MOD;

        }
    }
}

int faulhaber(long long n, int k){
    n %= MOD;
    if (!k) return n;

    n++, k++;
    int i, j;
    long long p = 1, res = n;

    for (i = 1; i < k; i++){
        p = (p * (k - i + 1)) % MOD;
        p = (p * inv[i]) % MOD;
        if (bernoulli[i]) res = (res + (p * bernoulli[i])) % MOD;
        res = (res * n) % MOD;
    }
    res = (res * inv[k]) % MOD;

    return res;
}

int main(){
    Generate();
    printf("%d\n", faulhaber(10, 4));
    return 0;
}
