#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// LCA in O(n)
/// 0-based index and for undirected trees. To change for directed trees just modify add() function
/// Call init(nodes, root (set to any for undirected) ), add edges, call build() to pre-process
/// Note that MAX in Sparse Table must be two times MAX nodes
/// Don't forget to call build()! If Program crashes make sure build() is called before any queries

namespace lca{
    #define MAX     100010 /// Maximum number of nodes in the tree
    #define LOG         18 /// (int)floor(log2(MAX)) + 2,  {...7 = 4, 8 = 5, 9 = 5...}
    #define MAXB     11188 /// ((MAX * 2) + LG - 1) / LG, ((MAX * 2) / LG) + 77 works fine
    #define op(a, b) ((lca::ar[(a)]) < (lca::ar[(b)]) ? (a) : (b)) /// comparator of two numbers, set to min

    typedef pair<int, int> Pair; /// Next node and Edge weight

    int n, r;
    vector <Pair> adj[MAX]; /// Consider removing weight if only LCA is required
    int m, lg, len, T[MAX << 1], ar[MAX << 1], tour[MAX << 1], first[MAX << 1], mask[1 << LOG], dp[LOG][MAXB];

    void init(int nodes, int root){
        n = nodes, r = root;
        for (int i = 0; i < MAX; i++) adj[i].clear();
    }

    /// Adds undirected edge from a-b with edge weight w (0 based index)
    void add(int a, int b, int w){
        adj[a].push_back(Pair(b, w));
        adj[b].push_back(Pair(a, w));
    }

    void dfs(int i, int p, int h){
        int j, x, len = adj[i].size();
        ar[m] = h, tour[m] = i, first[i] = m++;

        for (j = 0; j < len; j++){
            x = adj[i][j].first;
            if (x != p){
                dfs(x, i, h + 1);
                ar[m] = h, tour[m++] = i;
            }
        }
    }

    void build(){
        m = 0;
        dfs(r, -1, 0);
        int i, j, k, d, top;

        lg = 32 - __builtin_clz(m);
        d = -1, i = 0, len = (m + lg - 1) / lg;

        while (i < m){
            dp[0][++d] = i++;
            for (j = 1; j < lg && i < m; i++, j++){
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
            for (j = d - lg; j < m && j < d; j++){
                while (top && ar[j] < ar[mask[top]]) top--;
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

    /// returns the lowest common ancestors of l and r
    inline int lca(int l, int r){
        l = first[l], r = first[r];
        if (l > r) swap(l, r);
        int c, d, x = (l / lg) + 1, y = (r / lg) - 1, res = l;

        if(x <= y){
            d = lg - mask[y - x + 1] - 1;
            res = op(res, op(dp[d][x], dp[d][y - (1 << d) + 1]));
        }

        c = x * lg, d = y * lg;
        res = op(res, mask[T[(c - 1) < r ? (c - 1) : r] & (~(((1 << (l - c + lg )) - 1) << (c - l)))] + c - lg);
        l = l > (d + lg) ? l : d + lg;
        res = op(res, mask[T[r] & (~(((1 << (l - d - lg)) - 1) << (d + (lg << 1) - l)))] + d + lg);
        return tour[res];
    }
}

int main(){
    int n, q, i, j, k, a, b;

    while (scanf("%d", &n) != EOF){
        lca::init(n, 0);
        for (i = 0; i < n; i++){
            scanf("%d", &k);
            while (k--){
                scanf("%d", &b);
                lca::add(i, b, 1);
            }
        }
        lca::build();

        scanf("%d", &q);
        while (q--){
            scanf("%d %d", &a, &b);
            printf("%d\n", lca::lca(a, b));
        }
    }
    return 0;
}
