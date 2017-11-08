#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Min-cost Max-flow using variation of SPFA and Dijkstra
/// 0 Based indexed for directed weighted graphs (for undirected graphs, just add two directed edges)

namespace mcmf{
    const long long INF = 1LL << 60;

    struct edge{
        int u, v;
        long long cap, cost;

        inline edge(){}
        inline edge(int u, int v, long long cap, long long cost) : u(u), v(v), cap(cap), cost(cost){}
    };

    long long dis[MAX];
    vector <struct edge> adj[MAX];
    int n, s, t, flag, len[MAX], last[MAX], link[MAX], idx[MAX], visited[MAX];

    /// Optimization off by default because might produce wrong answer (don't know how this works)
    void init(int nodes, int source, int sink, int optimize = 0){
        flag = optimize, n = nodes, s = source, t = sink;
        for (int i = 0; i < MAX; i++){
            adj[i].clear();
            dis[i] = 0, len[i] = 0, last[i] = 0, link[i] = 0, idx[i] = 0, visited[i] = 0;
        }
    }

    inline void addEdge(int u, int v, long long f, long long c){
        adj[u].push_back(edge(len[v]++, v, f, c));
        adj[v].push_back(edge(len[u]++, u, 0, -c));
    }

    bool spfa(int s){
        int i, v, counter = 0;
        priority_queue <pair<long long, int> > PQ;

        if (flag > 0){ /// Unknown optimization
            for (i = 1, dis[s] = 0; i < n; i++){
                dis[i] = INF, counter = 0;
                for (edge e : adj[i]){
                    if (!e.cap && (dis[e.v] - e.cost) < dis[i]){
                        dis[i] = dis[e.v] - e.cost;
                        last[i] = e.v, link[i] = counter;
                    }
                    counter++;
                }
            }
        }
        else{
            for (i = 0; i < n; i++) dis[i] = INF, dis[s] = 0;
            PQ.push(make_pair(dis[s], s));

            while (!PQ.empty()){
                pair <long long, int> cur = PQ.top();
                v = cur.second, counter = 0;
                PQ.pop();

                if (-cur.first == dis[v]){
                    for (edge e : adj[v]){
                        if (e.cap > 0 && dis[e.v] > (dis[v] + e.cost)){
                            dis[e.v] = dis[v] + e.cost, last[e.v] = v, link[e.v] = counter;
                            PQ.push(make_pair(-dis[e.v], e.v));
                        }
                        counter++;
                    }
                }
            }
        }

        flag &= 666;
        return (dis[t] != INF);
    }

    inline long long dfs(int i, long long flow){
        if (i == t) return flow;

        visited[i] = 1;
        long long f = 0, old_flow = flow;

        for (int &j = idx[i]; j < len[i]; j++){
            edge &e = adj[i][j];
            if (e.cap > 0 && (dis[i] + e.cost) == dis[e.v] && !visited[e.v]){
                f = dfs(e.v, min(flow, e.cap));
                flow -= f, e.cap -= f;
                adj[e.v][e.u].cap += f;
            }

            if (flow == 0){
                visited[i] = 0;
                return old_flow - flow;
            }
        }
        return old_flow - flow;
    }

    inline pair <long long, long long> solve(){
        long long sum = 0, cost = 0, flow = 0;

        while (spfa(s)){
            sum += dis[t];
            for (int i = 0; i < n; i++) idx[i] = 0, visited[i] = 0;
            long long f = dfs(s, INF);

            cost += (sum * f), flow += f;
            for (int i = 0; i < n; i++){
                for (auto &e : adj[i]){
                    e.cost += (dis[i] - dis[e.v]);
                }
            }
        }
        return make_pair(cost, flow);
    }
}

int main(){
    clock_t start = clock();
    unsigned long long h = 0;
    int t = 10, n, m, i, j, k, l, u, v, c, w;

    while (t--){
        n = ran(2, 1000);
        m = ran(10000, 15000);
        mcmf::init(n, 0, 1);
        printf("%d %d\n", n, m);

        for (i = 0; i < m; i++){
            u = ran(0, n - 1);
            v = ran(0, n - 1);
            while (u == v) v = ran(0, n - 1);
            c = ran(0, 100), w = ran(0, 1000);
            mcmf::addEdge(u, v, c, w);
        }

        pair <long long, long long> res = mcmf::solve();
        h = h * 1000000007 + res.first;
        h = h * 1000000009;
        h = h * 1000000007 + res.second;
    }

    dbg(h);
    fprintf(stderr, "%0.9f\n", (clock() - start) / (1.0 * CLOCKS_PER_SEC));
    return 0;
}
