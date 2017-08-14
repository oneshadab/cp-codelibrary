#include <bits/stdc++.h>

using namespace std;

#define FOR(i,N) FORR(i, 0, N)
#define FORR(i,a,b) FOTR(i, a, b, 1)
#define FOTR(i,a,b,c) for(int i=(a);i<(b);i+=(c))

#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}
#define ll long long
#define MOD 1000000007

struct running_median{

    priority_queue<ll, vector<ll>,    less<ll> > lh;  //left half of sorted values
    priority_queue<ll, vector<ll>, greater<ll> > rh;  //right half of sorted values

    void INSERT(ll val){
        if(lh.empty() || (!rh.empty() && val < rh.top())) lh.push(val);
        else rh.push(val);

        //maintain size(lh) == size(rh) OR size(lh)+1 == size(rh)
        if(lh.size()    < rh.size())lh.push(rh.top()), rh.pop();
        if(lh.size() -1 > rh.size())rh.push(lh.top()), lh.pop();
    }
    ll GET(){
        return lh.empty()?-1:lh.top();
    }
    void INIT(){
        lh = priority_queue<ll, vector<ll>,    less<ll> >();
        rh = priority_queue<ll, vector<ll>, greater<ll> >();
    }
}RM;

//SPOJ WEIRDFN
int main(){
    cpp_io();

    int T;
    cin>> T;
    FOR(cs, T){
        ll a, b, c, n, ans=1, num=1, mid;
        cin>>a>>b>>c>>n;
        RM.INIT();
        RM.INSERT(1);
        FORR(i, 2, n+1){
            mid = RM.GET();
            num = ((a*mid) + (b*i) + c)%MOD;
            ans += num;
            RM.INSERT(num);
        }
        cout<<ans<<"\n";
    }
}

