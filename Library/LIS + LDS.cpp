#include <bits/stdtr1c++.h>

#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

int* LIS(int n, int ar[]){
    int* lis = new int[n + 10];
    int* val = new int[n + 10];

    int i, d, len = 0;
    lis[0] = 1, val[len++] = ar[0];

    for (i = 1; i < n; i++){
        d = lower_bound(val, val + len, ar[i]) - &val[0];
        lis[i] = d + 1;
        if (d == len) val[len++] = ar[i];
        else val[d] = ar[i];
    }

    return lis;
}

int* LDS(int n, int ar[]){
    for (int i = 0; i < n; i++) ar[i] = INT_MAX - ar[i];
    reverse(ar, ar + n);
    int* lds = LIS(n, ar);

    reverse(lds, lds + n);
    reverse(ar, ar + n);
    for (int i = 0; i < n; i++) ar[i] = INT_MAX - ar[i];

    return lds;
}

int main(){
    int n, i, j, k, m;

    while (scanf("%d", &n) != EOF){
        int* ar = new int[n + 10];
        for (int i = 0; i < n; i++) scanf("%d", &ar[i]);

        int* lis = LIS(n, ar);
        int* lds = LDS(n, ar);
    }
    return 0;
}

