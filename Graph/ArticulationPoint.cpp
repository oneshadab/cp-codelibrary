#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

namespace ArticulationPoint{
    const int NMAX = 110;
    vector <pair<int, int> > vec;
    int low[NMAX], num[NMAX], parent[NMAX], counter, root, rootc;
    bool visited[NMAX];

    void clear(){
        memset(visited, 0, sizeof(visited));
        memset(low, -1, sizeof(low));
        memset(num, -1, sizeof(num));
        memset(parent, 0, sizeof(parent));
        counter = 0;
        vec.clear();
    }

    void find(vector<int> G[], int u){

        low[u] = num[u] = counter++;
        int i, j;
        for(auto v: G[u]){
            if (!visited[v]){
                parent[v] = u;
                visited[v] = true;
                if (u == root)rootc++;
                find(G, v);
                if (low[v] > num[u]) {
                    int k = u, l = v;
                    if(k>l)swap(k,l);
                    vec.push_back(pii(k, l));
                }
                low[u] = min(low[u], low[v]);
            }
            else if (j != parent[u]){
                low[u] = min(low[u], num[v]);
            }
        }
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
            if(ArticulationPoint::visited[i])continue;
            ArticulationPoint::root = i;
            ArticulationPoint::visited[i] = true;
            ArticulationPoint::rootc = 0;
            ArticulationPoint::find(grph, i);
        }
        auto &vec = ArticulationPoint::vec;
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
