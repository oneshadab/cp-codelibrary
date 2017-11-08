#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

long long n, MOD = 1000000007;

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

/*** Fast Doubling Algorithm to calculate n'th fibonacci number ***/
/*** fib(0) = 0, fib(1) = 1, fib(n) = fib(n - 1) + fib(n - 2) ***/

inline long long fib(long long& x, long long& y, long long n){
    if (!n) x = 0, y = 1;
    else{
        long long a, b;
        fib(a, b, n >> 1);
        long long z = (b << 1) - a;
        if (z < 0) z += MOD;

        x = mul(a, z);
        y = mul(a, a) + mul(b, b);
        if (y >= MOD) y -= MOD;

        if (n & 1){
            x += y;
            if (x >= MOD) x -= MOD;
            x ^= y ^= x ^= y;
        }
    }
    return x;
}

inline long long fib(long long n){
    long long x = 0, y = 1;
    return fib(x, y, n);
}

int main(){
    while (scanf("%lld %lld", &n, &MOD) != EOF){
        printf("%lld\n", fib(n));
    }
    return 0;
}
