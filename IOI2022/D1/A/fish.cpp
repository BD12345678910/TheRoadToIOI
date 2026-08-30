#include "fish.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NINF = -4e18;
ll up[3003], down[3003], zero[3003];
// up[x] means last two columns were y x for y < x
// down[x] means last two columns were y x for y >= x
// zero[x] means last two columns were x 0!!
// for up, down, both x, y >= 1
ll nup[3003], ndown[3003], nzero[3003];
int grid[3003][3003];
ll a[3003][3003];

void mx(ll &x, ll y){
    if (y > x) x = y;
}

ll max_weights(int N,int M,vector<int>X,vector<int>Y,vector<int>W){
    for (int i = 0; i < M; i++){
        grid[X[i]+1][Y[i]+1] = W[i];
    }
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            a[i][j] = a[i][j-1]+grid[i][j];
        }
    }

    // -1 th column 0, 0 th column 0
    memset(up, 0xc0, sizeof(up)); 
    memset(down, 0xc0, sizeof(down));
    memset(zero, 0xc0, sizeof(zero));
    zero[0] = 0;
    for (int i = 1; i <= N; i++){
        memset(nup, 0xc0, sizeof(nup));
        memset(ndown, 0xc0, sizeof(ndown));
        memset(nzero, 0xc0, sizeof(nzero));
        // consider i-1, i-2, i
        //                j < x
        // j >= 1
        
        ll curr = NINF;
        for (int j = 1; j <= N-1; j++){
            mx(curr, up[j]-a[i-1][j]);
            mx(nup[j+1], curr+a[i-1][j+1]);
        }

        // what if j = 0? and we have j < x?
        // strip the contribution from x (x 0 y)
        
        curr = NINF;
        for (int x = 0; x <= N; x++){
            mx(curr, zero[x]-a[i-1][x]);
        }
        for (int y = 0; y <= N; y++){
            mx(nup[y], curr+a[i-1][y]);
        }

        // j >= x but x != 0
        curr = NINF;
        for (int j = N; j >= 1; j--){
            mx(curr, up[j]+a[i][j]);
            mx(ndown[j], curr-a[i][j]);
        }
        curr = NINF;
        for (int j = N; j >= 1; j--){
            mx(curr, down[j]+a[i][j]);
            mx(ndown[j], curr-a[i][j]);
        }

        // final special case: x = 0
        // part 1, previous >= 1
        for (int j = 1; j <= N; j++){
            mx(nzero[j], up[j]+a[i][j]);
            mx(nzero[j], down[j]+a[i][j]);
        }
        // part 2, previous == 0, as previously calculated
        for (int j = 0; j <= N; j++) mx(nzero[0], zero[j]);

        memcpy(up, nup, sizeof(nup));
        memcpy(down, ndown, sizeof(ndown));
        memcpy(zero, nzero, sizeof(nzero));
    }

    ll ans = NINF;
    for (int i = 0; i <= N; i++){
        mx(ans, up[i]);
        mx(ans, down[i]);
        mx(ans, zero[i]);
    }

    return ans;
}


