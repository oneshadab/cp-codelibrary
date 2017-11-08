#include <bits/stdtr1c++.h>

#define EPS 0
#define MAXV 4010
#define MAXC 4010

#define EQUAL 0
#define LESSEQ -1
#define GREATEQ 1
#define MINIMIZE -1
#define MAXIMIZE +1

#define FEASIBLE +1
#define INFEASIBLE -1
#define UNBOUNDED 666

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
    long long ar[MAXC][MAXV], val[MAXV], rhs[MAXC];
    int n, m, flag, adj[MAXV], idx[MAXV], down[MAXV], link[MAXC];

    void init(int nvar, long long func[], int min_or_max){ /// func[] = objective function
        m = 0, n = nvar, flag = min_or_max;
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

    void pivot(int x, int y, long long& res){ /// pivoting and exchanging a non-basic variable with a basic variable
		int i, j, len = 0;
        long long v = ar[x][y];

        swap(link[x], down[y]);
        rhs[x] /= v, ar[x][y] = 1;
		for (j = 1; j <= n; j++){
            ar[x][j] /= v;
            if (abs(ar[x][j]) > EPS) adj[len++] = j;
		}

		for (i = 1; i <= m; i++){
            if (abs(ar[i][y]) > EPS && i != x){
                rhs[i] -= ar[i][y] * rhs[x], v = ar[i][y], ar[i][y] = 0;
                for (j = 0; j < len; j++) ar[i][adj[j]] -= (v * ar[x][adj[j]]);
            }
		}

		res += (ar[0][y] * rhs[x]), v = ar[0][y], ar[0][y] = 0;
		for (j = 0; j < len; j++) ar[0][adj[j]] -= (v * ar[x][adj[j]]);
    }

    int solve(long long& res){ /// simplex core
        int i, j, x, y;
        long long u, v, mn, mx;
        for (i = 1; i <= n; i++) down[i] = i;
        for (i = 1; i <= m; i++) link[i] = i + n;

        while (1){ /// phase 1
            x = 0, y = 0, mn = -EPS;
            for (i = 1; i <= m; i++){
                if (rhs[i] < mn) mn = rhs[i], x = i;
            }
            if (x == 0) break;

            for (i = 1; i <= n; i++){
                if (ar[x][i] < -EPS){
                    y = i;
                    if (rand() & 1) break;
                }
            }
            if (y == 0) return INFEASIBLE;
            pivot(x, y, res);
        }

        while (1){ /// phase 2
            x = 0, y = 0, mx = EPS;
            for (i = 1; i <= n; i++){
                if (ar[0][i] > mx) mx = ar[0][i], y = i;
            }
            if (y == 0) break;

            for (i = 1; i <= m; i++){
                if (ar[i][y] > EPS){
                    u = rhs[i] / ar[i][y];
                    if (x == 0 || u < v) x = i, v = u;
                }
            }
            if (x == 0) return UNBOUNDED;
            pivot(x, y, res);
        }

        res *= flag;
        for (int i = 1; i <= m; i++){
            if(link[i] <= n) idx[link[i]] = i;
        }

        for (int i = 1; i <= n; i++) val[i] = rhs[idx[i]];
		return FEASIBLE;
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
