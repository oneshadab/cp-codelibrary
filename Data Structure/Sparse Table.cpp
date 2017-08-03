#include <bits/stdc++.h>

using namespace std;

//Sparse Table
struct Sparse{
    static const int NMAX = 200000;
    static const int WIDTH = 20;
    int A[NMAX+10], idx[NMAX+10][WIDTH+2];

    void build(int tmp[]){
        for(int i=0; i<NMAX; i++) A[i]=tmp[i], idx[i][0]=i;
        for(int h=0; h<bitWidth(NMAX); h++)
            for(int i=0; i+(1<<h)<NMAX; i++)
                idx[i][h+1]=argmin(idx[i][h], idx[i+(1<<h)][h]);
    }
    /*Index of Minimum Element*/
    int getIdx(int x, int y){
        if(x == y) return x;
        if(x >  y) swap(x, y);
        int h = bitWidth(y - x);
        return argmin(idx[x][h], idx[y - (1<<h)][h]);
    }
    int get(int x, int y){return A[getIdx(x, y)];}
    int bitWidth(int x){return 31-__builtin_clz(x);}
    int argmin(int x, int y){return A[x]<A[y]?x:y;}
};

int main(){
    return 0;
}
