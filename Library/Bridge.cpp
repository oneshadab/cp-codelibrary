#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/// Note: 0-based indexing for graphs
namespace fuck{
    typedef pair<int, int> Pair;

    vector <Pair> bridge;
    vector <Pair> adj[MAX];
    bool cut[MAX], visited[MAX];
    int n, disc_t, discover[MAX], low[MAX];

    void init(int nodes){
        n = nodes;
        for (int i = 0; i < MAX; i++) adj[i].clear();
    }

    void dfs(int i, int p){
        visited[i] = true;
        discover[i] = low[i] = ++disc_t;
        int j, x, cmp, children = 0, len = adj[i].size();

        for (j = 0; j < len; j++){
            x = adj[i][j].first;
            if (!visited[x]){
                children++;
                dfs(x, i);
                low[i] = min(low[i], low[x]);

                if (low[x] > discover[i]){
                    int cmp = -1; /// cmp used to check for multi-edge
                    if (j) cmp = adj[i][j - 1].first;
                    if (cmp != x && (j + 1) < len) cmp = adj[i][j + 1].first;
                    if (cmp != x) bridge.push_back(Pair(min(i, x), max(i, x))); /// lower node comes first in bridge representation
                }
            }
            else if (x != p) low[i] = min(low[i], discover[x]);
        }
    }

    /// Adds undirected edge from a to b with cost or edge index number i
    /// Note that i is optional, it's not needed to find bridges

    void add(int a, int b, int i){
        adj[a].push_back(Pair(b, i));
        adj[b].push_back(Pair(a, i));
    }

    void FindBridge(){
        int i, j;
        bridge.clear();
        clr(cut), clr(visited);
        for (i = 0; i < n; i++) sort(adj[i].begin(), adj[i].end()); /// To handle multi-edges

        for (i = 0; i < n; i++){
            if (!visited[i]){
                disc_t = 0;
                dfs(i, -1);
            }
        }
        /// bridge vector contains all the bridges as pairs now
    }
}

int main(){
}
