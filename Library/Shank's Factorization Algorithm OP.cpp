#include <bits/stdtr1c++.h>

#define MAX 1000010
#define isprime(x) prm::miller_rabin(x)
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

namespace prm{
    bitset <MAX> flag;
    long double op = 0.0;
    int p = 0, prime[78777];
    const int base[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    void Sieve(){
        int i, j, x;
        for (i = 3; i < MAX; i += 2) flag[i] = true;
        for (i = 3, flag[2] = true; (i * i) < MAX; i += 2){
            if (flag[i]){
                for (j = (i * i), x = i << 1; j < MAX; j += x){
                    flag[j] = false;
                }
            }
        }

        for (i = 2; i < MAX; i++){
            if (flag[i]) prime[p++] = i;
        }
    }

    void init(){
        if (!flag[2]) Sieve();
    }

    inline long long mul(long long a, long long b, long long MOD){
       if ((MOD < 3037000500LL)) return ((a * b) % MOD);
       long double res = a;
       res *= b;
       long long c = (long long)(res * op);
       a *= b;
       a -= c * MOD;
       if (a >= MOD) a -= MOD;
       if (a < 0) a += MOD;
       return a;
    }

    inline long long expo(long long x, long long n, long long m){
        long long res = 1;

        while (n){
            if (n & 1) res = mul(res, x, m);
            x = mul(x, x, m);
            n >>= 1;
        }

        return (res % m);
    }

    inline bool miller_rabin(long long p){
        if (p < MAX) return flag[p];
        if ((p + 1) & 1) return false;
        for (int i = 1; i < 10; i++){ /// basic iterations
            if (!(p % prime[i])) return false;
        }

        long long a, m, x, s = p - 1, y = p - 1;
        op = (long double)1 / p, s = s >> __builtin_ctzll(s);

        for (int i = 0; i < 7; i++) {
            x = s, a = (base[i] % y) + 1;
            m = expo(a, x, p);
            while ((x != y) && (m != 1) && (m != y)) m = mul(m, m, p), x <<= 1;
            if ((m != y) && !(x & 1)) return false;
        }
        return true;
    }

    /// n cannot be a prime or a square number
    /// Returns one factor of n, k = base multiplier for convergence
    /// Returns 1 on failure, try with next value of k. Returns 0 if not possible to factor due to overflow
    inline unsigned long long shanks(unsigned long long n, int k){
        int i, j, u, v;
        unsigned long long m, b, x, g, s, P[2], Q[2];

        m = n * k;
        if ((m / n) != k) return 0;
        s = sqrt((long double)m + 0.975);
        Q[0] = 1, P[0] = s, Q[1] = m - (P[0] * P[0]);

        for (i = 1; ;i++){
            u = i & 1, v = (i + 1) & 1;
            if (v){
                x = sqrt((long double)Q[u] + 0.95);
                if ((x * x) == Q[u]){
                    b = (s - P[v]) / x;
                    P[0] = (b * x) + P[v];
                    Q[0] = x, Q[1] = (m - P[0] * P[0]) / Q[0];
                    break;
                }
            }

            b = (s + P[v]) / Q[u];
            P[u] = (b * Q[u]) - P[v];
            Q[v] = Q[v] + (b * (P[v] - P[u]));
        }


        for (i = 1; ;i++){
            u = i & 1, v = (i + 1) & 1;
            b = (s + P[v]) / Q[u];
            P[u] = (b * Q[u]) - P[v];
            Q[v] = Q[v] + (b * (P[v] - P[u]));
            if (P[u] == P[v]) break;
        }

        g = __gcd(n, P[u]);
        return ((g == 1 || g == n) ? 1 : g);
    }

    inline long long countdiv(long long n){
        int i, j, c;
        long long x, res = 1;
        for (i = 0; i < p; i++){
            x = prime[i];
            if ((x * x * x) > n) break;

            c = 1;
            while (!(n % x)) c++, n /= x;
            if (c > 1){
                res *= c;
                if (miller_rabin(n)){
                    res <<= 1, n = 1;
                    break;
                }
            }
        }

        if (n > 1 && miller_rabin(n)) res <<= 1;
        else if (n > 1) {
            x = sqrt((long double)0.975 + n);
            if ((x * x) == n && miller_rabin(x)) res *= 3;
            else res <<= 2;
        }

        return res;
    }

    inline vector <long long> factorize(long long n){ /// Works well for n <= 10^17
        long long x;
        vector <long long> factors;

        for (int i = 0, c = 0; i < p; i++){
            c = 0, x = prime[i];
            if ((x * x * x) > n) break;

            while (!(n % x)){
                n /= x, c++;
                factors.push_back(x);
            }
            if (c && miller_rabin(n)){
                factors.push_back(n);
                n = 1;
                break;
            }
        }

        if (n > 1 && miller_rabin(n)) factors.push_back(n);
        else if (n > 1) {
            x = sqrt((long double)0.975 + n);
            if ((x * x) == n && miller_rabin(x)){
                factors.push_back(x);
                factors.push_back(x);
            }
            else{
                for (int i = 1; ;i++){
                    x = shanks(n, i); /// Overflow problem for some numbers > 10^17, since maximum i required can be around 32
                    if (x != 1 && x != n){
                        factors.push_back(x);
                        factors.push_back(n / x);
                        break;
                    }
                }
            }
        }

        sort(factors.begin(), factors.end());
        return factors;
    }
}

int main(){
    prm::init();
}
