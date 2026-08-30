#include "parks.h"
#include <bits/stdc++.h>
using namespace std;
const int dx[4] = {2,0,-2,0};
const int dy[4] = {0,2,0,-2};
map<pair<int,int>, int> M;
vector<int> U, V, A, B;
set<pair<int,int>> S;
int cnt;
bool vis[200005];

int construct_roads(vector<int> X, vector<int> Y){
    int n = X.size(); 
    if (n == 1) { build({}, {}, {}, {}); return 1; }
    for (int i = 0; i < n; i++) M[{X[i],Y[i]}] = i;
    queue<pair<int,int>> Q; Q.push({0,0});
    int w = 0;
    while (!Q.empty()){
        auto [node, dirfrom] = Q.front(); Q.pop();
        if (vis[node]) continue;
        vis[node] = 1;
        int x = X[node], y = Y[node];
        cout << node << ' ' << x << ' ' << y << ":" << endl;
        int stdir = (dirfrom+1)%4;
        if (node == 0) {
            for (int i = 0; i <= 3; i++){
                int xv = x+dx[i], yv = y+dy[i];
                cout << xv << ' ' << yv << endl;
                if (!M.count({xv,yv})) continue;
                int v = M[{xv,yv}];
                if (vis[v]) continue;
                cout << v << ' ' << xv << ' ' << yv << endl;
                U.push_back(node);
                V.push_back(v);
                if (xv==x){
                    if (!S.count({x+1,(yv+y)>>1})){
                        A.push_back(x+1);
                        B.push_back((yv+y)>>1);
                        Q.push({v, 3-i});
                        S.insert({x+1,(yv+y)>>1});
                    } else if (!S.count({x-1, (yv+y)>>1})){
                        A.push_back(x-1);
                        B.push_back((yv+y)>>1);
                        Q.push({v, 3-i});
                        S.insert({x-1,(yv+y)>>1});
                    } else {
                        return 0;
                    }
                } else {
                    if (!S.count({(xv+x)>>1,y+1})){
                        A.push_back((xv+x)>>1);
                        B.push_back(y+1);
                        Q.push({v, 3-i});
                        S.insert({(xv+x)>>1,y+1});
                    } else if (!S.count({(xv+x)>>1,y-1})){
                        A.push_back((xv+x)>>1);
                        B.push_back(y-1);
                        Q.push({v, 3-i});
                        S.insert({{(xv+x)>>1,y-1}});
                    } else {
                        return 0;
                    }
                }
                w++;
            }
        } else 
        for (int i = stdir; i != dirfrom; i = (i+1)%4){
            int xv = x+dx[i], yv = y+dy[i];
            cout << xv << ' ' << yv << endl;
            if (!M.count({xv,yv})) continue;
            int v = M[{xv,yv}];
            if (vis[v]) continue;
            cout << v << ' ' << xv << ' ' << yv << endl;
            U.push_back(node);
            V.push_back(v);
            if (xv==x){
                if (!S.count({x+1,(yv+y)>>1})){
                    A.push_back(x+1);
                    B.push_back((yv+y)>>1);
                    Q.push({v, 3-i});
                    S.insert({x+1,(yv+y)>>1});
                } else if (!S.count({x-1, (yv+y)>>1})){
                    A.push_back(x-1);
                    B.push_back((yv+y)>>1);
                    Q.push({v, 3-i});
                    S.insert({x-1,(yv+y)>>1});
                } else {
                    return 0;
                }
            } else {
                if (!S.count({(xv+x)>>1,y+1})){
                    A.push_back((xv+x)>>1);
                    B.push_back(y+1);
                    Q.push({v, 3-i});
                    S.insert({(xv+x)>>1,y+1});
                } else if (!S.count({(xv+x)>>1,y-1})){
                    A.push_back((xv+x)>>1);
                    B.push_back(y-1);
                    Q.push({v, 3-i});
                    S.insert({{(xv+x)>>1,y-1}});
                } else {
                    return 0;
                }
            }
            w++;
        }
    }

    if (w < n-1) return 0;
    build(U, V, A, B);
    return 1;
}





