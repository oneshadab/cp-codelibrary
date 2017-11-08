#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

long long dp[MAX];
bool isprime[MAX];
int prime[MAX], counter[MAX];

/// Calculates all values of a multiplicative function in dp array

void linear_sieve(){ /// by default set to euler's totient function
    int i, j, k, x, len = 0;
    for (i = 2; i < MAX; i++) isprime[i] = true;

    dp[1] = 1; /// f(x) when x = 1
    for (i = 2; i < MAX; i++){
        if (isprime[i]){
            dp[i] = i - 1; /// f(x) when x is prime
            prime[len++] = i, counter[i] = 1;
        }

        for (j = 0; j < len && (i * prime[j]) < MAX; j++){
            x = i * prime[j];
            isprime[x] = false;

            if (i % prime[j] == 0){
                counter[x] = counter[i] + 1;
                dp[x] = (dp[i] / counter[i]) * counter[x];
                break;
            }
            else{
                counter[x] = 1;
                dp[x] = dp[i] * dp[prime[j]];
            }
        }
    }
}

int main(){
    linear_sieve();
    int i, j, k;

    unsigned long long h = 0;
    for (i = 2; i < MAX; i++) h = h * 666666667 + dp[i] + 13;
    printf("%llu\n", h);
}
