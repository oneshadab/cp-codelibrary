#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000010
#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

long long factorial[MAX];

long long expo(long long x, long long n){
    long long res = 1;

    while (n){
        if (n & 1LL) res = (res * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1LL;
    }

    return (res % MOD);
}

long long binomial(int n, int k){
    long long x = factorial[n];
    long long y = (factorial[k] * factorial[n - k]) % MOD;
    long long res = (x * expo(y, MOD - 2)) % MOD;
    return res;
}

int main(){
    int i, n, k;

    factorial[0] = 1LL;
    for (i = 1; i < MAX; i++) factorial[i] = (factorial[i - 1] * i) % MOD;

    while (scanf("%d %d", &n, &k) != EOF){
        long long res = binomial(n, k);
        printf("%lld\n", res);
    }
    return 0;
}
