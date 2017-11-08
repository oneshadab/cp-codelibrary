#include <stdio.h>
#include <bits/stdtr1c++.h>

#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

struct node{
    node *l, *r;
    unsigned int priority;
    long long a, d, n, minval, maxval, tree_size;

    inline node(){
        l = r = 0;
    }

    inline node(long long first_term, long long common_diff, long long nterms){
        l = r = 0;
        if (nterms == 1) common_diff = 1;
        priority = (rand() << 16) ^ rand();
        a = first_term, d = common_diff, n = tree_size = nterms;
        minval = a, maxval = a + (n - 1) * d;
    }

    inline void update(){
        assert(n > 0);
        tree_size = n, minval = a, maxval = a + (n - 1) * d;
        if (l){
            tree_size += l->tree_size;
            minval = min(minval, l->minval);
            maxval = max(maxval, l->maxval);
        }
        if (r){
            tree_size += r->tree_size;
            minval = min(minval, r->minval);
            maxval = max(maxval, r->maxval);
        }
    }
} pool[8000010];

struct Treap{
    int idx;
    struct node* root;

    Treap(long long n){
        idx = 0;
        pool[idx] = node(1, 1, n);
        root = &pool[idx++];
    }

    inline long long size(){
        if (root) return root->tree_size;
        return 0;
    }

    inline long long size(node* &cur){
        if (cur) cur->update();
        return (cur ? cur->tree_size : 0);
    }

    inline void merge(node* &cur, node* l, node* r){
        if (!l || !r) cur = l ? l : r;
        else if (l->priority > r->priority) merge(l->r, l->r, r), cur = l;
        else merge(r->l, l, r->l), cur = r;
        if (cur) cur->update();
    }

    inline void split(node* cur, node* &l, node* &r, long long key, long long counter = 0){
        if (!cur){
            l = r = 0;
            return;
        }

        long long cur_key = counter + (cur->l ? cur->l->tree_size : 0);
        if (key <= cur_key) split(cur->l, l, cur->l, key, counter), r = cur;
        else split(cur->r, cur->r, r, key, cur_key + cur->n), l = cur;
        if (cur) cur->update();
    }

    inline void divide(node* &cur, long long i){
        if (i < 0 || i > size(cur)) return;

        node *l, *r, *m, *t;
        split(cur, l, r, i);
        if (!(!l || size(l) == i)){
            m = l;
            while (m->r) m = m->r;
            long long a = m->a, d = m->d, n = m->n;
            long long c1 = i - (size(l) - m->n), c2 = m->n - c1;

            split(l, l, t, size(l) - m->n);
            pool[idx] = node(a, d, c1);
            merge(l, l, &pool[idx++]);
            pool[idx] = node(a + c1 * d, d, c2);
            merge(l, l, &pool[idx++]);
        }
        merge(cur, l, r);
    }

    inline long long calc_pos(long long n, long long k){
        if (n % k == 0) return 0;
        if ((n - 1) % k == 0) return k - 1;
        long long x = n - (((n / k) * k) + 1);
        return k - 1 - x;
    }

    inline node* erase(node* cur, long long k, long long& pos){
        node *l, *r, *t1, *t2;
        split(cur, l, cur, size(cur->l));
        split(cur, cur, r, cur->n);

        if (l) l = erase(l, k, pos);
        if (pos >= cur->n){
            pos -= cur->n;
            if (r) r = erase(r, k, pos);
            merge(cur, l, r);
            return cur;
        }

        divide(cur, pos);
        split(cur, t1, t2, pos);

        long long n = t2->n;
        pos = calc_pos(n, k);
        pool[idx]= node(t2->a, t2->d * k, ((t2->n - 1) / k) + 1);

        merge(l, l, &pool[idx++]);
        if (r) r = erase(r, k, pos);
        merge(l, l, r);
        return l;
    }

    /// Keep the a, a + k, a + 2*k, ... b terms and delete all the rest from the segment
    inline void erase(long long a, long long b, long long k){
        node *l, *r, *m;
        long long pos = 0;
        divide(root, a - 1);
        split(root, l, r, a - 1);
        divide(r, b - a + 1);
        split(r, m, r, b - a + 1);
        m = erase(m, k, pos);
        merge(l, l, m);
        merge(root, l, r);
    }

    inline void erase(long long i){
        node *l, *r, *m;
        divide(root, i - 1);
        split(root, l, r, i - 1);
        divide(r, 1);
        split(r, m, r, 1);
        merge(root, l, r);
    }

    inline node query(long long a, long long b){
        node *l, *r, *m;
        divide(root, a - 1);
        split(root, l, r, a - 1);
        divide(r, b - a + 1);
        split(r, m, r, b - a + 1);
        node res = *m;
        merge(l, l, m);
        merge(root, l, r);
        return res;
    }
};

int main(){
    long long q, n, l, r;

    while (scanf("%lld %lld", &q, &n) != EOF){
        if (q == 0 && n == 0) break;

        Treap T = Treap(n);
        long long total = n;
        while (q--){
            scanf("%lld %lld", &l, &r);
            node res = T.query(l, r);
            printf("%lld %lld\n", res.minval, res.maxval);

            T.erase(l);
            if ((l + 1) <= r) T.erase(l, r - 1, 2);
        }
    }
    return 0;
}
