#include <bits/stdtr1c++.h>

#define MAXV 1010
#define MAXC 10010

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

/// Network Simplex
/// Variables and constraints are 1 based
/// Solution is contained in val[] array after termination
/// Only works for special types of linear programs, for example as in flow networks

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
    inline void add_constraint(long long var[], long long lim, int flag){
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
        long long u, v;
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
                    v = rhs[j] / ar[j][y];
                    if (x == 0 || v < u) x = j, u = v;
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

/// Reduces constraints in the form of a *(e.g. <, <=, >, >=) b, by removing redundant constraints
/// Lim = number of random iterations
/// Returns false if contradictions exist, for example a < b and b < a

bool reduce(int n, int lim, vector <pair<int, int> >& edge){
    bitset <202> adj[n + 1]; /// Maximum value for n
    while (lim--){
        vector <pair<int, int> > temp = edge;
        random_shuffle(temp.begin(), temp.end());

        for (int i = 1; i <= n; i++){
            adj[i].reset();
            adj[i][i] = true;
        }

        edge.clear();
        int len = temp.size();
        for (int e = 0; e < len; e++){
            int i = temp[e].first, j = temp[e].second;
            if (!adj[i][j]){
                edge.push_back(temp[e]);
                if (adj[j][i]) return false;

                for (int k = 1; k <= n; k++){
                    if (adj[k][i]) adj[k] |= adj[j];
                }
            }
        }

        if (edge.size() == temp.size()) return true;
    }
    return true;
}

int main(){

}
