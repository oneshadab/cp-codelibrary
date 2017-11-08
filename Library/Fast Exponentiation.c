#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int expo(int a, int b){
    int res = 1;

    while (b){
        if (b & 1) res = (long long)res * a % MOD;
        a = (long long)a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long expo(int x, int n, int m){
    if (!n) return (1 % m);
    else if (n & 1) return ((expo(x, n - 1, m) * x) % m);
    else{
        long long r = expo(x, n >> 1, m);
        return ((r * r) % m);
    }
}

long long expo(long long x, long long n, long long m){
    if (!n) return (1LL % m);
    else if (n & 1LL) return ((expo(x, n - 1, m) * x) % m);
    else{
        long long r = expo(x, n >> 1LL, m);
        return ((r * r) % m);
    }
}

long long expo(long long x, long long n, long long m){
    x %= m;
    long long res = 1;

    while (n){
        if (n & 1LL) res = (res * x) % m;
        x = (x * x) % m;
        n >>= 1LL;
    }

    return (res % m);
}

int expo(long long int x, int n, int m){
    x %= m;
    long long res = 1;

    while (n){
        if (n & 1) res = (res * x) % m;
        x = (x * x) % m;
        n >>= 1;
    }

    return (res % m);
}

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

long long expo(long long x, long long n){
    x %= MOD;
    long long res = 1;

    while (n){
        if (n & 1LL) res = (res * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1LL;
    }

    return (res % MOD);
}

int main(){
}

