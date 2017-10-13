#include <bits/stdc++.h>

using namespace std;

#define FOR(i, N) FORR(i, 0, N)
#define FORR(i, a, b) FOTR(i, a, b, 1)
#define FOTR(i, a, b, c) for(int i=(a);i<(b);i+=(c))
#define MEM(a, x) memset(a,x,sizeof(a))
#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}
#define INF 1000000000
#define MAX 70000
#define MOD 1000000007
typedef long long ll;

struct item {
    int x, y1, y2, type;

    bool operator<(const item &a) const {
        if (x == a.x)return type > a.type;
        return x < a.x;
    }
} items[MAX];

int A[MAX];
int tree[MAX * 2][2];

void update(int node, int first, int last, int l, int r, int v) {
    int mid = (first + last) >> 1, ch1 = node << 1, ch2 = ch1 | 1;
    if (first >= l && last <= r) {
        tree[node][1] += v;
        if (tree[node][1]) {
            tree[node][0] = A[last - 1] - A[first - 2];
        } else {
            if (first != last)tree[node][0] = tree[ch1][0] + tree[ch2][0];
            else tree[node][0] = 0;
        }
        return;
    }
    if (r <= mid) update(ch1, first, mid, l, r, v);
    else if (l > mid) update(ch2, mid + 1, last, l, r, v);
    else {
        update(ch1, first, mid, l, r, v);
        update(ch2, mid + 1, last, l, r, v);
    }
    if (tree[node][1])tree[node][0] = A[last - 1] - A[first - 2];
    else tree[node][0] = tree[ch1][0] + tree[ch2][0];
}

int main() {
    int T, n, x1, y1, x2, y2;
    scanf("%d", &T);
    FOR(cs, T) {
        MEM(tree, 0);
        map<int, int> mp;
        scanf("%d", &n);
        FOR(i, n) {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            int ch1 = (i << 1), ch2 = ch1 | 1;
            items[ch1].x = x1, items[ch1].y1 = y1, items[ch1].y2 = y2, items[ch1].type = 0;
            items[ch2].x = x2, items[ch2].y1 = y1, items[ch2].y2 = y2, items[ch2].type = 1;
            A[ch1] = y1;
            A[ch2] = y2;
        }

        sort(items, items + n * 2);
        sort(A, A + n * 2);
        int j = 0;
        FOR(i, n * 2) {
            if (mp[A[i]] == 0) {
                mp[A[i]] = j + 1;
                A[j] = A[i];
                j++;
            }
        }
        ll ans = 0, p = 0;
        FOR(i, n * 2) {
            x1 = items[i].x;
            ans += tree[1][0] * (x1 - p) * 1LL;
            do {
                if (items[i].y1 != items[i].y2) {
                    if (items[i].type)
                        update(1, 1, j, mp[items[i].y1] + 1, mp[items[i].y2], -1);
                    else update(1, 1, j, mp[items[i].y1] + 1, mp[items[i].y2], 1);
                }
                i++;
            } while (i < n * 2 && items[i].x == x1);
            i--;
            p = x1;
        }
        printf("Case %d: %lld\n", cs + 1, ans);
    }
}