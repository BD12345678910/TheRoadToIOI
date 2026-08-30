// ENBATTLE = backup, 
// what i wrote final
// in contest

// no MOVE

#include "embattle.h"
#include <bits/stdc++.h>
using namespace std;

unordered_map<int,int> rowmax;
unordered_map<int,int> colmax;
// x : <y, val>, classify at time of processing
unordered_map<int,unordered_map<int,int>> row;
unordered_map<int,unordered_map<int,int>> col;
// only for heavy
unordered_map<int,int> rowlz;
unordered_map<int,int> collz;
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
                rowmax[x] += d;
                for (const auto &[y, _]: row[x]){
                    col[y][x] += d;
                    int u = col[y][x];
                    row[x][y] += d;
                    mx(colmax[y], u+collz[y]);
                }
            } else {
                rowmax[x] += d;
                rowlz[x] += d;
                for (int y : heavycols){
                    if (!col[y].count(x)) continue;
                    col[y][x] += d;
                    int u = col[y][x];
                    mx(colmax[y], u+collz[y]);
                }
            }
        } else if (op == "YADD"){
            int y = arg1[i], d = arg2[i];
            // brute force update:
            if ((int)col[y].size() <= B){
                colmax[y] += d;
                for (const auto &[x, _]: col[y]){
                    row[x][y] += d;
                    int u = row[x][y];
                    col[y][x] += d;
                    mx(rowmax[x], u+rowlz[x]);
                }
            } else {
                colmax[y] += d;
                collz[y] += d;
                for (int x : heavyrows){
                    if (!row[x].count(y)) continue;
                    row[x][y] += d;
                    int u = row[x][y];
                    mx(rowmax[x], u+rowlz[x]);
                }
            }
        } else if (op == "XQUERY"){
            int x = arg1[i];
            // heavy columns have lazy that need to be pulled
            if ((int)row[x].size() <= B){
                int tans = 0;
                for (auto [y, v]: row[x]){
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
                for (auto [x, v]: col[y]){
                    mx(tans, v+rowlz[x]);
                }
                ans.push_back(tans);
            } else {
                ans.push_back(colmax[y]);
            }
        }
    }
    return ans;
}
