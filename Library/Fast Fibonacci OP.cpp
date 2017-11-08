#include <bits/stdtr1c++.h>

#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

namespace fib{ /// hash = 275701
    unsigned T[64][2][2], dp[8][256][2][2];

    inline unsigned mul(unsigned A[2][2], unsigned B[2][2]){
        unsigned C[2][2];
        C[0][0] = ((unsigned long long)A[0][0] * B[0][0] + (unsigned long long)A[0][1] * B[1][0]) % MOD;
        C[0][1] = ((unsigned long long)A[0][0] * B[0][1] + (unsigned long long)A[0][1] * B[1][1]) % MOD;
        C[1][0] = ((unsigned long long)A[1][0] * B[0][0] + (unsigned long long)A[1][1] * B[1][0]) % MOD;
        C[1][1] = ((unsigned long long)A[1][0] * B[0][1] + (unsigned long long)A[1][1] * B[1][1]) % MOD;
        A[0][0] = C[0][0], A[0][1] = C[0][1], A[1][0] = C[1][0], A[1][1] = C[1][1];
    }

    /// n'th fibonacci number, 0, 1, 1, 2, 3, 5, 8, 13....
    inline unsigned fast_fibonacci(unsigned long long n){ /// 0.15 s for 10^6 random 64 bit numbers in Codeforces
        if (n <= 1) return n % MOD;

        n -= 2;
        unsigned i = 0, mask, ar[2][2] = {1, 0, 0, 1};
        while (n){
            mask = n & 255;
            if (mask) mul(ar, dp[i][mask]);
            i++, n >>= 8;
        }
        return (ar[0][0] + ar[0][1]) % MOD;
    }

    /// n and n + 1'th fibonacci number as pair, {0, 1}, {1, 1}, {1, 2}, {2, 3}....
    inline pair<int, int> fast_fibonacci2(unsigned long long n){
        if (n == 0) return make_pair(0, 1 % MOD);
        if (n == 1) return make_pair(1 % MOD, 1 % MOD);

        n--;
        unsigned i = 0, mask, ar[2][2] = {1, 0, 0, 1};
        while (n){
            mask = n & 255;
            if (mask) mul(ar, dp[i][mask]);
            i++, n >>= 8;
        }
        return make_pair((ar[1][0] + ar[1][1]) % MOD, (ar[0][0] + ar[0][1]) % MOD);
    }

    inline void build(){ /// must call build() to initialize before anything
        int i, j, k, l, mask;
        T[0][0][0] = 1, T[0][0][1] = 1, T[0][1][0] = 1, T[0][1][1] = 0;

        for (i = 1; i < 64; i++){
            T[i][0][0] = T[i - 1][0][0], T[i][0][1] = T[i - 1][0][1];
            T[i][1][0] = T[i - 1][1][0], T[i][1][1] = T[i - 1][1][1];
            mul(T[i], T[i]);
        }

        for (i = 0, j = 0; i < 64; j++, i += 8){
            dp[j][0][0][0] = 1, dp[j][0][0][1] = 0, dp[j][0][1][0] = 0, dp[j][0][1][1] = 1;

            for (mask = 1; mask < 256; mask++){
                k = __builtin_ctz(mask), l = mask ^ (1 << k);
                dp[j][mask][0][0] = dp[j][l][0][0], dp[j][mask][0][1] = dp[j][l][0][1];
                dp[j][mask][1][0] = dp[j][l][1][0], dp[j][mask][1][1] = dp[j][l][1][1];
                mul(dp[j][mask], T[i + k]);
            }
        }
    }
}

int main(){
    int i, j, k, l, n, r;
    fib::build();

    for (i = 0; i <= 10; i++){
        pair <int, int> p = fib::fast_fibonacci2(i);
        printf("%d = %d %d\n", i, p.first, p.second);
    }

    n = 1000000;
    vector <long long> v;
    for (i = 0; i < n; i++){
        long long x = ran(1, 1000000000);
        long long y = ran(1, 1000000000);
        long long z = x << 31 ^ y;
        for (j = 0; j < 17; j++){
            k = ran(0, 62);
            z ^= (1LL << k);
        }

        v.push_back(z);
    }

    clock_t start = clock();
    unsigned long long h = 0;
    for (i = 0; i < v.size(); i++) h = (h * 1000000009) + fib::fast_fibonacci(v[i]);

    dbg(h);
    fprintf(stderr, "%0.6f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
