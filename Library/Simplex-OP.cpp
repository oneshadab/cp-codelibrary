#include <bits/stdtr1c++.h>

#define EPS 1e-9
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

/***
1.  Simplex Algorithm for Linear Programming
2.  Maximize or minimize f1*x1 + f2*x2 + f3*x3 + ... + fn*xn subject to some constraints
3.  Constraints are of the form, c1x1 + c2x2 + c3x3 + ... + cnxn (<= or >= or =) rhs
4.  m is the number of constraints indexed from 1 to m, and n is the number of variables indexed from 1 to n
5.  It is assumed that all variables satisfies non-negativity constraint, i.e, xi >= 0
6.  If non-negativity constraint is not desired for a variable x, replace each occurrence
    by difference of two new variables r1 and r2 (where r1 >= 0 and r2 >= 0, handled automatically by simplex).
    That is, replace every x by r1 - r2 (Number of variables increases by one, -x, +r1, +r2)
7.  solution_flag = INFEASIBLE if no solution is possible and UNBOUNDED if no finite solution is possible
8.  Returns the maximum/minimum value of the linear equation satisfying all constraints otherwise
9. After successful completion, val[] contains the values of x1, x2 .... xn for the optimal value returned

*** If ABS(X) <= M in constraints, Replace with X <= M and -X <= M

*** Fractional LP:

    max/min
        3x1 + 2x2 + 4x3 + 6
        -------------------
        3x1 + 3x2 + 2x3 + 5

        s.t. 2x1 + 3x2 + 5x3 ≥ 23
        3x2 + 5x2 + 4x3 <= 30
        x1, x2, x3 ≥ 0

    Replace with:

    max/min
        3y1 + 2y2 + 4y3 + 6t

        s.t. 3y1 + 3y2 + 2y3 + 5t = 1
        2y1 + 3y2 + 53 - 23t ≥ 0
        3y1 + 5y2 + 4y3- 30t <= 0
        y1, y2, y3, t ≥ 0

***/

namespace lp{
    double ar[MAXC][MAXV], val[MAXV], rhs[MAXC];
    int n, m, flag, adj[MAXV], idx[MAXV], down[MAXV], link[MAXC];

    void init(int nvar, double func[], int min_or_max){ /// func[] = objective function
        m = 0, n = nvar, flag = min_or_max;
        for (int i = 1; i <= n; i++) idx[i] = 0;
        for (int i = 1; i <= n; i++) ar[0][i] = func[i] * flag;
    }

    /// var[] = co-efficients of the constraints (LHS), lim = limit in RHS
    /// flag = EQUAL for var[] = lim, LESSEQ for var[] <= lim, GREATEQ for var[] >= lim
    inline void add_constraint(double var[], double lim, int flag){
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

    void pivot(int x, int y, double& res){ /// pivoting and exchanging a non-basic variable with a basic variable
		int i, j, len = 0;
        double v = ar[x][y];

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

    int solve(double& res){ /// simplex core
        int i, j, x, y;
        double u, v, mn, mx;
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

int main(){

}
