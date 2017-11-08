#include <bits/stdtr1c++.h>

#define MAX 200010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

int n, q;
long long ar[MAX];

/// Look thoroughly for a change
struct SegTree{
    int n;

    struct Node{
        long long a, d, inc, val;

        Node(){
        }

        Node(vector <int> ar){
            a = ar[0], d = ar[1], inc = ar[2], val = ar[3];
        }
    } tree[MAX << 2], nil = Node({0, 0, 0, 0}); /// If runtime error, replace array with vector
    /// nil should be chosen properly


    SegTree(){
    }

    SegTree(int m){
        n = m;
        for (int i = 0; i <= (n << 2); i++) tree[i] = nil; /// Tree initialization
    }

    long long F(long long a, long long d, long long inc, long long n){
        long long res = 0;
        while (n--){
            res += a;
            a += d;
            d += inc;
        }
        return res;
    }

    /// Add to information to left(ld) and right(rd) child ld and rd using information from data
    /// l = number of elements to be updated in ld, r = number of elements to be updated in rd
    void split(int l, int r, struct Node& data, struct Node& ld, struct Node& rd){
        ld.a += data.a, ld.d += data.d, ld.inc += data.inc;
        long long m = l + 1;
        rd.a += ( data.a + ((m - 1) * data.d) + ((((m - 1) * (m - 2)) >> 1) * data.inc) );
        rd.d += (data.d + (data.inc * (m - 1))), rd.inc += data.inc;
    }

    /// Update tree node during segment tree update
    void update_node(int idx, int a, int b, int l, int r, struct Node& data){
        tree[idx].a += data.a, tree[idx].d += data.d, tree[idx].inc += data.inc;
    }

    /// Update parent from left and right child
    void update_parent(int idx, int p, int q){
        tree[idx].val = tree[p].val + tree[q].val;
    }

    void propagate(int idx, int a, int b, int counter){
        if (tree[idx].a){
            int p = (idx << 1), q = p | 1;
            int c = (a + b) >> 1, d = c + 1;
            tree[idx].val = tree[idx].val + F(tree[idx].a, tree[idx].d, tree[idx].inc, b - a + 1); /// Lazy update node

            if (a != b){
                split((c - a + 1), (d - b + 1), tree[idx], tree[p], tree[q]); /// Propagate lazy values to left and right child

                if (counter--){
                    propagate(p, a, c, counter);
                    propagate(q, d, b, counter);
                }
            }
            tree[idx].a = tree[idx].d = tree[idx].inc = 0; /// Reset lazy values
        }
    }

    void update(int idx, int a, int b, int l, int r, struct Node& data){
        if (a == l && b == r){
            update_node(idx, a, b, l, r, data); /// Update whole segment
            propagate(idx, a, b, 1);
            return;
        }
        propagate(idx, a, b, 1);


        int p = (idx << 1), q = p | 1;
        int c = (a + b) >> 1, d = c + 1;

        if (r <= c){
            propagate(q, d, b, 1);
            update(p, a, c, l, r, data);
        }
        else if (l >= d){
            propagate(p, a, c, 1);
            update(q, d, b, l, r, data);
        }
        else{
            struct Node ld = nil, rd = nil;
            split((c - l + 1), (r - d + 1), data, ld, rd);
            update(p, a, c, l, c, ld);
            update(q, d, b, d, r, rd);
        }

        update_parent(idx, p, q); /// Update current node using information from left and right child
    }

    void update(int l, int r){
        struct Node data = Node({2, 4, 2, 0}); /// Change accordingly
        update(1, 1, n, l, r, data);
    }

    long long query(int idx, int a, int b, int l, int r){
        int p = (idx << 1), q = p + 1;
        int c = (a + b) >> 1, d = c + 1;

        propagate(idx, a, b, 1);
        if (a == l && b == r) return tree[idx].val;
        if (r <= c) return query(p, a, c, l, r);
        else if (l >= d) return query(q, d, b, l, r);
        else{
            long long x = query(p, a, c, l, c);
            long long y = query(q, d, b, d, r);
            return (x + y); /// Change accordingly
        }
    }

    long long query(int l, int r){
        return query(1, 1, n, l, r);
    }
};

void run(){
    int flag, i, l, r;
    struct SegTree S = SegTree(n);

    while (q--){
        scanf("%d %d %d", &flag, &l, &r);
        if (flag == 1){
            S.update(l, r);
        }
        else printf("%lld\n", S.query(l, r));
    }
}

int main(){
    while (scanf("%d %d", &n, &q) != EOF){
        run();
    }
    return 0;
}
