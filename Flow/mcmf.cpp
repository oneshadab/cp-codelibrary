#include <bits/stdc++.h>

using namespace std;


struct _mcmf{

    struct edge_t{
        int u, v, w, cap, prev;
    };

    static const int NMAX=300;
    static const int NINF=1000000;
    vector<edge_t> edges;
    int last[NMAX];
    int D[NMAX]; // Distance from source
    int E[NMAX]; // Edge used to get to u

    void reset(){
        edges.clear();
        memset(last, -1, sizeof(last));
    }

    void add_edge(int u, int v, int w, int cap){
        edges.push_back({u, v,  w, cap, last[u]});
        last[u] = edges.size() - 1;
        edges.push_back({v, u, -w, 0, last[v]});
        last[v] = edges.size() - 1;
    }

    bool bell_bfs(int src, int sink){
        for(int u=0; u<NMAX; u++) D[u]=NINF, E[u]=-1;
        int found = true;
        D[src] = 0;
        E[src] = -2;
        for(int k=0; k<NMAX&&found; k++){
            found = false;
            for(int u = 0; u < NMAX; u++){
                for(int i = last[u]; i != -1; i = edges[i].prev){
                    int v = edges[i].v, w = edges[i].w;
                    if(E[u]==-1) continue;
                    if(edges[i].cap && (E[v]==-1||D[u]+w < D[v])){
                        D[v]=D[u]+w;
                        E[v]=i;
                        found = true;
                    }
                }
            }
        }
        return (E[sink] != -1);
    }

    pair<int, int> max_flow(int src, int sink){
        int mflow = 0;
        int mcost = 0;
        while(bell_bfs(src, sink)){
            int flow = NINF;
            for(int i = E[sink]; i>=0 ; i = E[edges[i].u]){
                flow = min(flow, edges[i].cap);
            }
            for(int i = E[sink]; i>=0 ; i = E[edges[i].u]){
                edges[i].cap -= flow;
                edges[i^1].cap += flow;
                mcost += edges[i].w*flow;
            }
            mflow += flow;
        }
        return {mcost, mflow};
    }

} mcmf;

//Sample Problem SPOJ-SCITIES

int main()
{
    //freopen("input.txt", "r", stdin);
    int TC;
    scanf("%d", &TC);
    for(int cs = 1; cs <= TC; cs++){
        mcmf.reset();
        int n, m;
        scanf("%d%d", &n, &m);
        for(; ;){
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            if(u == 0 && v == 0 && w == 0) break;
            mcmf.add_edge(u, n + v, -w, 1);
        }
        for(int i = 1; i <= n; i++){
            mcmf.add_edge(0, i, 0, 1);
        }
        for(int i = 1; i <= m; i++){
            mcmf.add_edge(n + i, n + m + 1, 0, 1);
        }
        int mcost, mflow;
        tie(mcost, mflow)=mcmf.max_flow(0, n+m+1);
        printf("%d\n", -mcost);
    }
}
