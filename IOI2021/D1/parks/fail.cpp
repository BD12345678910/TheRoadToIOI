#include "parks.h"
#include <bits/stdc++.h>
using namespace std;

map<pair<int,int>, int> M;
vector<int> U, V;
int A[200005], B[200005];
vector<pair<int,int>> G[200005];
set<pair<int,int>> S;
int deg[200005];
int cc;
int fa[200005], cnt;
bool vis[200005];
int find(int x){
    if (fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void connect(int x, int y){
    int xx = find(x), yy = find(y);
    if (xx == yy) return;
    U.push_back(x); V.push_back(y);
    G[x].push_back({y, cnt});
    deg[x]++;
    G[y].push_back({x, cnt++});
    deg[y]++;
    fa[xx] = yy;
    cc--;
}

int construct_roads(vector<int> X, vector<int> Y){
    int n = X.size(); 
    if (n == 1) {
        build({}, {}, {}, {});
        return 1;
    }
    cc = n;
    for (int i = 0; i < n; i++){
        fa[i] = i;
    }
    for (int i = 0; i < n; i++){
        M[{X[i],Y[i]}] = i;
    }
    if (cc > 1) return 0;

    int start;
    for (int i = 0; i < n; i++){
        if (deg[i]==1){
            start = i;
            break;
        }
    }
    queue<int> Q; Q.push(start);
    while (!Q.empty()){
        int node = Q.front(); Q.pop();
        if (vis[node]) continue;
        vis[node] = 1;
        int x = X[node], y = Y[node];
        cout << node << ' ' << x << ' ' << y << endl;
        for (auto [v,w] : G[node]){
            if (vis[v]) continue;
            int xv = X[v], yv = Y[v];
            cout << v << endl;
            if (xv==x){
                if (!S.count({x+1,(yv+y)>>1})){
                    A[w] = x+1;
                    B[w] = (yv+y)>>1;
                    Q.push(v);
                    S.insert({x+1,(yv+y)>>1});
                } else if (!S.count({x-1, (yv+y)>>1})){
                    A[w] = x-1;
                    B[w] = (yv+y)>>1;
                    Q.push(v);
                    S.insert({x-1,(yv+y)>>1});
                } else {
                    return 0;
                }
            } else {
                if (!S.count({(xv+x)>>1,y+1})){
                    A[w] = (xv+x)>>1;
                    B[w] = y+1;
                    Q.push(v);
                    S.insert({(xv+x)>>1,y+1});
                } else if (!S.count({(xv+x)>>1,y-1})){
                    A[w] = (xv+x)>>1;
                    B[w] = y-1;
                    Q.push(v);
                    S.insert({{(xv+x)>>1,y-1}});
                } else {
                    return 0;
                }
            }
        }
    }
    
    build(U, V, vector<int>(A,A+n-1), vector<int>(B,B+n-1));
    return 1;
}





