#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1010
#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int binomial[MAX][MAX];
long long nPk[MAX][MAX];

void Generate(){
    int i, j;
    clr(binomial);

    for (i = 0; i < MAX; i++){
        for (j = 0; j <= i; j++){
            if (i == j || j == 0) binomial[i][j] = 1;
            else{
                binomial[i][j] = (binomial[i - 1][j] + binomial[i - 1][j - 1]);
                if (binomial[i][j] >= MOD) binomial[i][j] -= MOD;
            }
        }
    }

    clr(nPk);
    for (i = 0; i < MAX; i++){
        for (j = 0; j <= i; j++){
            if (!j) nPk[i][j] = 1;
            else nPk[i][j] = (nPk[i][j - 1] * (i - j + 1)) % MOD;
        }
    }
}

int main(){
    Generate();
}
