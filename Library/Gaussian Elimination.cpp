#include <bits/stdtr1c++.h>

#define MAX 105
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

/***

n = number of unknown variables
ar[i][n] = right-hand side values of constants

ar[0][0] * x1 + ar[0][1] * x2 + ... ar[0][n - 1] * xn = ar[0][n]
ar[1][0] * x1 + ar[1][1] * x2 + ... ar[1][n - 1] * xn = ar[1][n]
....
ar[n - 1][0] * x1 + ar[n - 1][1] * x2 + ... ar[n - 1][n - 1] * xn = ar[n - 1][n]


After running gauss,
x1 = ar[0][n], x2 = ar[1][n].....xn = ar[n - 1][n]
Also, R[0] = x1, R[1] = x2 ..... R[n - 1] = xn (R is used just for convenience)


Notes:
For solving problems on graphs with probability/expectation, make sure the graph
is connected and a single component. If not, then re-number the vertex and solve
for each connected component separately.

***/

bool gauss(int n, double ar[MAX][MAX], double* R){
    int i, j, k, r;

    for (i = 0; i < n; i++){
        r = i;
        for (j = i + 1; j < n; j++){
            if (abs(ar[j][i]) > abs(ar[r][i])) r = j;
        }
        if (abs(ar[r][i]) < 1e-9) return false; /// No unique solution exists, set EPS carefully

        for (j = 0; j <= n && r != i; j++) swap(ar[i][j], ar[r][j]);
        for (k = i + 1; k < n; k++){
            double x = ar[k][i] / ar[i][i];
            for (j = i; j <= n; j++){
                ar[k][j] -= (x * ar[i][j]);
            }
        }
    }

    for (i = n - 1; i >= 0; i--){
        for (j = i + 1; j < n; j++){
            ar[i][n] -= (ar[j][n] * ar[i][j]);
        }
        ar[i][n] /= ar[i][i];
        R[i] = ar[i][n];
    }

    return true;
}

int main(){
}
