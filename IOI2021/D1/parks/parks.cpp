#include "parks.h"
#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int dx[4] = {2, 0, -2, 0};
const int dy[4] = {0, 2, 0, -2};
map<pair<int,int>,int> pointInd;
map<pair<int,int>,vector<int>> M;
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
    if (n == 1) {
        build(U, V, A, B);
        return 1;
    }
    A.resize(n-1); B.resize(n-1);
    for (int i = 0; i < n; i++){
        pointInd[{X[i], Y[i]}] = i;
        fa[i] = i;
    }
    vector<int> shuf;
    for (int i = 0; i < n; i++) shuf.push_back(i);
    shuffle(shuf.begin(), shuf.end(), rng);
    for (int i : shuf){
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

    for (int i = 0; i < n-1; i++){
        int u = U[i], v = V[i];
        if (X[u] == X[v]){
            M[{X[u]+1, (Y[u]+Y[v])>>1}].push_back(i);
            M[{X[u]-1, (Y[u]+Y[v])>>1}].push_back(i);
        } else {
            M[{(X[u]+X[v])>>1, Y[u]+1}].push_back(i);
            M[{(X[u]+X[v])>>1, Y[u]-1}].push_back(i);
        }
    }
    queue<pair<int,int>> Q;
    queue<pair<int,int>> Q2;
    for (auto [p, f]: M){
        if ((int)f.size() == 1){
            Q.push(p);
        } else if ((int)f.size()==2){
            Q2.push(p);
        }
    }
    int tcnt = 0;
    while (tcnt < n-1){
        while (!Q.empty()){
            pair<int,int> P = Q.front(); Q.pop();
            // it has already been taken!
            if (M[P].size()==0) continue;
            int of = M[P][0];
            M.erase(P); 
            // the same of got counted twice...
            A[of] = P.first;
            B[of] = P.second;
            tcnt++;
            int u = U[of], v = V[of];
            pair<int,int> targ;
            if (X[u]==X[v]){
                if (P.first == X[u]+1){
                    targ = {X[u]-1, P.second};
                } else {
                    targ = {X[u]+1, P.second};
                }
            } else {
                if (P.second == Y[u]+1){
                    targ = {P.first, Y[u]-1};
                } else {
                    targ = {P.first, Y[u]+1};
                }
            }
            vector<int> tmp;
            auto &mt = M[targ];
            int s = 0;
            for (int i : mt){
                if (i != of) {
                    tmp.push_back(i);
                    s++;
                }
            }
            M[targ] = tmp;
            if (s==1) Q.push(targ);
            if (s==2) Q2.push(targ);
            if (tcnt >= n-1) {
                build(U, V, A, B);
                return 1;
            }
        }
        bool ndone = 1;
        while (!Q2.empty()){
            pair<int,int> p = Q2.front(); Q2.pop();
            if ((int)M[p].size() != 2) continue;
            M[p].pop_back(); Q.push(p);
            ndone = 0; break;
        }
        if (ndone) break;
    }
    
    return 0;
}





