/// Petr Mitrichev Contest 10, Problem F Hash
/// Given a polynomial hash function with base b and mod m, find two bit strings such that their hash is same
/// 2 <= b <= m - 2 and 4 <= m <= 10^14

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

long long b, m, expo[67], dp[4][1 << 16];

long long multiply(long long a, long long b, long long m){
    long long res = 0;
    while (b){
        if (b & 1) res = (res + a) % m;
        a = (a << 1) % m, b >>= 1;
    }
    return res;
}

long long hash(unsigned long long x){
    int i = 0;
    long long h = 0;
    while (x){
        h += dp[i++][x & 65535];
        x >>= 16;
    }
    return (h % m) ^ 0x6663E5667CC492E5LL;
}

void print(long long x){
    int i;
    for (i = 63; i >= 0; i--) printf("%d", (x & (1LL << i)) ? 1 : 0);
    puts("");
}

int main(){
    int i, j, k;
    long long u, v, x, y, s;

    while (scanf("%lld %lld", &b, &m) != EOF){
        if (b == 0 && m == 0) break;

        for (expo[0] = 1, i = 1; i < 64; i++) expo[i] = multiply(expo[i - 1], b, m);
        for (i = 0; i < 4; i++){
            for (j = 0; j < (1 << 16); j++){
                dp[i][j] = 0;
                for (k = 0; k < 16; k++){
                    dp[i][j] += expo[16 * i + k];
                    if (j & (1 << k)) dp[i][j] += expo[16 * i + k];
                    dp[i][j] %= m;
                }
            }
        }

        x = y = s = 29996224275833LL;
        while (1){
            x = hash(x);
            y = hash(hash(y));
            if (x == y) break;
        }

        while (x != s){
            u = hash(x), v = hash(s);
            if (u == v) break;
            x = u, s = v;
        }

        print(x);
        print(s);
        assert(u == v && x != s);
    }
    return 0;
}
