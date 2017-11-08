#include <bits/stdtr1c++.h>

#define MAXN 100
#define MAXM 100010
#define MAXP 666666
#define MAX 10000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))

using namespace std;

namespace pcf{
    long long dp[MAXN][MAXM];
    unsigned int ar[(MAX >> 6) + 5] = {0};
    int len = 0, primes[MAXP], counter[MAX];

    void Sieve(){
        setbit(ar, 0), setbit(ar, 1);
        for (int i = 3; (i * i) < MAX; i++, i++){
            if (!chkbit(ar, i)){
                int k = i << 1;
                for (int j = (i * i); j < MAX; j += k) setbit(ar, j);
            }
        }

        for (int i = 1; i < MAX; i++){
            counter[i] = counter[i - 1];
            if (isprime(i)) primes[len++] = i, counter[i]++;
        }
    }

    void init(){
        Sieve();
        for (int n = 0; n < MAXN; n++){
            for (int m = 0; m < MAXM; m++){
                if (!n) dp[n][m] = m;
                else dp[n][m] = dp[n - 1][m] - dp[n - 1][m / primes[n - 1]];
            }
        }
    }

    /// Count of numbers not greater than m and not divisible by any of the first n primes
    long long phi(long long m, int n){
        if (n == 0) return m;
        if (primes[n - 1] >= m) return 1;
        if (m < MAXM && n < MAXN) return dp[n][m];
        if ((long long)primes[n - 1] * primes[n - 1] >= m && m < MAX) return counter[m] - n + 1;

        if ((long long)primes[n - 1] * primes[n - 1] * primes[n - 1] >= m && m < MAX){
            int lim = counter[(int)sqrt(m + 0.95)];
            long long res = counter[m] - (((lim + n - 2) * (lim - n + 1 )) >> 1);
            for (int i = n; i < lim; i++) res += counter[m / primes[i]];
            return res;
        }

        return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
    }

    long long Legendre(long long m){ /// Returns the number of primes not greater than m
        if (m < MAX) return counter[m];
        int lim = sqrt(0.9 + m);
        return phi(m, counter[lim]) + counter[lim] - 1;
    }

    long long Lehmer(long long m){ /// Returns the number of primes not greater than m
        if (m < MAX) return counter[m];

        long long w, res = 0;
        int i, a, s, c, x, y;
        s = sqrt(0.9 + m), y = c = cbrt(0.9 + m);
        a = counter[y], res = phi(m, a) + a - 1;
        for (i = a; primes[i] <= s; i++) res = res - Lehmer(m / primes[i]) + Lehmer(primes[i]) - 1;
        return res;
    }
}

int main(){
    pcf::init();
    clock_t start = clock();
    dbg(pcf::Lehmer(1e12)); /// 37607912018
    printf("%0.3f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC)); /// 0.422
    start = clock();
    dbg(pcf::Legendre(1e12)); /// 37607912018
    printf("%0.3f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC)); /// 1.079
    return 0;
}
