#include <bits/stdtr1c++.h>

#define MAXN 3000010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))

using namespace std;

struct node{
    bool rev;
    node *l, *r;
    long long pref, suf, res, sum;
    int val, counter, subtree, priority;

    inline node(){
        l = r = 0;
    }

    inline node(int v, int c, int p){
        l = r = 0;
        priority = p;
        subtree = c, counter = c;
        val = pref = suf = res = sum = v, rev = false;
    }

    inline node(int v, int c){
        node(v, c, (rand() << 16) ^ rand());
    }

    inline void update(){
        subtree = counter;
        if (l) subtree += l->subtree;
        if (r) subtree += r->subtree;
    }
} zero, pool[MAXN]; /// Maximum number of nodes in treap

struct Treap{
    int idx;
    struct node* root;

    inline void push(node* cur){ /// Lazy propagation
        if (cur) cur->update();
        if (cur && cur->rev){
            cur->rev = false;
            if (cur->l) cur->l->rev ^= true;
            if (cur->r) cur->r->rev ^= true;
            swap(cur->l, cur->r);
            swap(cur->pref, cur->suf); /// Exchange maximum prefix sum and maximum suffix sum because of reversal
        }
    }

    inline void join(node* cur){ /// Update node from its children
        if (!cur) return;

        push(cur);
        node* l = &zero, *r = &zero;
        if (cur->l) push(cur->l), l = cur->l;
        if (cur->r) push(cur->r), r = cur->r;
        long long x = (long long)cur->val * cur->counter;
        long long y = max(x, (long long)cur->val);

        cur->res = y;
        cur->sum = x + l->sum + r->sum;
        cur->suf = (cur->r ? r->suf : y);
        cur->pref = (cur->l ? l->pref : y);
        cur->suf = max(cur->suf, max(r->sum + y, r->sum + x + max(0LL, l->suf)));
        cur->pref = max(cur->pref, max(l->sum + y, l->sum + x + max(0LL, r->pref)));

        if (cur->l) cur->res = max(cur->res, max(l->res, max(0LL, l->suf) + y));
        if (cur->r) cur->res = max(cur->res, max(r->res, max(0LL, r->pref) + y));
        cur->res = max(cur->res, max(0LL, l->suf) + x + max(0LL, r->pref));
    }

    inline void merge(node* &cur, node* l, node* r){
        push(l), push(r); /// Lazy propagation
        if (!l || !r) cur = l ? l : r;
        else if (l->priority > r->priority) merge(l->r, l->r, r), cur = l;
        else merge(r->l, l, r->l), cur = r;
        if (cur) join(cur);
    }

    /// Smallest v such that l->subtree = v and v >= key
    inline void split(node* cur, node* &l, node* &r, int key, int counter = 0){
        if (!cur){
            l = r = 0;
            return;
        }

        push(cur); /// Lazy propagation
        int cur_key = counter + (cur->l ? cur->l->subtree : 0);
        if (key <= cur_key) split(cur->l, l, cur->l, key, counter), r = cur;
        else split(cur->r, cur->r, r, key, cur_key + cur->counter), l = cur;
        if (cur) join(cur);
    }

    inline void divide(node* &cur, int k){ /// Slices the segment containing first k numbers
        node *l, *r, *m, *t = 0;
        split(cur, l, r, k);
        if (!(!l || l->subtree == k)){
            m = l;
            while (m->r) m = m->r;
            int v = m->val, c1 = k - (l->subtree - m->counter), c2 = m->counter - c1;

            split(l, l, t, l->subtree - m->counter);
            t = &pool[idx++];
            *m = node(v, c1);
            *t = node(v, c2);
            merge(l, l, m);
            merge(l, l, t);

        }
        merge(cur, l, r);
    }

    inline node* build(int i, int j, int* ar){ /// Builds implicit treap from array in O(n)
        int k = (i + j) >> 1;
        pool[idx] = node(ar[k], 1, (j - i + 1));
        node *cur = &pool[idx++];
        if (i < k) cur->l = build(i, k - 1, ar);
        if (j > k) cur->r = build(k + 1, j, ar);
        join(cur);
        return cur;
    }

    inline void insert(int i, int v, int c){ /// Inserts c copies of v after position i
        divide(root, i);
        node *l, *r, *m;
        split(root, l, r, i);
        pool[idx] = node(v, c);
        merge(l, l, &pool[idx++]);
        merge(root, l, r);
    }

    inline void insert(int i, node* cur){ /// Inserts node cur after position i
        divide(root, i);
        node *l, *r, *m;
        split(root, l, r, i);
        merge(l, l, cur);
        merge(root, l, r);
    }

    inline void erase(int a, int b){ /// Removes the segment [a:b]
        node *l, *r, *m;
        divide(root, a - 1);
        split(root, l, r, a - 1);
        divide(r, b - a + 1);
        split(r, m, r, b - a + 1);
        merge(root, l, r);
    }

    inline void reverse(int a, int b){ /// Reverses the segment [a:b]
        node *l, *r, *m;
        divide(root, a - 1);
        split(root, l, r, a - 1);
        divide(r, b - a + 1);
        split(r, m, r, b - a + 1);
        m->rev ^= true;
        merge(l, l, m);
        merge(root, l, r);
    }

    inline void replace(int a, int b, int c){ /// Replaces all values of the segment [a:b] with c
        node *l, *r, *m;
        divide(root, a - 1);
        split(root, l, r, a - 1);
        divide(r, b - a + 1);
        split(r, m, r, b - a + 1);
        *m = node(c, b - a + 1);
        merge(l, l, m);
        merge(root, l, r);
    }

    inline long long getsum(int a, int b){ /// sum of numbers in the segment [a:b]
        if (a > b) return 0;
        node *l, *r, *m;
        divide(root, a - 1);
        split(root, l, r, a - 1);
        divide(r, b - a + 1);
        split(r, m, r, b - a + 1);
        long long res = m->sum;
        merge(l, l, m);
        merge(root, l, r);
        return res;
    }

    inline long long getmaxsum(int a, int b){ /// Maximum sum of any non-empty contiguous subsequence of the segment [a:b]
        if (a > b) return 0;
        node *l, *r, *m;
        divide(root, a - 1);
        split(root, l, r, a - 1);
        divide(r, b - a + 1);
        split(r, m, r, b - a + 1);
        long long res = m->res;
        merge(l, l, m);
        merge(root, l, r);
        return res;
    }

    inline long long getmaxsum(){ /// Maximum sum of any non-empty contiguous subsequence of the array
        return root->res;
    }

    Treap(){
        idx = 0, root = 0;
        zero = node(0, 0);
    }

    inline int size(){
        if (root) return root->subtree;
        return 0;
    }

    inline void dfs(node* cur){
        if (!cur) return;
        push(cur); /// Lazy propagation
        dfs(cur->l);
        for (int i = 0; i < cur->counter; i++) printf("%d ", cur->val);
        dfs(cur->r);
    }
};

int main(){

}
