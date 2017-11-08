#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LEN 78777
#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))

int p, prime[LEN];
long long div[7001];
unsigned int ar[(MAX >> 6) + 5] = {0};

int compare(const void* a, const void* b){
    long long x = (*(long long*)a);
    long long y = (*(long long*)b);
    if (x == y) return 0;
    return ((x < y) ? -1 : 1);
}

void Sieve(){
    int i, j, k;
    setbit(ar, 0), setbit(ar, 1);

    for (i = 3; (i * i) < MAX; i++, i++){
        if (!chkbit(ar, i)){
            for (j = (i * i), k = i << 1; j < MAX; j += k) setbit(ar, j);
        }
    }

    for (i = 3, prime[0] = 2, p = 1; i < MAX; i++, i++){
        if (isprime(i)) prime[p++] = i;
    }
}

int divisors(long long x){
    int i, j, l, k, c, len = 0;
    for (i = 0, div[len++] = 1; i < p; i++){
        if ((long long)prime[i] * prime[i] > x) break;
        c = 0, k = len;
        while (!(x % prime[i])) c++, x /= prime[i];
        long long y = prime[i];
        for (j = 0; j < c; j++, y *= prime[i]){
            for (l = 0; l < k; l++) div[len++] = y * div[l];
        }
    }

    for (j = 0, k = len; j < k && x > 1; j++) div[len++] = div[j] * x;
    qsort(div, len, sizeof(long long), compare);
    return len;
}


int main(){
    Sieve();
    int i, j, k, x = divisors(2 * 3 * 5 * 21);
    printf("%d\n", x);
    for (i = 0; i < x; i++) printf("%lld\n", div[i]);
    return 0;
}
