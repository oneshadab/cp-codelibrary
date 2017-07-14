#include <bits/stdc++.h>

using namespace std;

struct _dinic{
    struct edge_t{
        int u, v, flow, cap, prev;
        int def_flow, def_cap; //default flow and capacity (necessary for reseting flow)
        edge_t(int uu, int vv, int cc, int ff, int pp){
            u = uu, v = vv, def_cap = cap = cc, def_flow = flow = ff, prev = pp;
        }
    };

    const static int MAX = 500;
    vector<edge_t> edges;

    int last[MAX + 10];
    int lvl[MAX + 10];
    int ptr[MAX + 10];
    int cover[MAX + 10];


    void reset(){
        memset(last, -1, sizeof(last));
        edges.clear();
    }

    void reset_flow(){
        for(int i = 0; i < edges.size(); i++){
            edges[i].flow = edges[i].def_flow;
            edges[i].cap = edges[i].def_cap;
        }
    }
    void add_edge(int u, int v, int cap){
        edges.push_back(edge_t(u, v, cap, 0, last[u]));
        last[u] = edges.size() - 1;
        edges.push_back(edge_t(v, u, cap, cap, last[v]));
        last[v] = edges.size() - 1;
    }

    int bfs(int src, int sink){
        memset(lvl, -1, sizeof(lvl));
        queue<int> que;
        que.push(src);
        lvl[src] = 0;
        while(!que.empty()){
            int u = que.front();
            que.pop();
            for(int i = last[u]; i != -1; i = edges[i].prev){
                int v = edges[i].v;
                int cap = edges[i].cap;
                int flow = edges[i].flow;
                if(lvl[v] == -1 && cap > flow){
                    lvl[v] = lvl[u] + 1;
                    que.push(v);
                }
            }
        }
        return lvl[sink] != -1;
    }

    int dfs(int u, int sink, int res){
        if(res == 0) return 0;
        if(u == sink) return res;
        for(int &idx = ptr[u]; idx != -1; idx = edges[idx].prev){
            int v = edges[idx].v;
            int cap = edges[idx].cap;
            int flow = edges[idx].flow;
            if(lvl[v] == lvl[u] + 1 && cap > flow){
                int pushed = dfs(v, sink, min(res, cap - flow));
                if(pushed){
                    edges[idx].flow += pushed;
                    edges[idx ^ 1].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    int max_flow(int src, int sink){
        reset_flow();
        int ret = 0;
        while(bfs(src, sink)){
            memcpy(ptr, last, sizeof(last));
            while(int pushed = dfs(src, sink, INT_MAX)){
                ret += pushed;
            }
        }
        return ret;
    }

    //left and right side(excluding source and sink)
    vector<int> vertex_cover(int src, int sink, int l_st, int l_ed, int r_st, int r_ed){
        memset(cover, 0, sizeof(cover));
        bfs(src, sink);
        for(int i = l_st; i <= l_ed; i++){
            if(lvl[i] == -1) cover[i] = 1;;
        }
        for(int i = r_st; i <= r_ed; i++){
            if(lvl[i] != -1) cover[i] = 1;
        }
        vector<int> vec;
        for(int i = l_st; i <= l_ed; i++){
            if(!cover[i] && !cover[r_st + (i - l_st)]){
                vec.push_back(i);
            }
        }
        return vec;
    }

} dinic;

int A[500];

//Sample Problem SPOJ-DIVREL

int main()
{
    //freopen("input.txt", "r", stdin);
    dinic.reset();
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &A[i]);
    }
    sort(A + 1, A + n + 1);
    int j = 1;
    for(int i = 1; i <= n; i++){
        if(A[i] != A[j]){
            A[++j] = A[i];
        }
    }
    n = j;
    for(int i = 1; i <= n; i++){
        dinic.add_edge(0, i, 1);
        dinic.add_edge(n + i, n + n + 1, 1);
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i != j && A[i] % A[j] == 0){
                dinic.add_edge(i, n + j, 1);
            }
        }
    }
    int dt = dinic.max_flow(0, n + n + 1);
    vector<int> vec = dinic.vertex_cover(0, n + n + 1, 1, n, n + 1, n + n);
    printf("%d\n", (int)vec.size());
    for(int i = 0; i < vec.size(); i++){
        int x = vec[i];
        if(i != 0) printf(" ");
        printf("%d", A[x]);
    }
}
