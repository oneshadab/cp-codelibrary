/// Problem Baltic Informatics Olympiad, Day 2, Cities
/// Given an undirected, weighted graph and k special cities
/// Find a subset of roads with minimum total cost such that all special cities are connected
/// Complexity: 2^k * spfa() + 3^k
/// Note 1 based index for graphs in this implementation

#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAXK 5
#define MAXN 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

const long long INF = 1LL << 60;

bitset <MAXN> visited;
long long dis[1 << MAXK][MAXN];
vector <pair<int, int> > graph[MAXN];
int n, k, m, Q[10000000], special[MAXK];

void spfa(long long dis[MAXN]){
    int i, j, x, w, f = 0, l = 0;
    for (i = 0; i <= n; i++){
        visited[i] = 0;
        if (dis[i] < INF) Q[l++] = i;
    }

    while (f < l){
        i = Q[f++];
        for (j = 0; j < graph[i].size(); j++){
            x = graph[i][j].first, w = graph[i][j].second;
            if (dis[x] > dis[i] + w){
                dis[x] = dis[i] + w;
                if (!visited[x]){
                    visited[x] = 1;
                    if (f && rand() & 7) Q[--f] = x;
                    else Q[l++] = x;
                }
            }
        }
        visited[i] = 0;
    }
}

long long minimumSteinerTree(){
    int i, j, mask, submask;

    for (mask = 1; mask < (1 << k); mask++){
        for (i = 1; i <= n; i++) dis[mask][i] = INF;
        if (__builtin_popcount(mask) == 1){
            dis[mask][special[31 - __builtin_clz(mask)]] = 0;
        }
        else{
            for (i = 1; i <= n; i++){
                for (submask = mask - 1; submask >= (submask ^ mask); submask = (submask - 1) & mask){
                    dis[mask][i] = min(dis[mask][i], dis[submask][i] + dis[submask ^ mask][i]);
                }
            }
        }
        spfa(dis[mask]);
    }

    return *std::min_element(dis[mask - 1] + 1, dis[mask - 1] + 1 + n);
}

int main(){
    int i, j, u, v, w;

    while (scanf("%d %d %d", &n, &k, &m) != EOF){
        for (i = 0; i < MAXN; i++) graph[i].clear();
        for (i = 0; i < k; i++) scanf("%d", &special[i]);

        for (i = 0; i < m; i++){
            scanf("%d %d %d", &u, &v, &w);
            graph[u].push_back(make_pair(v, w));
            graph[v].push_back(make_pair(u, w));
        }

        printf("%lld\n", minimumSteinerTree());
    }
    return 0;
}
