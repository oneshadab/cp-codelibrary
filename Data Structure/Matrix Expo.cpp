#include <bits/stdc++.h>

using namespace std;

/* Template Begins */

#define For(i,N) Forr(i, 0, N)
#define Forr(i,a,b) Fotr(i, a, b, 1)
#define Fotr(i,a,b,c) for(int i=(a);i<(b);i+=(c))
#define FOREACH(it, x) for(__typeof__((x).begin()) it=(x).begin();it!=(x).end();it++)
#define MEM(a,x) memset(a,x,sizeof(a))
#define BCHK(a,x) (((a)>>(x))&1)
#define BSET(a,x) ((a)|(1<<(x)))
#define BCLR(a,x) ((a)&(~(1<<(x))))
#define BTGL(a,x) ((a)^(1<<(x)))
#define FMT(...) (sprintf(CRTBUFF, __VA_ARGS__)?CRTBUFF:0)
#define read() freopen("input.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
#define cpp_io() {ios_base::sync_with_stdio(false);cin.tie(NULL);}
#define BUFFSIZE 30000
#define INF 1000000000
#define MOD 1000000007
#define MAX 200000
#define pb push_back
#define mkpr make_pair
#define pii pair<int, int>
#define fi first
#define si second
typedef long long ll;

char CRTBUFF[BUFFSIZE];

#define dbg(args...) {cout<<"-->";debugger::call(#args,args);cout<<"\n";}
struct debugger{
    static void call(const char* it){}
    template<typename T, typename ... aT>
    static void call(const char* it, T a, aT... rest){
        string b;
        for(;*it&&*it!=',';++it) if(*it!=' ')b+=*it;
        cout<<b<<"="<<a<<" ";
        call(++it, rest...);
    }
};

/* Template Ends */

struct Matrix{
    vector<ll> vec;
    int R, C;

    inline Matrix(){}
    inline Matrix(int RR, int CC){
        R = RR, C = CC;
        vec.resize(R * C + 1);
        fill(vec.begin(), vec.end(), 0);
    }

    inline ll* operator[](int x){
        return &vec[x * C];
    }

    inline Matrix operator*(Matrix &B){
        Matrix &A = *this;
        Matrix C(A.R, B.C);
        for(int i = 0; i < C.R; i++){
            for(int k = 0; k < A.C; k++){
                for(int j = 0; j < C.C; j++){
                    C[i][j] += (MOD + A[i][k] * B[k][j]) % MOD;
                    C[i][j] %= MOD;
                }
            }
        }
        return C;
    }

};

Matrix expo(Matrix M, ll e)
{
    Matrix ret = M;
    while(e){
        if(e&1) ret = ret * M;
        M = M * M, e>>=1;
    }
    return ret;
}

int main()
{
    return 0;
}


