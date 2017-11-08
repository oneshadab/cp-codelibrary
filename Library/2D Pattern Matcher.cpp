#include <bits/stdtr1c++.h>

#define MAX 1010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/*** 2D Pattern Matcher, n x m text, r x c pattern ***/

namespace pm{
    const unsigned long long base = 1995433697ULL;
    const unsigned long long base2 = 1000000007ULL;

    int n, m, r, c, match;
    bool occur[MAX][MAX]; /// occur[i][j] = true if pattern occurs in text[i][j] (pattern[0][0] = text[i][j])
    char str[MAX][MAX], pattern[MAX][MAX];
    unsigned long long pattern_hash, P[MAX], F[MAX], ar[MAX];

    void init(int a, int b, char text[MAX][MAX], int u, int v, char pat[MAX][MAX]){ /// hash = 502708
        n = a, m = b, r = u, c = v;
        for (int i = 0; i < n; i++) text[i][m] = 0, strcpy(str[i], text[i]);
        for (int i = 0; i < r; i++) pat[i][c] = 0, strcpy(pattern[i], pat[i]);

        P[0] = F[0] = 1;
        for (int i = 1; i < MAX; i++){
            P[i] = P[i - 1] * base;
            F[i] = F[i - 1] * base2;
        }

        pattern_hash = 0;
        for (int i = 0; i < r; i++){
            unsigned long long res = 0;
            for (int j = 0; j < c; j++) res = (res * base2) + pattern[i][j];
            pattern_hash = (pattern_hash * base) + res;
        }

        for (int i = 0; i < n; i++){
            unsigned long long res = 0;
            for (int j = 0; j < c; j++) res = (res * base2) + str[i][j];
            ar[i] = res;
        }
    }

    void roll(int col){ /// hash = 72374
        int i, j;
        unsigned long long x = 0, y;

        for (i = 0; i < r; i++) x = (x * base) + ar[i];
        for (i = 0; i < n; i++){
            if ((i + r) > n) break;
            if (x == pattern_hash) match++, occur[i][col] = true;

            y = (x - (P[r - 1] * ar[i]));
            x = (y * base) + ar[i + r];
        }
    }

    void solve(){ /// hash = 544808
        match = 0, clr(occur);
        for (int j = 0; j < m; j++){
            if ((j + c) > m) break;

            roll(j);
            for (int i = 0; i < n; i++){
                unsigned long long x = ar[i];
                x = x - (F[c - 1] * str[i][j]);
                ar[i] = (x * base2) + str[i][j + c];
            }
        }
    }
}

int main(){
}
