#include "embattle.h"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

gp_hash_table<int,int> rowmax;
gp_hash_table<int,int> colmax;
// x : <y, val>, classify at time of processing
gp_hash_table<int,gp_hash_table<int,int>> row;
gp_hash_table<int,gp_hash_table<int,int>> col;
// only for heavy
gp_hash_table<int,int> rowlz;
gp_hash_table<int,int> collz;
vector<int> heavyrows;
vector<int> heavycols;

void mx(int &x, int y){
    if (x < y) x = y;
}

vector<int> embattle(
    int N, vector<int> X, vector<int> Y,
    vector<int> E, vector<string> OP,
    vector<int> arg1, vector<int> arg2){
    vector<int> ans;

    int B = sqrt(N);
    for (int i = 0; i < N; i++){
        int x = X[i], y = Y[i], e = E[i];
        mx(row[x][y], e);
        mx(col[y][x], e);
        mx(rowmax[x], row[x][y]);
        mx(colmax[y], col[y][x]);
        rowlz[x] = 0;
        collz[y] = 0;
    }

    for (const auto &[x, _]: row){
        if ((int)_.size() > B){
            heavyrows.push_back(x);
        }
    }
    for (const auto &[x, _]: col){
        if ((int)_.size() > B){
            heavycols.push_back(x);
        }
    }

    int q = (int) OP.size();
    for (int i = 0; i < q; i++){
        string op = OP[i];
        if (op == "XADD"){
            int x = arg1[i], d = arg2[i];
            // brute force update:
            if ((int)row[x].size() <= B){
                auto &rx = row[x];
                rowmax[x] += d;
                for (const auto &[y, _]: rx){
                    auto &cy = col[y];
                    cy[x] += d;
                    int u = cy[x];
                    rx[y] += d;
                    mx(colmax[y], u+collz[y]);
                }
            } else {
                rowmax[x] += d;
                rowlz[x] += d;
                for (int y : heavycols){
                    auto &cy = col[y];
                    if (cy.find(x)==cy.end()) continue;
                    cy[x] += d;
                    int u = cy[x];
                    mx(colmax[y], u+collz[y]);
                }
            }
        } else if (op == "YADD"){
            int y = arg1[i], d = arg2[i];
            // brute force update:
            if ((int)col[y].size() <= B){
                auto &cy = col[y];
                colmax[y] += d;
                for (const auto &[x, _]: cy){
                    auto &rx = row[x];
                    rx[y] += d;
                    int u = rx[y];
                    cy[x] += d;
                    mx(rowmax[x], u+rowlz[x]);
                }
            } else {
                colmax[y] += d;
                collz[y] += d;
                for (int x : heavyrows){
                    auto &rx = row[x];
                    if (rx.find(y)==rx.end()) continue;
                    rx[y] += d;
                    int u = rx[y];
                    mx(rowmax[x], u+rowlz[x]);
                }
            }
        } else if (op == "XQUERY"){
            int x = arg1[i];
            // heavy columns have lazy that need to be pulled
            if ((int)row[x].size() <= B){
                int tans = 0;
                auto &rx = row[x];
                for (auto [y, v]: rx){
                    mx(tans, v+collz[y]);
                }
                ans.push_back(tans);
            } else {
                ans.push_back(rowmax[x]);
            }
        } else if (op == "YQUERY"){
            int y = arg1[i];
            // heavy columns have lazy that need to be pulled
            if ((int)col[y].size() <= B){
                int tans = 0;
                auto cy = col[y];
                for (auto [x, v]: cy){
                    mx(tans, v+rowlz[x]);
                }
                ans.push_back(tans);
            } else {
                ans.push_back(colmax[y]);
            }
        } else if (op == "XMOVE"){
            int x = arg1[i], d = arg2[i];
            if ((int)row[x].size() <= B){
                auto &rx = row[x];
                if (row.find(x+d)){
                    // small to large:
                } else {
                    row[x+d] = *rx;
                    row.erase(x);
                }
            }
        }
    }
    return ans;
}
