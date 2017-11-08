#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 666
#define inf (~0U >> 1)
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

bool used[MAX];
int n, m, ar[MAX][MAX];
int U[MAX], V[MAX], P[MAX], way[MAX], minv[MAX], match[MAX];

/*** Hungarian Algorithm for weighted bipartite matching ***/
/*** n = number of rows,m = number of columns, in 1-base ***/
/*** match[i] contains the column to which it is matched ***/
/*** n = Note that m should be >= n, Just fill the whole matrix with 0 if this is not true ***/

int hungarian(int n, int m, int ar[MAX][MAX]){
    if (n > m) m = n;
    clr(way), clr(U), clr(V), clr(P);
    int i, j, i0, i1, j0, j1, cur, delta;

    for (i = 1; i <= n; i++){
        P[0] = i, j0 = 0;
        for (j = 0; j <= m; j++) minv[j] = inf, used[j] = false;

        do{
            used[j0] = true;
            i0 = P[j0], j1 = 0, delta = inf;

            for (j = 1; j <= m; j++){
                if (!used[j]){
                    cur = ar[i0][j] - U[i0] - V[j];
                    if (cur < minv[j]){
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta){
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }

            for (j = 0; j <= m; j++){
                if (used[j]){
                    U[P[j]] += delta;
                    V[j] -= delta;
                }
                else minv[j] -= delta;
            }
            j0 = j1;
        } while (P[j0] != 0);

        do{
            j1 = way[j0];
            P[j0] = P[j1];
            j0 = j1;
        } while (j0 != 0);
    }
    for (j = 1; j <= m; j++) match[P[j]] = j;

    return -V[0];
}

int main(){
}
