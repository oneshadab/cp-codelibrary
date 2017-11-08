#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int phi[MAX];
short P[MAX] = {0};

void Generate(){
    int i, j, k, d, x;

    P[0] = P[1] = 1;
    for (i = 4; i < MAX; i++, i++) P[i] = 2;

    for (i = 3; i * i < MAX;){
        d = i << 1;
        for (j = (i * i); j < MAX; j += d) P[j] = i;
        do{
            i++;
        } while (P[++i]);
    }

    phi[1] = 1;
    for (i = 2; i < MAX; i++){
        if (!P[i]) phi[i] = i - 1;
        else{
            k = i / P[i];
            if (!(k % P[i])) phi[i] = phi[k] * P[i];
            else phi[i] = phi[k] * (P[i] - 1);
        }
    }
}

int main(){
    Generate();
    return 0;
}
