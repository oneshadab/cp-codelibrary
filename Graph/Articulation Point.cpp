#include<bits/stdc++.h>

#define MEM(a,x) memset(a,x,sizeof(a))
#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}
#define pii pair<int, int>
#define pb push_back

using namespace std;

//namespace ArticulationPoint
namespace AP {
    const int NMAX = 110;
    vector<pair<int, int> > bridges;
    int low[NMAX], num[NMAX], parent[NMAX], counter, root, rootc;

    bool visited[NMAX];
    int ap[NMAX]; //ap[i] stores the number of vertex will disconnect
                  //if i is removed

    void clear() {
        MEM(visited, 0); MEM(ap, 0); MEM(low, -1); MEM(num, -1); MEM(parent, 0);
        counter = 0; rootc = 0;
        bridges.clear();
    }

    void find(vector<int>const (&G)[NMAX], int u) {
        visited[u] = true;
        if(u==root)rootc = 0;
        low[u] = num[u] = counter++;
        for (auto v: G[u]) {
            if (!visited[v]) {
                parent[v] = u;
                if (u == root)rootc++;
                find(G, v);

                //set Articulation Point
                if (low[v] >= num[u])ap[u]++;

                //set Bridge
                if (low[v] > num[u]) {
                    int k = u, l = v;
                    if (k > l)swap(k, l);
                    bridges.pb({k, l});
                }
                low[u] = min(low[u], low[v]);
            } else if (v != parent[u]) {
                low[u] = min(low[u], num[v]);
            }
        }
        if(u==root && rootc < 2) ap[root] = 0;
    }
}

//UVa 796 - Critical Links
int main() {
    cpp_io();
    stringstream ss;
    string s;
    int x, y, m, i, cs = 1;
    int n;
    while (cin >> n) {
        getline(cin, s);
        vector<int> G[110];
        for (i = 0; i < n; i++) {
            getline(cin, s);
            ss.clear();
            ss.str(s);
            ss >> x;
            ss >> s;
            while (ss >> y) {
                G[x].pb(y);
            }
        }
        AP::clear();
        for (i = 0; i < n; i++) {
            if (AP::visited[i])continue;
            AP::root = i;
            AP::find(G, i);
        }
        auto &bridges = AP::bridges;
        y = 0;
        sort(bridges.begin(), bridges.end());
        cout << bridges.size() << " critical links\n";
        for (i = 0; i < bridges.size(); i++) {
            cout << bridges[i].first << " - " << bridges[i].second << "\n";
        }
        cout << "\n";
    }
}

// SOLVED
/* UVa 796 - Critical Links
 * UVa 10765 - Doves and bombs
 * hackerearth tutorial: https://goo.gl/rD1Z1q */
// _SOLVED