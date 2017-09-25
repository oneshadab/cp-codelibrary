#include <bits/stdc++.h>
#include <tr1/tuple>

using namespace std;

//LCA with Sparse Table
struct LCA{
    static const int NMAX = 200100; // Must be atleast twice the number of nodes
    static const int WIDTH = 20;
    int F[NMAX+10], L[NMAX+10], D[NMAX+10], lst;
    int idx [NMAX+10][WIDTH+2];
    vector<int> *G;
    void build(vector<int> *G, int u){
        memset(F, -1, sizeof(F));
        this->G=G;
        D[u]=lst=0;
        dfs(u);
        for(int h=0; h<bitWidth(NMAX); h++)
            for(int i=0; i+(1<<h)<NMAX; i++)
                idx[i][h+1]=argmin(idx[i][h], idx[i+(1<<h)][h]);
    }
    void dfs(int u){
        idx[lst][0] = u;
        F[u]=L[u]=lst++;
        for(auto v: G[u]){
            if(F[v]==-1){
                D[v]=D[u]+1;
                dfs(v);
                idx[lst][0] = u;
                L[u]=lst++;
            }
        }
    }
    int get(int u, int v){
        int x = min(F[u], F[v]), y = max(L[u], L[v]);
        if(x == y) return u;
        if(x >  y) swap(x, y);
        int h = bitWidth(y - x);
        return argmin(idx[x][h], idx[y - (1<<h)][h]);
    }
    int dist(int u, int v){return D[u]+D[v]-2*D[get(u, v)];}
    // Helper Functions
    int bitWidth(int x){return 31-__builtin_clz(x);}
    int argmin(int x, int y){return D[x]<D[y]?x:y;}
}lca;

int main()
{
    return 0;
}
