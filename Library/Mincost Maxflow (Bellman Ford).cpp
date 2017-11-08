#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAX 200010 /// 2 * max(nodes, edges)
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Min-cost Max-flow using bellman ford
/// 0 Based indexed for directed weighted graphs (for undirected graphs, just add two directed edges)
/// Runs in around 0.75 seconds when n <= 100 and m = n * (n - 1) / 2
/// Runs well for sparse graphs though, e.g, m <= 10 * n
/// Costs must be non-negative

namespace mcmf{
    const long long INF = 1LL << 60;

    long long dis[MAX], cap[MAX], cost[MAX];
    int n, m, s, t, to[MAX], from[MAX], last[MAX], next[MAX], adj[MAX];

    void init(int nodes, int source, int sink){
        m = 0, n = nodes;
        s = source, t = sink;
        for (int i = 0; i <= n; i++) last[i] = -1;
    }

    void addEdge(int u, int v, long long c, long long w){
        from[m] = u, adj[m] = v, cap[m] = c, cost[m] = w, next[m] = last[u], last[u] = m++;
        from[m] = v, adj[m] = u, cap[m] = 0, cost[m] = -w, next[m] = last[v], last[v] = m++;
    }

    bool bellman_ford(){
        int i, u, v, e, flag = 1;
        for (i = 0; i < n; i++) to[i] = -1;
        for (i = 0; i < n; i++) dis[i] = INF;

        dis[s] = 0;
        for (i = 0; i < n && flag; i++){
            for (u = 0, flag = 0; u < n; u++){
                for (e = last[u]; e != -1; e = next[e]){
                    v = adj[e];
                    if (cap[e] && dis[v] > (dis[u] + cost[e])){
                        dis[v] = dis[u] + cost[e];
                        to[v] = e;
                        flag = 1;
                    }
                }
            }
        }
        ///assert(i < n); /// Negative cycle found
        return (dis[t] < INF);
    }

    pair<long long, long long> solve(){
        long long maxflow = 0, mincost = 0;

        while (bellman_ford()){
            long long aug = INF;
            for (int e = to[t]; e != -1; e = to[from[e]]) aug = min(aug, cap[e]);
            for (int e = to[t]; e != -1; e = to[from[e]]){
                mincost += (aug * cost[e]);
                cap[e] -= aug, cap[e ^ 1] += aug;
            }
            maxflow += aug;
        }
        return make_pair(mincost, maxflow);
    }
}

int main(){

}
