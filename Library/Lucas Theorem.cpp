#include <bits/stdtr1c++.h>

#define MAXP 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/// Lucas theorem to calculate binomial co-efficients modulo a prime

namespace lc{
    int MOD = 1000000007;
    int fact[MAXP], inv[MAXP];

    /// Call once with the modulo prime
    void init(int prime){
        MOD = prime;
        fact[0] = 1, inv[MOD - 1] = MOD - 1;
        for (int i = 1; i < MOD; i++) fact[i] = ((long long)fact[i - 1] * i) % MOD;
        for (int i = MOD - 2; i >= 0; i--) inv[i] = ((long long)inv[i + 1] * (i + 1)) % MOD;
    }

    inline int count(int n, int k){
        if (k > n) return 0;
        int x = ((long long)inv[n - k] * inv[k]) % MOD;
        return ((long long)x * fact[n]) % MOD;
    }

    /// Lucas theorem, calculates binomial(n, k) modulo MOD, MOD must be a prime
    inline int binomial(long long n, long long k){
        if (k > n) return 0;

        int res = 1;
        while (k){
            res = ((long long)res * count(n % MOD, k % MOD)) % MOD;
            n /= MOD, k /= MOD;
        }
        return res;
    }
}

int main(){
    lc::init(997);
    printf("%d\n", lc::binomial(10, 5));
    printf("%d\n", lc::binomial(1996, 998));
    return 0;
}
