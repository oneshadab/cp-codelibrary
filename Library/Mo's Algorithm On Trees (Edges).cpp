/// Frank Sinatra, Winter Training Camp Moscow SU Trinity Contest
/// Given a weighted tree, find the minimum non-negative value which does not occur in the path from u to v

#include <bits/stdtr1c++.h>

#define MAXN 100010
#define MAXQ 100010
#define MAXV 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

const int block_size = 633;
typedef pair<int, int> Pair;

namespace mo{ /// Mo's Algorithm on tree(for nodes), 1-based index for nodes and queries
    char visited[MAXN];
    vector <Pair> adj[MAXN];
    int t, q, n, out[MAXQ], dp[MAXV], freq[MAXV], val[MAXN], depth[MAXN], parent[MAXN], discover[MAXN];

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

    void init(int nodes){
        t = q = 0, n = nodes;
        for (int i = 0; i < MAXN; i++) adj[i].clear();
    }

    inline void add_edge(int u, int v, int w){
        adj[u].push_back(Pair(v, w));
        adj[v].push_back(Pair(u, w));
    }

    inline void push(int l, int r){
        q++;
        Q[q] = query(l, r, q);
    }

    inline void dfs(int i){
        discover[i] = ++t;
        int j, x, len = adj[i].size();
        for (j = 0; j < len; j++){
            x = adj[i][j].first;
            if (x != parent[i]){
                val[x] = adj[i][j].second;
                parent[x] = i, depth[x] = depth[i] + 1;
                dfs(x);
            }
        }
    }

    inline void jump(int& i){
        if (!visited[i]){
            if (!freq[val[i]]++) dp[val[i] / block_size]++; /// insert
        }
        else{
            if (!--freq[val[i]]) dp[val[i] / block_size]--; /// delete
        }
        visited[i] ^= 1;
        i = parent[i];
    }

    inline void update(int u, int v){
        while (depth[u] > depth[v]) jump(u);
        while (depth[u] < depth[v]) jump(v);
        while (u != v) jump(u), jump(v);
    }

    inline void run(){
        clr(dp), clr(freq), clr(visited);
        parent[1] = 1, depth[1] = 0, Q[0] = query(1, 1, 0);

        dfs(1);
        sort(Q + 1, Q + q + 1);
        for (int i = 1; i <= q; i++){
            update(Q[i - 1].l, Q[i].l);
            update(Q[i - 1].r, Q[i].r);
            int res = 0, pos = 0;
            while (dp[pos] == block_size) res += block_size, pos++;
            while (freq[res] > 0) res++;
            out[Q[i].idx] = res;
        }
        for (int i = 1; i <= q; i++) printf("%d\n", out[i]);
    }
}

int main(){
    int n, q, i, j, k, a, b, c;

    scanf("%d %d", &n, &q);
    mo::init(n);
    for (i = 1; i < n; i++){
        scanf("%d %d %d", &a, &b, &c);
        c = min(c, n + 1); /// Only for this problem since weights can be up to 10^9
        mo::add_edge(a, b, c);
    }

    for (i = 1; i <= q; i++){
        scanf("%d %d", &a, &b);
        mo::push(a, b);
    }
    mo::run();
    return 0;
}
