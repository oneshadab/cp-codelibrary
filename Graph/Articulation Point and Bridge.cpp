#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

namespace ArticulationPoint{
    const int NMAX = 110;
    vector <pair<int, int> > bridges;
    int low[NMAX], num[NMAX], parent[NMAX], counter, root, rc;
    bool visited[NMAX], aVertex[NMAX];

    void clear(){
        memset(visited, 0, sizeof(visited));
        memset(low, -1, sizeof(low));
        memset(num, -1, sizeof(num));
        memset(parent, 0, sizeof(parent));
        counter = 0;
        root = -1;
        bridges.clear();
    }
    void find(vector<int> G[], int u){
        if(num[u] != -1 ) return;
        if(root == -1) root = u, rc = 0;
        low[u] = num[u] = counter++;
        for(auto v: G[u]){
            if (num[v] == -1){
                parent[v] = u;
                if (u == root) rc++;
                find(G, v);
                if (low[v] > num[u]) {
                    if(u != root) aVertex[u] = true;
                    bridges.push_back({min(u, v), max(u, v)});
                }
                low[u] = min(low[u], low[v]);
            }
            else if (v != parent[u]){
                low[u] = min(low[u], num[v]);
            }
        }
        if (rc >= 2) aVertex[root] = true;
        if (root == u) root = -1, rc = 0;
    }
}



bool fnc(const pii &a, const pii &b)
{
    return (a.first < b.first);
}
int main(){
    //freopen("796.txt", "r", stdin);
    //ofstream cot("o.txt");
    stringstream ss;
    string s;
    int x, y, m, i, cs = 1;
    int n;
    while (cin >> n) {
        getline (cin, s);
        vector <int> grph[110];
        for (i=0; i<n; i++){
            getline (cin, s);
            ss.clear();
            ss.str(s);
            ss>>x;
            ss>>s;
            while(ss>>y) {
                grph[x].push_back(y);
            }
        }
        ArticulationPoint::clear();
        for (i=0; i<n; i++){
            ArticulationPoint::find(grph, i);
        }
        auto &vec = ArticulationPoint::bridges;
        y = 0;
        sort (vec.begin(), vec.end(), fnc);
        cout<<vec.size()<< " critical links\n";
        for(i=0; i<vec.size(); i++) {
            cout<<vec[i].first<<" - "<<vec[i].second<<"\n";
        }
        cout<<"\n";
        ArticulationPoint::clear();
    }
}
