#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

struct Sudoku{
    int i, j, x;
};

bool flag;
char str[10];
struct Sudoku adj[81];
int A[9], B[9], C[3][3];
int t, len, steps, n = 9, T[1 << 10], dv[10], row[9], col[9], box[3][3], ar[9][9];

int compare(const void* a, const void* b){
    return ((*(struct Sudoku*)b).x - (*(struct Sudoku*)a).x);
}

int F(){
    int i, j, k, l, d, x;

    clr(A), clr(B), clr(C);
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            x = ar[i][j];
            if (x){
                x--;
                A[i] |= (1 << x);
                B[j] |= (1 << x);
                C[i / 3][j / 3] |= (1 << x);
            }
        }
    }

    int idx = 0, r = -1;
    for (d = 0; d < len; d++){
        i = adj[d]. i, j = adj[d].j;
        if (!ar[i][j]){
            k = __builtin_popcount(A[i] | B[j] | box[i / 3][j / 3]);
            if (k > r) r = k, idx = d;
            if (r == n) return -1;
        }
    }

    return idx;
}

void backtrack(int idx){
    steps++;
    if (idx == len){
        int k, l;
        flag = true;
        for (k = 0; k < n; k++){
            for (l = 0; l < n; l++){
                printf("%d ", ar[k][l]);
            }
            puts("");
        }
        return;
    }

    int lol = F();
    if (lol == -1) return;
    int y, d, i = adj[lol].i, j = adj[lol].j, k = dv[i], l = dv[j];
    int x = ~(row[i] | col[j] | box[k][l]) & 511;

    while (x){
        y = (-x & x);
        d = T[y];

        ar[i][j] = d + 1, row[i] |= (1 << d), col[j] |= (1 << d), box[k][l] |= (1 << d);
        backtrack(idx + 1);
        ar[i][j] = 0, row[i] &= ~(1 << d), col[j] &= ~(1 << d), box[k][l] &= ~(1 << d);

        if (flag) return;
        x ^= y;
    }
}

int main(){
    int i, j, k, l, x;
    for (i = 0; i < 10; i++) T[1 << i] = i, dv[i] = (i / 3);

    scanf("%d", &t);
    while (t--) {
        clr(ar), clr(row), clr(col), clr(box);

        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                scanf("%d", &ar[i][j]);
                if (!ar[i][j]) continue;

                x = ar[i][j] - 1;
                row[i] |= (1 << x);
                col[j] |= (1 << x);
                box[i / 3][j / 3] |= (1 << x);
            }
        }

        len = 0;
        for (i = n - 1; i >= 0; i--){
            for (j = n - 1; j >= 0; j--){
                if (!ar[i][j]){
                    x = row[i] | col[j] | box[i / 3][j / 3];
                    adj[len].i = i, adj[len].j = j;
                    adj[len++].x = __builtin_popcount(x);
                }
            }
        }
        qsort(adj, len, sizeof(struct Sudoku), compare);

        flag = false, steps = 0;
        backtrack(0);
        if (!flag) puts("No solution");
    }
    return 0;
}
