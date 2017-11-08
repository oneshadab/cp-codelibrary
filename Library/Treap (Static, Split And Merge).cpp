#include <bits/stdtr1c++.h>

#define MAXN 200010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl

using namespace std;

int pool_index = 0;

struct node{
    node *l, *r, *parent;
    int key, subtree, priority;

    inline node(){
        l = r = 0, parent = 0;
    }

    inline node(int val){
        l = r = 0, parent = 0;
        subtree = 1, key = val;
        priority = (rand() << 16) ^ rand();
    }

    inline void update(){
        subtree = 1;
        if (l){
            l->parent = this;
            subtree += l->subtree;
        }
        if (r){
            r->parent = this;
            subtree += r->subtree;
        }
    }
} pool[MAXN];

struct Treap{
    struct node* root;

    inline int size(node* &cur){
        if (cur) cur->update();
        return (cur ? cur->subtree : 0);
    }

    inline int size(){
        return (root ? root->subtree : 0);
    }

    inline void merge(node* &cur, node* l, node* r){
        if (!l || !r) cur = l ? l : r;
        else if (l->priority > r->priority) merge(l->r, l->r, r), cur = l;
        else merge(r->l, l, r->l), cur = r;
        if (cur) cur->update();
    }

    void split(node* cur, node* &l, node* &r, int key) {
        l = 0, r = 0;
        if (!cur) return;

        if (cur->key < key) {
            l = cur;
			split(l->r, l->r, r, key);
			l->update();
        }
        else{
            r = cur;
			split(r->l, l, r->l, key);
			r->update();
        }
    }

    void split_index(node* cur, node* &l, node* &r, int index) {
        l = 0, r = 0;
        if (!cur) return;

        if (size(cur->l) < index) {
            l = cur;
            split_index(l->r, l->r, r, index - size(cur->l) - 1);
            if (l) l->update();
        }
        else {
            r = cur;
            split_index(r->l, l, r->l, index);
            if (r) r->update();
        }
    }

    Treap(){
        root = 0;
        pool_index = 0; /// Remove if multiple copies of treap required at the same time
    }

    inline void insert(int key){
        node* l, *r;
        split(root, l, r, key);
        pool[pool_index] = node(key);
        merge(root, l, &pool[pool_index++]);
        merge(root, root, r);
    }

    inline bool erase(int key){
        node *l, *r, *m;
        split(root, l, r, key);
        split_index(r, m, r, 1);
        bool res = (m && m->key == key);
        if (!res) merge(r, m, r);
        merge(root, l, r);
        return res;
    }

    inline int rank(node* cur){ /// rank of node in the treap
        int res = 1 + size(cur->l);
        while (cur->parent){
            if (cur->parent->r == cur) res += (size(cur->parent->l) + 1);
            cur = cur->parent;
        }
        return res;
    }

    /// Returns the k'th smallest element of treap in 1-based index, -1 on failure
    inline int kth(int k){
        if ((k < 1) || (k > size())) return -1;

        node *l, *r, *m;
        split_index(root, l, r, k);
        split_index(l, l, m, l->subtree - 1);
        int res = m->key;
        merge(l, l, m);
        merge(root, l, r);
        return res;
    }

    /// Returns the count of keys less than x in treap
    inline int count(int key){
        node *l, *r, *cur = root;
        split(root, l, r, key);
        int res = (l ? l->subtree : 0);
        merge(root, l, r);
        return res;
    }
};

int main(){
    char str[10];
    int n, i, j, x, res;
    tr1::unordered_set <int> S;

    scanf("%d", &n);
    Treap T = Treap();
    while (n--){
        scanf("%s %d", str, &x);
        if (str[0] == 'I' && !S.count(x)) S.insert(x), T.insert(x);
        if (str[0] == 'D') S.erase(x), T.erase(x);
        if (str[0] == 'C') printf("%d\n", T.count(x));
        if (str[0] == 'K'){
            res = T.kth(x);
            if (res == -1) puts("invalid");
            else printf("%d\n", res);
        }
    }
    return 0;
}
