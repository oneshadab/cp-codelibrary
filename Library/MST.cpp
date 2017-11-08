#include <bits/stdtr1c++.h>

#define MAXN 200010
#define MAXE 200010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

struct Edge{
    int u, v, cost;

    Edge(){
    }

    Edge(int a, int b, int c){
        u = a, v = b, cost = c;
    }

    bool operator < (const Edge& other) const{
        return (cost < other.cost);
    }
};

int n, m;
struct Edge E[MAXE];
int union_parent[MAXN], union_rank[MAXN];

int find_root(int i){
    while (i != union_parent[i]){
        union_parent[i] = union_parent[union_parent[i]];
        i = union_parent[i];
    }
    return union_parent[i];
}

int main(){
    int i, j, k, a, b, c, d, sum, counter, mst;

    while (scanf("%d %d", &n, &m) != EOF){
        if (n == 0 && m == 0) break;

        for (i = 0; i <= n; i++){
            union_rank[i] = 0;
            union_parent[i] = i;
        }

        sum = 0;
        for (i = 0; i < m; i++){
            scanf("%d %d %d", &E[i].u, &E[i].v, &E[i].cost);
            sum += E[i].cost;
        }
        sort(E, E + m);

        counter = 0, mst = 0;
        for (i = 0; i < m; i++){
            a = E[i].u, b = E[i].v;

            c = find_root(a), d = find_root(b);
            if (c != d){
                if (union_rank[c] < union_rank[d]) union_parent[c] = d;
                else if (union_rank[c] > union_rank[d]) union_parent[d] = c;
                else{
                    union_parent[c] = d;
                    union_rank[d]++;
                }

                counter++;
                mst += E[i].cost;
                if (counter == (n - 1)) break;
            }
        }

        int res = sum - mst;
        printf("%d\n", res);
    }
    return 0;
}
