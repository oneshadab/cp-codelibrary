#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LET 26
#define MAX 405
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int id, Q[MAX], fail[MAX], lethash[256], trie[MAX][LET];

int node(){
    clr(trie[id]);
    fail[id] = 0;
    return id++;
}

void init(){
    for (id = 'a'; id <= 'z'; id++) lethash[id] = id - 'a';
    id = 0, node();
}

void insert(char* str, int i){
    int j, x, cur = 0;
    for (j = 0; str[j] != 0; j++){
        x = lethash[str[j]];
        if (!trie[cur][x]) trie[cur][x] = node();
        cur = trie[cur][x];
    }
}

void build(){
    int i, j, x, f = 0, l = 0;
    for (i = 0; i < LET; i++){
        if (trie[0][i]) Q[l++] = trie[0][i];
    }

    while (f < l){
        for (j = 0, i = Q[f++]; j < LET; j++){
            if (trie[i][j] == 0) trie[i][j] = trie[fail[i]][j];
            else{
                fail[trie[i][j]] = trie[fail[i]][j];
                Q[l++] = trie[i][j];
            }
        }
    }
}

int main(){
}
