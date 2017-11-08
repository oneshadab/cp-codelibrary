#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000010
#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

bool prime[MAX];
int p, len, P[MAX], counter[MAX];

void Sieve(){
    clr(prime);
    int i, j, d;
    const int sqr = ;

    prime[2] = true;
    for (i = 3; i < MAX; i++, i++) prime[i] = true;

    for (i = 3; i < sqr;){
        d = i << 1;
        for (j = (i * i); j < MAX; j += d) prime[j] = false;

        i++, i++;
        while (!prime[i]) i++, i++;
    }

    p = 0;
    for (i = 0; i < MAX; i++){
        if (prime[i]) P[p++] = i;
    }
}

void factorize(int n, bool add){
    int i, j, c, x;

    prime[1] = true;
    for (i = 0; i < p; i++){
        if (prime[n]) break;

        c = 0, x = P[i];
        while ((n % x) == 0){
            n /= x;
            c++;
        }

        if (add) counter[x] += c;
        else counter[x] -= c;
    }

    if (n > 1){
        if (add) counter[n]++;
        else counter[n]--;
    }
}

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
    int i, x;
    clr(counter);

    if ((n - k) > k) k = (n - k);
    for (i = k + 1; i <= n; i++) factorize(i, true);
    for (i = 2; i <= (n - k); i++) factorize(i, false);

    long long res = 1;
    for (i = 0; i < p; i++){
        x = P[i];
        if (x > n) break;
        if (counter[x]) res = (res * expo(x, counter[x])) % MOD;
    }

    return res;
}

int main(){
    Sieve();
    int n, k;

    while (scanf("%d %d", &n, &k) != EOF){
        clr(counter);
        long long res = binomial(n, k);
        printf("%lld\n", res);
    }
    return 0;
}
