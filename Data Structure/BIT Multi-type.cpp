#include <bits/stdc++.h>

using namespace std;

#define MEM(a,x) memset(a,x,sizeof(a))
#define MAX 300001
#define ll long long

//COMMENTS
/* ****** 0 based BIT ******
 * There are 3 kinds of BIT functions based on query and update:
 * 1. Point Update Range Query (PURQ)
 * 2. Range Update Point Query (RUPQ)
 * 3. Range Update Range Query (RURQ)
 * Only one kind of functions will work at a given time. I.e. you can not use PURQ functions
 * and then use RUPQ functions in a single code. */
//_COMMENTS

struct BIT{
    ll bit[MAX], bit1[MAX]; int N;

    void init(int n, bool resetRURQ){
        MEM(bit, 0);
        if(resetRURQ)MEM(bit1,0);
        N=n;
    }
    void create_from_vector(vector<int> a) {
        for (int i = 0; i < N; i++) {
            bit[i] += a[i];
            int j = i | (i + 1);
            if (j < N)
                bit[j] += bit[i];
        }
    }
    //return min P where sum bit[0..p]

    /****** Point Update Range Query ******/
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

    /****** Range Update Point Query ******/
    // add 'value' to each element of bit, from a to b
    void add(int a, int b, ll value) {
        add(a, value);
        add(b + 1, -value);
    }
    // return value of bit[i]
    ll get_rupq(int i) {
        return sum(i);
    }

    /****** Range Update Range Query ******/
    // (bit array passed) bit[index] += value
    void add(ll *bit, int i, ll value) {
        for (; i < N; i |= i + 1)
            bit[i] += value;
    }
    // (bit array passed) sum[0..i]
    ll sum(ll *bit, int i) {
        ll res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1)
            res += bit[i];
        return res;
    }
    // add 'value' to each element, from a to b
    void add_rurq(int a, int b, ll value) {
        add(bit, a, value);
        add(bit, b, -value);
        add(bit1, a, -value * (a - 1));
        add(bit1, b, value * b);
    }
    // sum[0...i]
    ll sum_from_zero(int i){
        return (sum(bit, i) * i + sum(bit1, i));
    }
    // sum[a...b]
    ll sum_rurq(int a, int b) {
        a--;
        return sum_from_zero(b) - ((a<0)?0:sum_from_zero(a));
    }

    /*** Binary search on bit: find min p where sum[0..p] >= value ***/
    int bs_bit(ll value){
        int lf=0, rt=N-1, mid;
        while(lf<=rt){
            mid = (lf+rt)>>1;
            ll res = sum(mid);
            if(res == value)return mid;
            else if (res > value) rt = mid-1;
            else lf = mid+1;
        }
        return -1;
    }
};

BIT bit;
int main(){
    bit.init(10, false);
    bit.set_v(5, 1);
    bit.add(9, -2);
    cout<<bit.sum(0, 10)<<"\n";           // -1

    bit.init(6, false);
    vector<int> v = {1, 2, 3, 4, 5, 6};
    bit.create_from_vector(v);
    for (int i = 0; i < 6; i++)
        cout<<bit.get(i)<<" ";
    cout<<endl;                           // 1 2 3 4 5 6

    bit.init(8, false);
    v = {0, 0, 1, 0, 0, 1, 0, 0};
    bit.create_from_vector(v);
    cout<< bit.bs_bit(2) << "\n";        // 5
    cout<< bit.bs_bit(3) << "\n";        // -1

    bit.init(10, false);
    bit.add_rurq(0, 9, 1);
    bit.add_rurq(0, 0, -2);
    cout<<bit.sum_rurq(0, 9)<<endl;      // 8
}


// SOLVED
/* LightOJ 1112 - Curious Robin Hood (PURQ)
 * SPOJ UPDATEIT (RUPQ)
 * SPOJ HORRIBLE (RURQ) */
// _SOLVED