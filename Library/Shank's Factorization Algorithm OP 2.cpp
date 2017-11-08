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

    void sieve(){
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
        if (!flag[2]) sieve();
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
        for (int i = 1; i < 10; i++){
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

    inline long long isqrt(long long x){
        return (long long)sqrtl((long double)0.975 + x);
    }

    inline bool is_square(long long x){
        long long y = isqrt(x);
        return (y * y == x);
    }

    /// Shank's Factorization Algorithm (SQUFOF)
    /// Complexity: O(N^(1/4)), (N must be greater than 1 and not a prime)
    /// Algorithms terminates successfully if all required multiplications do not overflow, otherwise throws std::overflow_error
    /// All numbers less than 2^58 are guaranteed to find a factor successfully

    inline long long shanks(long long n){
        auto find_factor = [n](const long long k)->long long{
            long long p, q, b, x, old_p, old_q, sqrt_q, sqrt_kn;

            p = sqrt_kn = isqrt(k * n);
            q = k * n - p * p, old_p = old_q = 1;
            if (q == 0) return (k == 1) ? p : 1;

            auto update = [&]{
                old_p = p;
                b = (sqrt_kn + old_p) / q, p = b * q - old_p;
                x = q, q = old_q + b * (old_p - p), old_q = x;
            };
            for (int i = 1; (i & 1) || !is_square(q); i++) update();

            sqrt_q = isqrt(q), b = (sqrt_kn - p) / sqrt_q;
            p = b * sqrt_q + p, old_q = sqrt_q, q = (k * n - p * p) / old_q;

            do{
                update();
            } while (p != old_p);
            return __gcd(n, p);
        };

        const long long lim = std::numeric_limits <long long>::max() / n;
        for (long long k = 1; k <= lim; k++){
            long long f = find_factor(k);
            if (f != 1 && f != n) return f;
        }

        throw std::overflow_error("Shanks overflow error!\n");
        return -1;
    }

    inline void factorize(long long n, vector <long long>& res){
        if (n == 1) return;
        if (isprime(n)){
            res.push_back(n);
            return;
        }

        long long f = shanks(n);
        factorize(f, res);
        factorize(n / f, res);
    }

    inline vector <long long> factorize(long long n){
        vector <long long> res;
        for (int i = 0; i < p; i++){
            if ((long long)prime[i] * prime[i] * prime[i] * prime[i] > n) break;
            while (n % prime[i] == 0){
                n /= prime[i];
                res.push_back(prime[i]);
            }
        }
        factorize(n, res);

        sort(res.begin(), res.end());
        return res;
    }
}

int main(){
    prm::init();
    vector <long long> v = prm::factorize(12 * 31 * 7 * 997 * 17 * 2147483647LL);
    for (int i = 0; i < v.size(); i++) dbg(v[i]);
}
