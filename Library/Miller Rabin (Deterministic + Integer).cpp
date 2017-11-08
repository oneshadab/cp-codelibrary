#include <bits/stdtr1c++.h>

#define MAX 1000010
#define isprime(x) prm::miller_rabin(x)
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

namespace prm{ /// hash = 663918
    bitset <MAX> flag;
    int p = 0, prime[78777];
    const unsigned long long base[] = {4230279247111683200ULL, 14694767155120705706ULL, 16641139526367750375ULL};

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

    inline int expo(long long x, int n, int m){
        long long res = 1;

        while (n){
            if (n & 1) res = (res * x) % m;
            x = (x * x) % m;
            n >>= 1;
        }

        return (res % m);
    }

    inline bool miller_rabin(int p){
        if (p < MAX) return flag[p];
        if ((p + 1) & 1) return false;
        for (int i = 1; i < 9; i++){
            if (!(p % prime[i])) return false;
        }

        int a, m, x, s = p - 1, y = p - 1;
        s = s >> __builtin_ctz(s);

        for (int i = 0; i < 3; i++) {
            x = s, a = (base[i] % y) + 1;
            m = expo(a, x, p);
            while ((x != y) && (m != 1) && (m != y)) m = ((long long)m * m) % p, x <<= 1;
            if ((m != y) && !(x & 1)) return false;
        }
        return true;
    }
}

int main(){
    prm::init();
}
