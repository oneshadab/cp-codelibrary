#include <bits/stdtr1c++.h>

#define MAX 200010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define neg(x) ((x) <= n ? (x + n) : (x - n))

using namespace std;

int n;
bool visited[MAX], val[MAX];
int l, cmp, ar[MAX], num[MAX];
vector <int> adj[MAX], rev[MAX];

void topsort(int i){
    visited[i] = true;
    int j, x, len = adj[i].size();

    for (j = 0; j < len; j++){
        x = adj[i][j];
        if (!visited[x]) topsort(x);
    }
    ar[l++] = i;
}

void dfs(int i){
    num[i] = cmp;
    visited[i] = true;
    int j, x, len = rev[i].size();

    for (j = 0; j < len; j++){
        x = rev[i][j];
        if (!visited[x]) dfs(x);
    }
}

void SCC(){
    int i, j, x;
    l = 0, cmp = 0;

    clr(visited);
    for (i = 0; i < n; i++){
        if (!visited[i]) topsort(i);
    }

    clr(visited);
    for (i = l - 1; i >= 0; i--){
        x = ar[i];
        if (!visited[x]){
            cmp++;
            dfs(x);
        }
    }
}

int main(){
    int T = 0, t, q, a, b;

    scanf("%d", &t);
    while (t--){
        clr(adj), clr(rev);
        scanf("%d %d", &n, &q);

        while (q--){
            scanf("%d %d", &a, &b);
            adj[a].push_back(b);
            rev[b].push_back(a);
        }

        SCC();
    }
    return 0;
}
