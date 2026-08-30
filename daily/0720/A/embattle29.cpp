// no XADD, YADD

#include "embattle.h"
#include <bits/stdc++.h>
using namespace std;

map<int,int> xmax;
map<int,int> ymax;

void mx(int &x, int y){
    if (x < y) x = y;
}

vector<int> embattle(
    int N, vector<int> X, vector<int> Y,
    vector<int> E, vector<string> OP,
    vector<int> arg1, vector<int> arg2){
    vector<int> ans;
    for (int i = 0; i < N; i++){
        if (xmax.count(X[i])) mx(xmax[X[i]], E[i]);
        else xmax[X[i]] = E[i];
        if (ymax.count(Y[i])) mx(ymax[Y[i]], E[i]);
        else ymax[Y[i]] = E[i];
    }
    int q = (int) OP.size();
    for (int i = 0; i < q; i++){
        string op = OP[i];
        if (op == "XMOVE"){
            int xq = arg1[i], d = arg2[i];
            if (xmax.count(xq)){
                int tmp = xmax[xq];
                xmax.erase(xq);
                if (xmax.count(xq+d)) 
                    mx(xmax[xq+d], tmp);
                else 
                    xmax[xq+d] = tmp;
            }
        // } else if (op == "XADD"){
        //     int xq = arg1[i], d = arg2[i];
        //     for (int j = 1; j <= N; j++){
        //         if (x[j]==xq){
        //             val[j] += d;
        //         }
        //     }
        } else if (op == "YMOVE"){
            int yq = arg1[i], d = arg2[i];
            if (ymax.count(yq)){
                int tmp = ymax[yq];
                ymax.erase(yq);
                if (ymax.count(yq+d)) 
                    mx(ymax[yq+d], tmp);
                else 
                    ymax[yq+d] = tmp;
            }
        // } else if (op == "YADD"){
        //     int yq = arg1[i], d = arg2[i];
        //     for (int j = 1; j <= N; j++){
        //         if (y[j]==yq){
        //             val[j] += d;
        //         }
        //     }
        } else if (op == "XQUERY"){
            int xq = arg1[i];
            if (xmax.count(xq)) ans.push_back(xmax[xq]);
            else ans.push_back(0);
        } else if (op == "YQUERY"){
            int yq = arg1[i];
            if (ymax.count(yq)) ans.push_back(ymax[yq]);
            else ans.push_back(0);
        } 
    }
    return ans;
}
