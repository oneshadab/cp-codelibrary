#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Sparse Table in O(n), for min and max
namespace st{
    #define MAX     100010 /// Maximum number of elements in the array
    #define LOG         17 /// (int)floor(log2(MAX)) + 1,  {...7 = 3, 8 = 4, 9 = 4...}
    #define MAXB      5925 /// (MAX + LG - 1) / LG, (MAX / LG) + 77 works fine
    #define op(a, b) ((st::ar[(a)]) < (st::ar[(b)]) ? (a) : (b)) /// comparator of two numbers, set to min

    int n, lg, len, T[MAX], ar[MAX], mask[1 << LOG], dp[LOG][MAXB];

    /// Build the sparse table in O(n)
    void init(int m, int* val){
        int i, j, k, d, top;
        for (n = 0; n < m; n++) ar[n] = val[n];

        lg = 32 - __builtin_clz(n);
        d = -1, i = 0, len = (n + lg - 1) / lg;

        while (i < n){
            dp[0][++d] = i++;
            for (j = 1; j < lg && i < n; i++, j++){
                dp[0][d] = op(i, dp[0][d]);
            }
        }

        for (j = 1; j < lg; j++){
            d = (1 << j) >> 1;
            for (i = 0; i < len; i++){
                dp[j][i] = op(dp[j - 1][i], dp[j - 1][i + ((i + d) < len ? d : 0)]);
            }
        }

        for (i = 0; i < len; i++){
            top = 0, d = (i * lg) + lg;
            for (j = d - lg; j < n && j < d; j++){
                while (top && ar[j] < ar[mask[top]]) top--; /// Change to ar[j] > ar[mask[top]] for max
                T[j] = 1 << (d - j - 1);
                if (top) T[j] |= T[mask[top]];
                mask[++top] = j;
            }
        }

        for (i = 1, k = 1 << lg, d = lg - 1; i < k; i++){
            if (i >= (1 << (lg - d))) d--;
            mask[i] = d;
        }
    }

    /// returns the minimum value (as op is set to min) in the range l-r, l must not be greater than r
    inline int query(int l, int r){
        int c, d, x = (l / lg) + 1, y = (r / lg) - 1, res = l;

        if(x <= y){
            d = lg - mask[y - x + 1] - 1;
            res = op(res, op(dp[d][x], dp[d][y - (1 << d) + 1]));
        }

        c = x * lg, d = y * lg;
        res = op(res, mask[T[(c - 1) < r ? (c - 1) : r] & (~(((1 << (l - c + lg )) - 1) << (c - l)))] + c - lg);
        l = l > (d + lg) ? l : d + lg;
        res = op(res, mask[T[r] & (~(((1 << (l - d - lg)) - 1) << (d + (lg << 1) - l)))] + d + lg);
        return ar[res]; /// return res to return index of the minimum value(as op is set to min)
    }
}

int main(){
    return 0;
}
