#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1010
#define MOD 1000000007
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int S[MAX][MAX];

void Generate(){ /// hash = 173404
    int i, j;

    S[0][0] = 1;
    for (i = 1; i < MAX; i++){
        S[i][0] = 0;
        for (j = 1; j <= i; j++){
            S[i][j] = ( ((long long)S[i - 1][j] * j) + S[i - 1][j - 1]) % MOD;
        }
    }
}

long long faulhaber(long long n, int k){ /// hash = 766729
    if (!k) return (n % MOD);

    int i, j, l;
    long long z, res = 0;

    for (j = 0; j <= k; j++){
        z = 1;
        for (l = j + 1, i = 0; (i - 1) < j; i++){
            if ((l > 1) && !((n - i + 1) % l)){
                z = (z * (((n - i + 1) / l) % MOD) ) % MOD;
                l = 1;
            }
            else z = (z * ((n - i + 1) % MOD) ) % MOD;
        }
        res = (res + (z * S[k][j])) % MOD;
    }
    return res;
}

int main(){
    Generate();
    int t, k;
    long long n;

    scanf("%d", &t);
    while (t--){
        scanf("%lld %d", &n, &k);
        printf("%lld\n", faulhaber(n, k));
    }
    return 0;
}
