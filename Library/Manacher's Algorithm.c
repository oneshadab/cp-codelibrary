#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int n, m, L[(MAX << 1) + 5];
char str[MAX], T[(MAX << 1) + 5];

void Manacher(char* str){
    int i, c, r, l;
    n = strlen(str), m = (n << 1) + 3;
    T[0] = 64, T[m - 1] = 36, T[m - 2] = 35, T[m] = 0;

    for (i = 0; i < n; i++){
        T[(i << 1) + 1] = 35;
        T[(i + 1) << 1] = str[i];
    }

    c = r = L[0] = 0;
    for (i = 1; i < m; i++){
        L[i] = 0;
        l = (c << 1) - i;
        if (r > i) L[i] = (L[l]<(r - i)) ? L[l]:(r - i);
        while (T[i + 1 + L[i]] == T[i - 1 - L[i]]) L[i]++;

        if ((i + L[i]) > r){
            c = i;
            r = i + L[i];
        }
    }
}

int main(){
    while (scanf("%s", str) != EOF){
        Manacher(str);
    }
    return 0;
}
