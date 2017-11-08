#include <bits/stdtr1c++.h>

#define MAX 1000010
#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

namespace lgr{
    short factor[MAX];
    int S[MAX], ar[MAX], inv[MAX];

    inline int expo(int a, int b){
        int res = 1;

        while (b){
            if (b & 1) res = (long long)res * a % MOD;
            a = (long long)a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    int lagrange(long long n, int k){
        if (!k) return (n % MOD);

        int i, j, x, y, res = 0;
        if (!inv[0]){
            for (i = 2, x = 1; i < MAX; i++) x = (long long)x * i % MOD;
            inv[MAX - 1] = expo(x, MOD - 2);
            for (i = MAX - 2; i >= 0; i--) inv[i] = ((long long)inv[i + 1] * (i + 1)) % MOD;

            for (i = 0; i < MAX; i++) factor[i] = 0;
            for (i = 4; i < MAX; i += 2) factor[i] = 2;
            for (i = 3; (i * i) < MAX; i += 2){
                if (!factor[i]){
                    for (j = (i * i), x = i << 1; j < MAX; j += x){
                        factor[j] = i;
                    }
                }
            }
        }

        k++;
        for (ar[1] = 1, ar[0] = 0, i = 2; i <= k; i++){
            if (!factor[i]) ar[i] = expo(i, k - 1);
            else ar[i] = ((long long)ar[factor[i]] * ar[i / factor[i]]) % MOD;
        }


        for (i = 1; i <= k; i++){
            ar[i] += ar[i - 1];
            if (ar[i] >= MOD) ar[i] -= MOD;
        }
        if (n <= k) return ar[n];

        for (S[k] = 1, i = k - 1; i >= 0; i--) S[i] = ((long long)S[i + 1] * ((n - i - 1) % MOD)) % MOD;
        for (i = 0, y = 1; i <= k; i++){
            x = (long long)ar[i] * y % MOD * S[i] % MOD * inv[k - i] % MOD * inv[i] % MOD;
            if ((k - i) & 1){
                res -= x;
                if (res < 0) res += MOD;
            }
            else{
                res += x;
                if (res >= MOD) res -= MOD;
            }
            y = ((long long)y * ((n - i) % MOD)) % MOD;
        }

        return (res % MOD);
    }
}

int main(){
    int k;
    long long n;
    while (scanf("%lld %d", &n, &k) != EOF){
        printf("%d\n", lgr::lagrange(n, k));
    }
    return 0;
}
