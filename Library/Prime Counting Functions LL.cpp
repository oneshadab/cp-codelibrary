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

namespace pcf{ /// Prime counting function
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

    long long phi(long long m, int n){ /// Returns the number of primes not greater than m
        if (n == 0) return m;
        if (primes[n - 1] >= m) return 1;
        if (m < MAXM && n < MAXN) return dp[n][m];
        return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);
    }

    long long Legendre(long long m){
        if (m < MAX) return counter[m];
        int lim = sqrt(0.9 + m);
        return phi(m, counter[lim]) + counter[lim] - 1;
    }

    long long Lehmer(long long m){ /// Returns the number of primes not greater than m
        if (m < MAX) return counter[m];

        int i, j, a, b, c, lim;
        b = sqrt(0.9 + m), c = Lehmer(cbrt(0.9 + m)), a = Lehmer(sqrt(0.9 + b)), b = Lehmer(b);

        long long res = phi(m, a) + (( (long long)(b + a - 2) * (b - a + 1)) >> 1);
        for (i = a; i < b; i++){
            long long w = m / primes[i];
            lim = Lehmer(sqrt(0.9 + w)), res -= Lehmer(w);
            for (j = i; j < lim && i <= c; j++) res = res + j - Lehmer(w / primes[j]);
        }

        return res;
    }
}

int main(){
    pcf::init();
    dbg(pcf::Lehmer(1e11)); /// 4118054813
    return 0;
}
