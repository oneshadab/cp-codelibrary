// COMMENTS
/* ****** 0 based BIT ******
 * Source: http://code-library.herokuapp.com/fenwick-tree-extended/java
 * There are 3 kinds of BIT functions based on query and update:
 * 1. Point Update Range Query (PURQ)
 * 2. Range Update Point Query (RUPQ)
 * 3. Range Update Range Query (RURQ)
 */
// _COMMENTS

#include <bits/stdc++.h>

using namespace std;

#define MEM(a,x) memset(a,x,sizeof(a))
#define MAX 100010
#define ll long long

struct BIT_PURQ{
    ll bit[MAX]; int N;

    void init(int n){ MEM(bit, 0); N=n; }

    void create_from_vector(vector<int> a) {
        for (int i = 0; i < N; i++) {
            bit[i] += a[i];
            int j = i | (i + 1);
            if (j < N) bit[j] += bit[i];
        }
    }
    // bit[i] += value
    void add(int i, ll value) {
        for (; i < N; i |= i + 1)
            bit[i] += value;
    }
    // sum[0..i]
    ll sum(int i) {
        ll res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += bit[i];
        return res;
    }
    // sum[a..b]
    ll sum(int a, int b) {
        return sum(b) - sum(a - 1);
    }
    // value of bit[index]
    ll get(int i) {
        return sum(i) - sum(i-1);
    }
    // bit[index] = value
    void set_v(int i, ll value) {
        add(i, -get(i) + value);
    }
};

struct BIT_RUPQ{
    ll bit[MAX]; int N;

    void init(int n){ MEM(bit, 0); N=n; }

    void create_from_vector(vector<int> a) {
        for (int i = 0; i < N; i++) {
            bit[i] += a[i];
            int j = i | (i + 1);
            if (j < N) bit[j] += bit[i];
        }
    }
    // bit[i] += value
    void add(int i, ll value) {
        for (; i < N; i |= i + 1)
            bit[i] += value;
    }
    // *use this add*
    void add(int a, int b, ll value) {
        add(a, value);
        add(b + 1, -value);
    }
    // return value of bit[i]
    ll get(int i) {
        ll res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += bit[i];
        return res;
    }
};

struct BIT_RURQ{
    ll bit1[MAX], bit2[MAX]; int N;

    void init(int n){ MEM(bit1, 0); MEM(bit2, 0); N=n; }

    void add(ll *bit, int i, ll value) {
        for (; i < N; i |= i + 1)
            bit[i] += value;
    }
    ll sum(ll *bit, int i) {
        ll res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += bit[i];
        return res;
    }
    // add 'value' to each element, from a to b; *use this in code*
    void add(int a, int b, ll value) {
        add(bit1, a, value);
        add(bit1, b, -value);
        add(bit2, a, -value * (a - 1));
        add(bit2, b, value * b);
    }
    // sum[0...i]
    ll sum(int i){
        return (sum(bit1, i) * i + sum(bit2, i));
    }
    // sum[a...b]; *use this in code*
    ll sum(int a, int b) {
        a--;
        return sum(b) - ((a<0)?0: sum(a));
    }
};

// Find the smallest index for which sum[0...index]>=value
// Works for BIT_PURQ & BIT_RURQ
int bs_bit(BIT_PURQ bit, ll value){
//int bs_bit(BIT_RURQ bit, ll value){
    int lf=0, rt=bit.N -1, mid;
    while(lf<=rt){
        mid = (lf+rt)>>1;
        ll res = bit.sum(mid);
        if(res == value)return mid;
        else if (res > value) rt = mid-1;
        else lf = mid+1;
    }
    return -1;
}

int main(){

    BIT_PURQ bit_purq;
    BIT_RUPQ bit_rupq;
    BIT_RURQ bit_rurq;

    bit_purq.init(10);
    bit_purq.set_v(5, 1);
    bit_purq.add(9, -2);
    cout<<bit_purq.sum(0, 10)<<"\n";             // -1

    bit_purq.init(6);
    vector<int> v = {1, 2, 3, 4, 5, 6};
    bit_purq.create_from_vector(v);
    for (int i = 0; i < 6; i++)
        cout<<bit_purq.get(i)<<" ";
    cout<<endl;                                 // 1 2 3 4 5 6

    bit_purq.init(8);
    v = {0, 0, 1, 0, 0, 1, 0, 0};
    bit_purq.create_from_vector(v);
    cout<< bs_bit(bit_purq, 2) << "\n";        // 5
    cout<< bs_bit(bit_purq, 3) << "\n";        // -1

    bit_rupq.init(10);
    bit_rupq.add(0, 2, 5);
    bit_rupq.add(2, 4, 5);
    cout<<bit_rupq.get(1) << " " << bit_rupq.get(2)
        << " " << bit_rupq.get(3)<<"\n";       // 5 10 5

    bit_rurq.init(10);
    bit_rurq.add(0, 9, 1);
    bit_rurq.add(0, 0, -2);
    cout<<bit_rurq.sum(0, 9)<<endl;            // 8
}

// SOLVED
/* LightOJ 1112 - Curious Robin Hood (PURQ)
 * SPOJ UPDATEIT (RUPQ)
 * SPOJ HORRIBLE (RURQ) */
// _SOLVED