#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

long long mul(long long a, long long b, long long m){
    long long res = 0;
    long long x = (a % m);

    while (b){
        if (b & 1){
            res = res + x;
            if (res >= m) res -= m;
        }
        b >>= 1;
        x <<= 1;
        if (x >= m) x -= m;
    }

    return res;
}

long long expo(long long x, long long n, long long m){
    long long res = 1;

    while (n){
        if (n & 1) res = mul(res, x, m);
        x = mul(x, x, m);
        n >>= 1;
    }

    return (res % m);
}

int main(){

}
