#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MOD 1007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

long long mul(long long a, long long b){
    long long res = 0;

    while (b){
        if (b & 1LL) res = (res + a) % MOD;
        a = (a << 1LL) % MOD;
        b >>= 1LL;
    }

    return res;
}

long long mul(long long a, long long b){
   if ((MOD < 3037000500LL)) return ((a * b) % MOD);
   long double res = a;
   res *= b;
   long long c = (long long)(res / MOD);
   a *= b;
   a -= c * MOD;
   if (a >= MOD) a -= MOD;
   if (a < 0) a += MOD;
   return a;
}

long long binary_div(long long a, long long b){ /* (a + b) / 2 without overflow */
    long long x = (a >> 1LL), y = (b >> 1LL);
    long long res = x + y;
    if ((a & 1) && (b & 1)) res++;
    return res;
}




const long long LIM = LLONG_MAX;

uint64_t mul(uint64_t a, uint64_t b){
    a %= MOD, b %= MOD;
    if (a > b) swap(a, b);
    if (!a) return 0;
    if (a < (LIM / b)) return ((a * b) % MOD);

    uint64_t res = 0;
    int x, k = min(30, __builtin_clzll(MOD) - 1);
    int bitmask = (1 << k) - 1;

    while (a > 0){
        x = a & bitmask;
        res = (res + (b * x)) % MOD;
        a >>= k;
        b = (b << k) % MOD;
    }
    return res;
}

/// Not sure, morris vesion
long long mul(long long a, long long b, long long MOD) {
    long long x = (long long)((double)a * b / MOD + 0.5);
    long long res = ((a * b) - (x * MOD)) % MOD;
    if (res < 0) res += MOD;
    return res;
}

int main(){
}
