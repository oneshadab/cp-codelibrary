#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAX 200010 /// 2 * max(nodes, edges)
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Min-cost Max-flow using dijkstra with potentials
/// 0 Based indexed for directed weighted graphs (for undirected graphs, just add two directed edges)
/// Runs in around 2 seconds when n <= 200 and m = n * (n - 1) / 2
/// Runs well for sparse graphs though, e.g, m <= 10 * n
/// Costs must be non-negative

namespace mcmf{
    const long long INF = 1LL << 60;

    long long potential[MAX], dis[MAX], cap[MAX], cost[MAX];
    int n, m, s, t, to[MAX], from[MAX], last[MAX], next[MAX], adj[MAX];

    struct compare{
        inline bool operator()(int a, int b){
            if (dis[a] == dis[b]) return (a < b);
            return (dis[a] < dis[b]);
        }
    };
    set<int, compare> S;

    void init(int nodes, int source, int sink){
        m = 0, n = nodes;
        s = source, t = sink;
        for (int i = 0; i <= n; i++) potential[i] = 0, last[i] = -1;
    }

    void addEdge(int u, int v, long long c, long long w){
        from[m] = u, adj[m] = v, cap[m] = c, cost[m] = w, next[m] = last[u], last[u] = m++;
        from[m] = v, adj[m] = u, cap[m] = 0, cost[m] = -w, next[m] = last[v], last[v] = m++;
    }

    pair<long long, long long> solve(){
        int i, j, e, u, v;
        long long w, aug = 0, mincost = 0, maxflow = 0;

        while (1){
            S.clear();
            for (i = 0; i < n; i++) dis[i] = INF;

            dis[s] = 0, S.insert(s);
            while (!S.empty()){
                u = *(S.begin());
                if (u == t) break;
                S.erase(S.begin());

                for (e = last[u]; e != -1; e = next[e]){
                    if (cap[e] != 0){
                        v = adj[e];
                        w = dis[u] + potential[u] + cost[e] - potential[v];

                        if (dis[v] > w){
                            S.erase(v);
                            dis[v] = w, to[v] = e;
                            S.insert(v);
                        }
                    }
                }
            }
            if (dis[t] >= (INF >> 1)) break;

            aug = cap[to[t]];
            for (i = t; i != s; i = from[to[i]]) aug = min(aug, cap[to[i]]);
            for (i = t; i != s; i = from[to[i]]){
                cap[to[i]] -= aug;
                cap[to[i] ^ 1] += aug;
                mincost += (cost[to[i]] * aug);
            }
            for (i = 0; i <= n; i++) potential[i] = min(potential[i] + dis[i], INF);
            maxflow += aug;
        }
        return make_pair(mincost, maxflow);
    }
}

int main(){

}
