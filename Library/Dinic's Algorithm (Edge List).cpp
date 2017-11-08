#include <bits/stdtr1c++.h>

#define MAXN 30010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Dinic's algorithm for directed graphs (0 based index for graphs)
/// For undirected graphs, just add two directed edges

const long long INF = (~0ULL) >> 1;

namespace flow{
    struct Edge{
        int u, v;
        long long cap, flow;

        Edge(){}
        Edge(int a, int b, long long c, long long f){
            u = a, v = b, cap = c, flow = f;
        }
    };

    vector <int> adj[MAXN];
    vector <struct Edge> E;
    int n, s, t, ptr[MAXN], len[MAXN], dis[MAXN], Q[MAXN];

    inline void init(int nodes, int source, int sink){
        clr(len);
        E.clear();
        n = nodes, s = source, t = sink;
        for (int i = 0; i < MAXN; i++) adj[i].clear();
    }

    /// Adds a directed edge with capacity c
    inline void addEdge(int a, int b, long long c){
        adj[a].push_back(E.size());
        E.push_back(Edge(a, b, c, 0));
        len[a]++;
        adj[b].push_back(E.size());
        E.push_back(Edge(b, a, 0, 0));
        len[b]++;
    }

    inline bool bfs(){
        int i, j, k, id, f = 0, l = 0;
        memset(dis, -1, sizeof(dis[0]) * n);

        dis[s] = 0, Q[l++] = s;
        while (f < l && dis[t] == -1){
            i = Q[f++];
            for (k = 0; k < len[i]; k++){
                id = adj[i][k];
                if (dis[E[id].v] == -1 && E[id].flow < E[id].cap){
                    Q[l++] = E[id].v;
                    dis[E[id].v] = dis[i] + 1;
                }
            }
        }
        return (dis[t] != -1);
    }

    long long dfs(int i, long long f){
        if (i == t || !f) return f;
        while (ptr[i] < len[i]){
            int id = adj[i][ptr[i]];
            if (dis[E[id].v] == dis[i] + 1){
                long long x = dfs(E[id].v, min(f, E[id].cap - E[id].flow));
                if (x){
                    E[id].flow += x, E[id ^ 1].flow -= x;
                    return x;
                }
            }
            ptr[i]++;
        }
        return 0;
    }

    long long dinic(){
        long long res = 0;

        while (bfs()){
            memset(ptr, 0, n * sizeof(ptr[0]));
            while (long long f = dfs(s, INF)) {
                res += f;
            }
        }
        return res;
    }
}

namespace nodeflow{
    void init(int n, int s, int t, vector <long long> capacity){
        flow::init(n * 2, s * 2, t * 2 + 1);

        for (int i = 0; i < n; i++){
            flow::addEdge(i * 2, i * 2 + 1, capacity[i]);
        }
    }

    void addEdge(int a, int b, long long c){
        flow::addEdge(a * 2 + 1, b * 2, c);
    }

    long long dinic(){
        return flow::dinic();
    }
}

int main(){
    int n, i, j, k, a, b, c, s, t, m;

    n = MAXN - 10;
    s = 0, t = n - 1;
    flow::init(n, s, t);

    ///m = n * 1.75;
    m = 1e6;

    while (m--){
        a = ran(0, n - 1);
        b = ran(0, n - 1);
        c = ran(1, 1000000000);
        flow::addEdge(a, b, c);
    }

    clock_t start = clock();
    printf("%lld\n", flow::dinic());
    fprintf(stderr, "%0.6f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
