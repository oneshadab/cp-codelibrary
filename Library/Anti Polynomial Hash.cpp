#include <stdio.h>
#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

namespace hsh{
    long long b[2], m[2], expo[2][67], dp[2][4][1 << 16];

    /// Returns the hash value of character ch in defender's code (set to mine)
    inline long long char_hash(char ch){
        if (ch == '0') return ch + 1007;
        if (ch == '1') return ch + 1007;
    }

    /// Merge two double hash values (probably no change required here)
    inline long long merge(long long h1, long long h2){
        return (h1 << 32) ^ h2;
    }

    long long multiply(long long a, long long b, long long m){
        a %= m, b %= m;
        long long res = 0;
        while (b){
            if (b & 1) res = (res + a) % m;
            a = (a << 1) % m, b >>= 1;
        }
        return res;
    }

    long long get_hash(unsigned long long x){
        long long i = 0, h1 = 0, h2 = 0;
        while (x){
            h1 += dp[0][i][x & 65535];
            h2 += dp[1][i][x & 65535];
            i++, x >>= 16;
            if (h1 >= m[0]) h1 -= m[0];
            if (h2 >= m[1]) h2 -= m[1];
        }

        return merge(h1, h2) ^ 0x5555555555555555LL;
    }

    void print(long long x){
        int i;
        for (i = 63; i >= 0; i--) printf("%d", (x & (1LL << i)) ? 1 : 0);
        puts("");
    }

    inline void solve(long long base1, long long mod1, long long base2, long long mod2){
        int l, i, j, k;
        long long u, v, x, y, s;
        b[0] = base1, m[0] = mod1, b[1] = base2, m[1] = mod2;

        for (l = 0; l < 2; l++){
            for (expo[l][0] = 1, i = 1; i < 64; i++) expo[l][i] = multiply(expo[l][i - 1], b[l], m[l]);
            for (i = 0; i < 4; i++){
                for (j = 0; j < (1 << 16); j++){
                    dp[l][i][j] = 0;
                    for (k = 0; k < 16; k++){
                        if (j & (1 << k)) dp[l][i][j] += multiply(expo[l][16 * i + k], char_hash('1'), m[l]);
                        else dp[l][i][j] += multiply(expo[l][16 * i + k], char_hash('0'), m[l]);
                        dp[l][i][j] %= m[l];
                    }
                }
            }
        }

        x = y = s = 6666666666666666677LL;
        while (1){
            x = get_hash(x);
            y = get_hash(get_hash(y));
            if (x == y) break;
        }

        while (x != s){
            u = get_hash(x), v = get_hash(s);
            if (u == v) break;
            x = u, s = v;
        }

        print(x);
        print(s);
        assert(u == v && x != s);
    }
}

int main(){
    long long b1, m1, b2, m2; /// 1000000007 2091573227 1997293877 2117566807

    while (cin >> b1 >> m1 >> b2 >> m2){
        hsh::solve(b1, m1, b2, m2);
    }
    return 0;
}
