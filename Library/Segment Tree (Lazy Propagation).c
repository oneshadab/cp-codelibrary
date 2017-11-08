#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)

int n, q;
int tree[MAX << 2], lazy[MAX << 2];

void propagate(int idx, int a, int b){
    if (lazy[idx]){
        int p = (idx << 1), q = p + 1;
        int c = (a + b) >> 1, d = c + 1;

        tree[idx] += (lazy[idx] * (b - a + 1));
        if (a != b){
            lazy[p] += lazy[idx];
            lazy[q] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int* tree, int* lazy, int idx, int a, int b, int l, int r, int x){
    int p = (idx << 1), q = p + 1;
    int c = (a + b) >> 1, d = c + 1;

    if (a == l && b == r) lazy[idx] += x;
    propagate(idx, a, b);
    if (a == l && b == r) return;

    if (r <= c){
        propagate(q, d, b);
        update(tree, lazy, p, a, c, l, r, x);
    }
    else if (l >= d){
        propagate(p, a, c);
        update(tree, lazy, q, d, b, l, r, x);
    }
    else{
        update(tree, lazy, p, a, c, l, c, x);
        update(tree, lazy, q, d, b, d, r, x);
    }

    tree[idx] = tree[p] + tree[q];
}

int query(int* tree, int* lazy, int idx, int a, int b, int l, int r){
    int p = (idx << 1), q = p + 1;
    int c = (a + b) >> 1, d = c + 1;

    propagate(idx, a, b);
    if (a == l && b == r) return tree[idx];
    if (r <= c) return query(tree, lazy, p, a, c, l, r);
    else if (l >= d) return query(tree, lazy, q, d, b, l, r);
    else{
        int x = query(tree, lazy, p, a, c, l, c);
        int y = query(tree, lazy, q, d, b, d, r);
        return (x + y);
    }
}

void update_range(int l, int r, int v){
    update(tree, lazy, 1, 1, n, l, r, v);
}

int query_range(int l, int r){
    return query(tree, lazy, 1, 1, n, l, r);
}

int main(){
}
