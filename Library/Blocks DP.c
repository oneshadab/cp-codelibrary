#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

bool visited[200][200][200];
int t, n, ar[200], dp[200][200][200];

int F(int i, int j, int k){
    if (i > j) return 0;
    if (visited[i][j][k]) return dp[i][j][k];

    int l, res = 0;
    res = ((k + 1) * (k + 1)) + F(i + 1, j, 0);
    for (l = i + 1; l <= j; l++){
        if (ar[i] == ar[l]){
            int x = F(i + 1, l - 1, 0) + F(l, j, k + 1);
            if (x > res) res = x;
        }
    }

    visited[i][j][k] = true;
    return (dp[i][j][k] = res);
}

int main(){
    int T = 0, i, j;

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (i = 0; i < n; i++) scanf("%d", &ar[i]);

        clr(visited);
        int res = F(0, (n - 1), 0);
        printf("Case %d: %d\n", ++T, res);
    }
    return 0;
}
