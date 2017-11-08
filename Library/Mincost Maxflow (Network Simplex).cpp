#include <stdio.h>
#include <bits/stdtr1c++.h>

#define MAXV 12010
#define MAXC 12210

#define EQUAL 0
#define LESSEQ -1
#define GREATEQ 1
#define MINIMIZE -1
#define MAXIMIZE +1

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

/// Min-cost Max-flow using network simplex
/// 0 Based indexed for directed weighted graphs (for undirected graphs, just add two directed edges)
/// Runs in around 1.25 seconds when n <= 100 and m = n * (n - 1) / 2
/// Costs can be negative and works with negative cycles as well
/// Number of variables in simplex = M, Number of constraints = N + M

struct edge{
    int u, v;
    long long c, w; /// c = capacity, w = weight of edge
    edge(){}
    edge(int a, int b, long long x, long long y){
        u = a, v = b;
        c = x, w = y;
    }
};

namespace lp{
    bool has_solution;
    int n, m, flag, link[MAXC], down[MAXV], idx[MAXV];
    long long res, ar[MAXC][MAXV], val[MAXV], rhs[MAXC];

    void init(int nvar, long long func[], int min_or_max){ /// func[] = objective function
        flag = min_or_max;
        has_solution = false;
        res = 0, m = 0, n = nvar;
        for (int i = 1; i <= n; i++) idx[i] = 0;
        for (int i = 1; i <= n; i++) ar[0][i] = func[i] * flag;
    }

    /// var[] = co-efficients of the constraints (LHS), lim = limit in RHS
    inline void add_constraint(long long var[], int lim, int flag){
        flag *= -1;
        if (flag == 0){
            rhs[++m] = lim;
            for (int i = 1; i <= n; i++) ar[m][i] = var[i];
            rhs[++m] = -lim;
            for (int i = 1; i <= n; i++) ar[m][i] = -var[i];
        }
        else{
            rhs[++m] = lim * flag;
            for (int i = 1; i <= n; i++) ar[m][i] = var[i] * flag;
        }
    }

    void pivot(int x, int y){ /// pivoting and exchanging a non-basic variable with a basic variable
		int i, j, t = 0;
        long long v = ar[x][y];

        rhs[x] /= v;
        ar[x][y] = 1;
        swap(link[x], down[y]);
		for (j = 1; j <= n; j++){
            ar[x][j] /= v;
            if (ar[x][j]) val[++t] = j;
		}

		for (i = 1; i <= m; i++){
            if (ar[i][y] && i != x){
                rhs[i] -= (ar[i][y] * rhs[x]);
                v = ar[i][y], ar[i][y] = 0;
                for (j = 1; j <= t; j++) ar[i][val[j]] -= (v * ar[x][val[j]]);
            }
		}

		res += (ar[0][y] * rhs[x]), v = ar[0][y], ar[0][y] = 0;
		for (j = 1; j <= t; j++) ar[0][val[j]] -= (v * ar[x][val[j]]);
    }

    long long solve(){ /// simplex core
        int i, j, x, y;
        for (i = 1; i <= n; i++) down[i] = i;
        for (i = 1; i <= m; i++) link[i] = i + n;

        while (1){
            for (x = 1; x <= m && rhs[x] >= 0; x++){}
            if (x > m) break;
            for (j = 1, y = 0; j <= n; j++){
                if (ar[x][j] < 0){
                    y = j;
                    if (rand() & 1) break; /// try removing rand()
                }
            }
            if (y == 0) return -666;
            pivot(x, y);
        }

        while (1){
            for (i = 1, y = 0; i <= n; i++){
                if (ar[0][i] > 0 && (y == 0 || ar[0][i] > ar[0][y])) y = i;
            }
            if (y == 0) break;
            for (j = 1, x = 0; j <= m; j++){
                if (ar[j][y] > 0){
                    if (x == 0 || rhs[j] / ar[j][y] < rhs[x] / ar[x][y]) x = j;
                }
            }
            assert(x != 0);
            pivot(x, y);
        }

        has_solution = true;
        for (int i = 1; i <= m; i++){
            if(link[i] <= n) idx[link[i]] = i;
        }
        for (int i = 1; i <= n; i++) val[i] = rhs[idx[i]];
		return res * flag;
	}
}

void buildFlowNetwork(int n, int s, int t, vector <edge> E, int flag, long long flow = 0){
    long long ar[MAXV] = {0};
    vector <pair<int, int>> in[n + 1], out[n + 1];

    for (int i = 0; i < E.size(); i++){
        if (E[i].u == t || E[i].v == s) continue;
        out[E[i].u].push_back(make_pair(i + 1, E[i].c));
        in[E[i].v].push_back(make_pair(i + 1, E[i].c));
    }

    clr(ar);
    if (flag == 0){ /// to find maximum flow
        for (int i = 0; i < out[s].size(); i++) ar[out[s][i].first] += 1;
        lp::init(E.size(), ar, MAXIMIZE);
    }
    else{ /// to find minimum cost
        for (int i = 0; i < E.size(); i++) ar[i + 1] += E[i].w;
        lp::init(E.size(), ar, MINIMIZE);
    }

    if (flag == 1){ /// add additional constraint that total flow from source equals maximum flow
        clr(ar);
        for (int i = 0; i < out[s].size(); i++) ar[out[s][i].first] += 1;
        lp::add_constraint(ar, flow, EQUAL);
    }

    clr(ar);
    for (int i = 0; i < out[s].size(); i++) ar[out[s][i].first] += 1;
    for (int i = 0; i < in[t].size(); i++) ar[in[t][i].first] += -1;
    lp::add_constraint(ar, 0, LESSEQ);

    clr(ar);
    for (int i = 0; i < E.size(); i++){
        ar[i + 1] = 1;
        lp::add_constraint(ar, E[i].c, LESSEQ);
        ar[i + 1] = 0;
    }

    for (int i = 0; i < n; i++){
        if (i != s && i != t){
            clr(ar);
            for (int j = 0; j < out[i].size(); j++) ar[out[i][j].first] += 1;
            for (int j = 0; j < in[i].size(); j++) ar[in[i][j].first] += -1;
            lp::add_constraint(ar, 0, LESSEQ);
        }
    }
}

/// n = nodes, s = source, t = sink, E = list of edges
pair<long long, long long> solve(int n, int s, int t, vector <edge> E){
    long long flow = 0, cost = 0;
    buildFlowNetwork(n, s, t, E, 0);

    flow = lp::solve();
    if (flow > 0){
        buildFlowNetwork(n, s, t, E, 1, flow);
        cost = lp::solve();
    }
    return make_pair(cost, flow);
}

int main(){

}
