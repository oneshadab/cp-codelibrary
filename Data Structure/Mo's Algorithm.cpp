#include <bits/stdc++.h>

using namespace std;

#define MAX 105000
#define read() freopen("input.txt", "r", stdin)
#define MEM(a, x) memset(a, x, sizeof(a))

struct query_t {
    int x, y, block, idx, ans;

    static bool sortByBlock(const query_t &a, const query_t &b) {
        if (a.block == b.block) {
            return a.y < b.y;
        }
        return a.block < b.block;
    }

    static bool sortByIdx(const query_t &a, const query_t &b) {
        return a.idx < b.idx;
    }
};

int N, M;
int A[MAX + 100];
query_t Q[MAX + 100];
int MP[MAX + 100];
int L, R;
int ANS;

void process(int i) {
    Q[i].ans = 0;
    while (L > Q[i].x) {
        L -= 1;
        MP[A[L]] += 1;
        if (MP[A[L]] == 1) {
            ANS += 1;
        }
    }
    while (R <= Q[i].y) {
        MP[A[R]] += 1;
        if (MP[A[R]] == 1) {
            ANS += 1;
        }
        R += 1;
    }
    while (L < Q[i].x) {
        MP[A[L]] -= 1;
        if (MP[A[L]] == 0) {
            ANS -= 1;
        }
        L += 1;
    }
    while (R > Q[i].y + 1) {
        R -= 1;
        MP[A[R]] -= 1;
        if (MP[A[R]] == 0) {
            ANS -= 1;
        }
    }
    Q[i].ans = ANS;
}

int main() {
    //read();
    int TC;
    scanf("%d", &TC);
    for (int cs = 1; cs <= TC; cs++) {
        ANS = L = R = 0;
        MEM(MP, 0);
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N; i++) {
            scanf("%d", &A[i]);
        }
        int sqN = sqrt(N);
        for (int i = 1; i <= M; i++) {
            scanf("%d%d", &Q[i].x, &Q[i].y);
            Q[i].idx = i;
            Q[i].block = Q[i].x / sqN;
        }
        sort(Q + 1, Q + M + 1, query_t::sortByBlock);
        for (int i = 1; i <= M; i++) {
            process(i);
        }
        sort(Q + 1, Q + M + 1, query_t::sortByIdx);
        printf("Case %d:\n", cs);
        for (int i = 1; i <= M; i++) {
            printf("%d\n", Q[i].ans);
        }
    }
}
