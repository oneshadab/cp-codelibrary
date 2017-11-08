#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1010
#define clr(ar) (memset(ar, 0, sizeof(ar)))
#define read() freopen("lol.txt", "r", stdin)

bool bfs_vis[MAX];
int t, n, m, ar[MAX][MAX], len[MAX], left[MAX], right[MAX], Q[MAX], dis[MAX], parent[MAX];

bool dfs(int i){
    int j, x;

    for (j = 0; j < len[i]; j++){
        x = ar[i][j];
        if (left[x] == -1 || (parent[left[x]] == i)){
            if (left[x] == -1 || dfs(left[x])){
                left[x] = i;
                right[i] = x;
                return true;
            }
        }
    }
    return false;
}

bool bfs(){
    clr(bfs_vis);
    int i, j, x, d, f = 0, l = 0;

    for (i = 0; i < n; i++){
        if (right[i] == -1){
            Q[l++] = i;
            dis[i] = 0;
            bfs_vis[i] = true;
        }
    }

    while (f < l){
        i = Q[f++];

        for (j = 0; j < len[i]; j++){
            x = ar[i][j];
            d = left[x];
            if (d == -1) return true;

            else if (!bfs_vis[d]){
                Q[l++] = d;
                parent[d] = i;
                bfs_vis[d] = true;
                dis[d] = dis[i] + 1;
            }
        }
    }
    return false;
}

int hopcroft_karp(){
    int i, j, counter = 0;
    memset(left, -1, sizeof(left));
    memset(right, -1, sizeof(right));

    while (bfs()){
        for (i = 0; i < n; i++){
            if (right[i] == -1 && dfs(i)) counter++;
        }
    }
    return counter;
}

int main(){
    int i, a, b;

    while (scanf("%d %d", &n, &m) != EOF){
        clr(len);
        for (i = 0; i < m; i++){
            scanf("%d %d", &a, &b);
            ar[a][len[a]++] = b;
        }
    }
    return 0;
}
