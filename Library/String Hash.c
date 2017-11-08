#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000010
#define min(a,b) ((a)<(b)?(a):(b))
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

const unsigned long long base = 1925728309;

int n;
char str[MAX];
unsigned long long ar[3][MAX];

void Generate(char* str, int n, unsigned long long ar[3][MAX]){
    int i;
    unsigned long long x;

    ar[0][0] = 1;
    for (i = 1; i <= n; i++) ar[0][i] = (ar[0][i - 1] * base);

    x = 0;
    for (i = 0; i < n; i++){
        x = (x * base) + str[i];
        ar[1][i] = x;
    }

    x = 0;
    for (i = n - 1; i >= 0; i--){
        x = (x * base) + str[i];
        ar[2][i] = x;
    }
}

unsigned long long forward_hash(int i, int j, unsigned long long ar[3][MAX], int n){
    unsigned long long x = ar[1][j];
    if (i){
        unsigned long long y = ar[0][j - i + 1] * ar[1][i - 1];
        x -= y;
    }
    return x;
}

unsigned long long reverse_hash(int i, int j, unsigned long long ar[3][MAX], int n){
    unsigned long long x = ar[2][i];
    if ((j + 1) != n){
        unsigned long long y = ar[0][j - i + 1] * ar[2][j + 1];
        x -= y;
    }
    return x;
}

int main(){
}
