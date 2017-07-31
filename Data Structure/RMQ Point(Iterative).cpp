#include <bits/stdc++.h>

using namespace std;

struct RMQ {
    vector<int> t;
    int n;

    void build(int *A, int n) {
        this->n = n;
        t.assign(2 * n, 0);
        for (int p = n - 1; p >= 0; p--) t[p + n] = A[p];
        for (int p = n - 1; p >= 0; p--) t[p] = min(t[p << 1], t[p << 1 | 1]);
    }

    void update(int p, int val) {
        for (t[p += n] = val; p >>= 1;) {
            t[p] = min(t[p << 1], t[p << 1 | 1]);
        }
    }

    int query(int L, int R) {
        int res = t[n + L];
        //n+1 for exclusivity [L, R)
        for (L += n, R += n + 1; L < R; L >>= 1, R >>= 1) {
            if (L & 1) res = min(res, t[L++]);
            if (R & 1) res = min(t[--R], res);
        }
        return res;
    }
};

int main() {
    int A[] = {10, 3, 4, 5, 2};
    RMQ t;
    t.build(A, 5);
    cout << t.query(0, 4);
}


