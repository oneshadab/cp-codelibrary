#include <bits/stdc++.h>

using namespace std;

int N, M;
int GS[110][110];
bool gauss(int GS[110][110], int N, int M){
    for(int k = 1; k <= N; k++){
        int mx = k;
        for(int i = k + 1; i <= N; i++){
            if(GS[i][k] > GS[mx][k]) mx = i;
        }
        swap(GS[k], GS[mx]);
        double x = GS[k][k];
        if(x == 0) return false;
        for(int i = k + 1; i <= N; i++){
            double y = (GS[i][k]);
            for(int j = 1; j <= N + 1; j++){
                GS[i][j] -= (y / x) *  GS[k][j];
            }
        }
    }
    for(int k = N; k >= 1; k--){
        double x = GS[k][k];
        if(x == 0) return false;
        for(int i = k - 1; i >= 1; i--){
            double y = (GS[i][k]);
            for(int j = 1; j <= N + 1; j++){
                GS[i][j] -= (y / x) * GS[k][j];
            }
        }
    }
    for(int k = 1; k <= N; k++){
        double x = GS[k][k];
        GS[k][k] = 1;
        GS[k][N + 1] /= x;
    }
}

int main()
{
    bool possible = gauss(GS, N, M);
}
