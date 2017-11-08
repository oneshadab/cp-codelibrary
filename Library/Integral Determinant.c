#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int expo(int a, int b, int MOD){
    int res = 1;

    while (b){
        if (b & 1) res = (long long)res * a % MOD;
        a = (long long)a * a % MOD;
        b >>= 1;
    }
    return res;
}

int gauss(int n, int ar[MAX][MAX], int MOD){ /// Gaussian elimination in field MOD (MOD should be a prime)
    int i, j, k, l, p, counter = 0;

    for (i = 0; i < n; i++){
        for (p = i, j = i + 1; j < n && !ar[p][i]; j++){
            p = j;
        }
        if (!ar[p][i]) return -1;

        for (j = i; j < n; j++){
            k = ar[p][j], ar[p][j] = ar[i][j], ar[i][j] = k;
        }

        if (p != i) counter++;
        for (j = i + 1; j < n; j++){
            long long x = (long long)expo(ar[i][i], MOD - 2, MOD) * (MOD - ar[j][i]) % MOD;
            for (k = i; k < n; k++){
                ar[j][k] = (x * ar[i][k] + ar[j][k]) % MOD;
            }
        }
    }
    return counter;
}

/// Finds the determinant of a square matrix
/// Returns 0 if the matrix is singular or degenerate (hence no determinant exists)

int determinant(int n, int ar[MAX][MAX], int MOD){
    long long res = 1;
    int i, j, k, free;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (ar[i][j] < 0) ar[i][j] += MOD;
        }
    }

    free = gauss(n, ar, MOD);
    if (free == -1) return 0; /// Determinant is 0 so matrix is not invertible, singular or degenerate matrix

    for (i = 0; i < n; i++) res = (res * ar[i][i]) % MOD;
    if (free & 1) res = MOD - res;
    if ((MOD - res) < res) res -= MOD; /// Determinant can be negative so if determinant is more close to MOD than 0, make it negative

    return res;
}

int n, ar[MAX][MAX];

int main(){
    int t, i, j, k, l;
    const int MOD = 1000000007;

    while (scanf("%d", &n) != EOF){
        if (n == 0) break;

        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                scanf("%d", &ar[i][j]);
            }
        }

        printf("%d\n", determinant(n, ar, MOD));
    }
    return 0;
}
