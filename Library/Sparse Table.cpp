#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

namespace st{
    #define LOG  18
    #define MAXN 100010

    int n, lim, lg[MAXN], dp[LOG][MAXN];

    int query(int i, int j){
        int len = lg[j - i];
        return max( dp[len][i], dp[len][j - (1 << len) + 1] );
    }

    void build(int m, int* ar){
        n = m;
        int i, j, l, d, len;

        lg[0] = lg[1] = 0;
        lim = 32 - __builtin_clz(n);

        if (!lg[2]){
            for (i = 2; i < MAXN; i++) lg[i] = lg[i >> 1] + 1;
        }

        for (i = 0; i < n; i++) dp[0][i] = ar[i];
        for (l = 1; l < lim; l++){
            len = (1 << l);
            for (i = 0; (i + len) <= n; i++){
                d = 1 << (l - 1);
                dp[l][i] = max(dp[l - 1][i], dp[l - 1][i + d]);
            }
        }
    }
}

int main(){
}
