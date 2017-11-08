#include <bits/stdtr1c++.h>

#define MAX 1000010
#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

namespace lgr{ /// hash = 985021
    int F[MAX], P[MAX], S[MAX];

    int expo(int a, int b){
        long long res = 1;

        while (b){
            if (b & 1) res = res * a % MOD;
            a = (long long)a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    int lagrange(long long n, int k){
        long long res = 0;
        int i, x, y, z, m = k + 2, sum = 0;

        if (!F[0]){
            for (F[0] = 1, i = 1; i < MAX; i++) F[i] = ((long long)F[i - 1] * i) % MOD;
        }

        P[0] = S[m + 1] = 1;
        for (i = 1; i <= m; i++) P[i] = ((long long)P[i - 1] * (((n - i) % MOD) + MOD)) % MOD;
        for (i = m; i >= 1; i--) S[i] = ((long long)S[i + 1] * (((n - i) % MOD) + MOD)) % MOD;

        for (i = 1; i <= m; i++){
            sum += expo(i, k);
            if (sum >= MOD) sum -= MOD;
            x = ((long long)P[i - 1] * S[i + 1]) % MOD;
            y = ((long long)F[i - 1] * F[m - i]) % MOD;
            if ((m - i) & 1) y = MOD - y;
            z = ((long long)x * expo(y, MOD - 2)) % MOD;
            res = (res + ((long long)z * sum)) % MOD;
        }

        return (res % MOD);
    }
}

int main(){
    int k;
    long long n;
    cin >> n >> k;
    cout << lgr::lagrange(n, k) << endl;
    return 0;
}
