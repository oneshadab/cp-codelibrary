#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

namespace fenwick2D{
    long long tree[MAX * 128];
    int n, idx, root[MAX], L[MAX * 128], R[MAX * 128]; /// Set as large as possible

    /// n by n matrix, initially all 0
    inline void init(int nsize){
        n = nsize + 1, idx = 0;
        clr(tree), clr(root), clr(L), clr(R);
    }

    inline void update(int &cur, int a, int b, int p, long long v){
        if (!cur) cur = ++idx;
        tree[cur] += v;

        if (a ^ b){
            int m = (a + b) >> 1;
            if (p <= m) update(L[cur], a, m, p, v);
            else update(R[cur], m + 1, b, p, v);
        }
    }

    inline long long query(int cur, int a, int b, int r){
        if (!cur) return 0;
        if (r >= b) return tree[cur];

        int m = (a + b) >> 1;
        if (r <= m) return query(L[cur], a, m, r);
        return tree[L[cur]] + query(R[cur], m + 1, b, r);
    }

    /// Add v to the sub-rectangle from upper-left [i,j] to lower-right [n,n]
    inline void update(int x, int y, long long v){
        while (x <= n){
            update(root[x], 1, n, y, v);
            x += (x & -x);
        }
    }

    /// Add v to the sub-rectangle from upper-left [i,j] to lower-right [k,l]
    void update(int i, int j, int k, int l, int v){
        if (i > k || j > l) return;

        update(i, j, v);
        update(k + 1, j, -v);
        update(k + 1, l + 1, v);
        update(i, l + 1, -v);
    }

    /// Query for the value at index [i][j]
    inline long long query(int x, int y){
        long long res = 0;
        while (x){
            res += query(root[x], 1, n, y);
            x ^= (x & -x);
        }
        return res;
    }
}

int main(){
    int n, i, j;

    n = 10;
    fenwick2D::init(n);
    fenwick2D::update(3, 5, 6, 7, 1);
    fenwick2D::update(4, 6, 8, 9, 1);

    for (i = 1; i <= n; i++){
        for (j = 1; j <= n; j++){
            cout << fenwick2D::query(i, j) << " ";
        }
        puts("");
    }
    puts("");
}
