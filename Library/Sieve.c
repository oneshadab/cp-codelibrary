#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int p, P[MAX];
bool prime[MAX];

void Sieve(){
    clr(prime);
    int i, j, d;
    const int sqr = ;

    prime[2] = true;
    for (i = 3; i < MAX; i++, i++) prime[i] = true;

    for (i = 3; i < sqr;){
        d = i << 1;
        for (j = (i * i); j < MAX; j += d) prime[j] = false;

        i++, i++;
        while (!prime[i]) i++, i++;
    }

    p = 0;
    for (i = 0; i < MAX; i++){
        if (prime[i]) P[p++] = i;
    }
}

int main(){
    Sieve();
}
