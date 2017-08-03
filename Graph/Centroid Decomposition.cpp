#include <bits/stdc++.h>
#include <tr1/tuple>

using namespace std;


/* Template Begins */

#define FOR(i,N) FORR(i, 0, N)
#define FORR(i,a,b) FOTR(i, a, b, 1)
#define FOTR(i,a,b,c) for(int i=(a);i<(b);i+=(c))
#define FOREACH(it, x) for(__typeof__((x).begin()) it=(x).begin();it!=(x).end();it++)
#define MEM(a,x) memset(a,x,sizeof(a))
#define BCHK(a,x) (((a)>>(x))&1)
#define BSET(a,x) ((a)|(1<<(x)))
#define BCLR(a,x) ((a)&(~(1<<(x))))
#define BTGL(a,x) ((a)^(1<<(x)))
#define FMT(...) (sprintf(CRTBUFF, __VA_ARGS__)?CRTBUFF:0)
#define read() freopen("input.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}
#define BUFFSIZE 30000
#define INF 1000000000
#define MOD 1000000007
#define MAX 200000
#define pb push_back

typedef long long ll;

char CRTBUFF[BUFFSIZE];

#define dbg(args...) {string s(#args);s+=',';cout<<"-->";debugger::call(s.begin(), s.end(), args);cout<<"\n";}
#define dbg_A(A, N) {cout<<#A<<"=(";FOR(i,N)cout<<A[i]<<" ";cout<<"\b)\n";}
struct debugger{
    typedef string::iterator si;
    static void call(si it, si ed){}
    template<typename T, typename ... aT>
    static void call(si it, si ed, T a, aT... rest){
        string b;
        for(;*it!=',';++it) if(*it!=' ')b+=*it;
        cout << b << "=" << a << " ";
        call(++it, ed, rest...);
    }
};

//LCA with Sparse Table
struct LCA{
    static const int NMAX = 200000;
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

struct Centroid{
    const static int NMAX = 200000;
    const static int NINF  = 1000000000;
    int root;
    int P[NMAX+100], SUB[NMAX+10], vis[NMAX+10], REM[NMAX+10];
    int A[NMAX+10];
    vector<int> G[NMAX+10], NG[2][NMAX+10];

    void addEdge(int u, int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int dfsSUB(int u, int p){
        SUB[u]=1;
        for(auto v: G[u]){
            if(v!=p&&!REM[v]){
                SUB[u]+=dfsSUB(v, u);
            }
        }
        return SUB[u];
    }

    int findCentroid(int u, int p, int sz){
        int mx=-1;
        for(auto v: G[u]){
            if(v!=p&&!REM[v]){
                if(mx==-1||SUB[v]>SUB[mx])
                    mx=v;
            }
        }
        if(mx==-1||SUB[mx]<=(sz/2)) return u;
        return findCentroid(mx, u, sz);
    }
    void decompose(int u){
        root = decompose(u, u);
    }

    int decompose(int u, int p){
        dfsSUB(u, u);
        int c=findCentroid(u, u, SUB[u]);
        REM[c]=true;
        for(auto v: G[c]){
            if(!REM[v]){
                int tmp=decompose(v, c);
                //NG[0][c].pb(tmp);
                P[tmp]=c;
            }
        }
        return c;
    }

    void add(int u){
        int v=u;
        while(true){
            A[v]=min(A[v], lca.dist(u, v));
            if(v==root) break;
            v=P[v];
        }
    }

    int ask(int u){
        int ret=NINF, v=u;
        while(true){
            ret=min(ret, lca.dist(u, v)+A[v]);
            if(v==root) break;
            v=P[v];
        }
        return ret;
    }
}cd;



// Sample Problem: Codeforces Xenia and Tree
int main()
{
    //read();
    cpp_io();
    //begin
    int n, m;
    while(cin >> n >> m){
        FOR(i, n-1){
            int u, v;
            cin >> u >> v;
            u--, v--;
            cd.addEdge(u, v);
        }
        lca.build(cd.G, 0);
        cd.decompose(0);
        FOR(i, n) cd.A[i]=INF;
        cd.add(0);
        FOR(i, m){
            int op, x;
            cin >> op >> x;
            x--;
            if(op==1){
                cd.add(x);
            }
            else{
                int ans=cd.ask(x);
                cout << ans << "\n";
            }
        }
    }
    return 0;
}
