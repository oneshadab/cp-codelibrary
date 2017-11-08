/// SPOJ Count On A Tree II, Number of distinct values on nodes on the path from U to V

#include <bits/stdtr1c++.h>

#define LOGN 18
#define MAXN 100010
#define MAXQ 100010
#define MAXV 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

const int block_size = 341;

namespace mo{ /// Mo's Algorithm on tree(for nodes), 1-based index for nodes and queries
    char visited[MAXN];
    vector <int> adj[MAXN];
    int t, q, n, res, out[MAXQ], freq[MAXV], lg[MAXN], val[MAXN], depth[MAXN], parent[MAXN], discover[MAXN], dp[MAXN][LOGN];

    struct query{
        int l, r, idx;

        inline query(){}
        inline query(int a, int b, int c){
            idx = c;
            l = a, r = b;
        }

        inline bool operator < (const query& other) const{
            int d1 = discover[l] / block_size, d2 = discover[other.l] / block_size;
            if (d1 != d2) return (d1 < d2);
            return ((d1 & 1) ? (discover[r] < discover[other.r]) : (discover[r] > discover[other.r])); /// experiment
        }
    } Q[MAXQ];

    void init(int nodes, int nodeval[MAXN]){
        t = q = res = 0, n = nodes;
        for (int i = 0; i < MAXN; i++) adj[i].clear();
        for (int i = 1; i <= nodes; i++) val[i] = nodeval[i];
    }

    inline void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    inline void push(int l, int r, int idx){
        Q[++q] = query(l, r, idx);
    }

    inline void dfs(int i){
        discover[i] = ++t;
        int j, x, len = adj[i].size();
        for (j = 0; j < len; j++){
            x = adj[i][j];
            if (x != parent[i]){
                parent[x] = i, depth[x] = depth[i] + 1;
                dfs(x);
            }
        }
    }

    inline int lca(int a, int b){
        if (a == b) return a;
        if (depth[a] < depth[b]) swap(a, b);

        for (int i = lg[depth[a] - depth[b]]; i >= 0; i--){
            if ((depth[a] - (1 << i)) >= depth[b]) a = dp[a][i];
        }
        if (a == b) return a;

        for (int i = lg[depth[a]]; i >= 0; i--){
            if (dp[a][i] != dp[b][i]){
                a = dp[a][i];
                b = dp[b][i];
            }
        }

        return (a == b) ? a : parent[a];
    }

    inline void build(){
        clr(freq), clr(visited);
        parent[1] = 1, depth[1] = 0, lg[0] = lg[1] = 0;
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;

        dfs(1);
        for (int l = 0; l <= lg[n]; l++){
            for (int i = 1; i <= n; i++){
                if (!l) dp[i][l] = parent[i];
                else dp[i][l] = dp[dp[i][l - 1]][l - 1];
            }
        }
    }

    inline void update(int i){
        if (!visited[i]){
            if (!freq[val[i]]++) res++; /// insert
        }
        else{
            if (!--freq[val[i]]) res--; /// delete
        }
        visited[i] ^= 1;
    }

    inline void update_path(int u, int v){
        while (depth[u] > depth[v]) update(u), u = parent[u];
        while (depth[u] < depth[v]) update(v), v = parent[v];
        while (u != v){
            update(u), update(v);
            u = parent[u], v = parent[v];
        }
        update(u);
    }

    inline void run(){
        build();
        update(1);

        Q[0] = query(1, 1, 0);
        sort(Q + 1, Q + q + 1);

        for (int i = 1; i <= q; i++){
            update_path(Q[i - 1].l, Q[i].l);
            update_path(Q[i - 1].r, Q[i].r);
            int l1 = lca(Q[i - 1].r, Q[i].r), l2 = lca(Q[i - 1].l, Q[i].l);
            int l3 = lca(Q[i].l, Q[i].r), l4 = lca(Q[i - 1].l, Q[i - 1].r);
            update(l1), update(l2), update(l3), update(l4);
            out[Q[i].idx] = res;
        }
        for (int i = 1; i <= q; i++) printf("%d\n", out[i]);
    }
}

int T[MAXN], H[MAXN];
tr1::unordered_map <int, int> mp;

int main(){
    int n, q, h, i, j, k, a, b;

    scanf("%d %d", &n, &q);
    for (i = 1; i <= n; i++) scanf("%d", &T[i]);

    ///Co-ordinate compression, necessary only for this problem

    /*** mp.clear();
    for (h = 0, i = 0; i < n; i++) H[i] = T[i + 1];
    sort(H, H + n);
    H[n] = -1;
    for (i = 0; i < n; i++){
        if (H[i] != H[i + 1]) mp[H[i]] = ++h;
    }
    for (i = 1; i <= n; i++) T[i] = mp[T[i]]; ***/

    mo::init(n, T);
    for (i = 1; i < n; i++){
        scanf("%d %d", &a, &b);
        mo::add_edge(a, b);
    }

    for (i = 1; i <= q; i++) {
        scanf("%d %d", &a, &b);
        mo::push(a, b, i);
    }

    mo::run();
    return 0;
}
