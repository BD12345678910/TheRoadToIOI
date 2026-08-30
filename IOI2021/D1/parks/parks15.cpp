#include "parks.h"
#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {2, 0, -2, 0};
const int dy[4] = {0, 2, 0, -2};
map<pair<int,int>,int> pointInd;
int fa[200005], cc;
int find(int x){
    if (fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}

vector<int> U, V, A, B;
void connect(int x, int y){
    int xx = find(x), yy = find(y);
    if (xx == yy) return;
    fa[xx] = yy;
    U.push_back(x);
    V.push_back(y);
    cc--;
}

int construct_roads(vector<int> X, vector<int> Y){
    int n = X.size(); cc = n;
    for (int i = 0; i < n; i++){
        pointInd[{X[i], Y[i]}] = i;
        fa[i] = i;
    }
    for (int i = 0; i < n; i++){
        int x = X[i], y = Y[i];
        for (int d = 0; d < 4; d++){
            int nx = x + dx[d], ny = y + dy[d];
            if (pointInd.count({nx, ny})){
                int j = pointInd[{nx,ny}];
                connect(i, j);
            }
        }
    }

    if (cc != 1) return 0;

    for (int idx = 0; idx < n-1; idx++){
        int i = U[idx], j = V[idx];
        if (X[i]==X[j] && X[i]==2){
            A.push_back(1);
            B.push_back((Y[i]+Y[j])>>1);
        } else if (X[i]==X[j] && X[i]==4){
            A.push_back(5);
            B.push_back((Y[i]+Y[j])>>1);
        } else {
            A.push_back(3);
            B.push_back(Y[i]-1);
        }
    }
    build(U, V, A, B);
    return 1;
}





