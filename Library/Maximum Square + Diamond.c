#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 505
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

char str[MAX];
bool ar[MAX][MAX];
int n, m, dp[MAX][MAX] = {0};

int Square(){ /// hash = 270386
    int i, j, x, y, res, counter = 0;

    for (i = 0; i < MAX; i++){
        dp[0][i] = dp[i][0] = dp[n + 1][i] = dp[i][m + 1] = 0;
    }

    for (i = 1; i <= n; i++){
        for (j = 1; j <= m; j++){
            if (ar[i][j]){
                x = dp[i - 1][j], y = dp[i][j - 1];
                if (y < x) x = y;
                res = x + ar[i - x][j - x];
                dp[i][j] = res;

                res--;
                if (res) counter += res;
            }
            else dp[i][j] = 0;
        }
    }
    return counter;
}

int Kite(){ /// hash = 775619
    int i, j, x, y, res, counter = 0;

    for (i = 0; i < MAX; i++){
        dp[0][i] = dp[i][0] = dp[n + 1][i] = dp[i][m + 1] = 0;
    }

    for (i = 1; i <= n; i++){
        for (j = 1; j <= m; j++){
            if (ar[i][j]){
                x = dp[i - 1][j - 1], y = dp[i - 1][j + 1];
                if (y < x) x = y;
                y = x << 1;

                if (!x || !ar[i - 1][j]) res = 1;
                else if (ar[i - y][j] && ar[i - y + 1][j]) res = x + 1;
                else res = x;
                dp[i][j] = res;

                res--;
                if (res) counter += res;
            }
            else dp[i][j] = 0;
        }
    }
    return counter;
}

int main(){
    int i, j, k;

    while (scanf("%d", &n) != EOF){

        m = n;
        for (i = 1; i <= n; i++){
            scanf("%s", str);
            for (j = 0; str[j] != 0; j++){
                ar[i][j + 1] = (str[j] == 'x');
            }
        }

        int x = Square();
        int y = Kite();
        int res = x + y;
        printf("%d\n", res);
    }
    return 0;
}
