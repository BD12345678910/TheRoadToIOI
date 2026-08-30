// brute force solution

#include "embattle.h"
#include <bits/stdc++.h>
using namespace std;

static int x[5002], y[5002], val[5002];

vector<int> embattle(
    int N, vector<int> X, vector<int> Y,
    vector<int> E, vector<string> OP,
    vector<int> arg1, vector<int> arg2){
    vector<int> ans;
    for (int i = 0; i < N; i++){
        x[i+1] = X[i];
        y[i+1] = Y[i];
        val[i+1] = E[i];
    }
    int q = (int) OP.size();
    for (int i = 0; i < q; i++){
        string op = OP[i];
        if (op == "XMOVE"){
            int xq = arg1[i], d = arg2[i];
            for (int j = 1; j <= N; j++){
                if (x[j]==xq){
                    x[j] += d;
                }
            }
        } else if (op == "XADD"){
            int xq = arg1[i], d = arg2[i];
            for (int j = 1; j <= N; j++){
                if (x[j]==xq){
                    val[j] += d;
                }
            }
        } else if (op == "YMOVE"){
            int yq = arg1[i], d = arg2[i];
            for (int j = 1; j <= N; j++){
                if (y[j]==yq){
                    y[j] += d;
                }
            }
        } else if (op == "YADD"){
            int yq = arg1[i], d = arg2[i];
            for (int j = 1; j <= N; j++){
                if (y[j]==yq){
                    val[j] += d;
                }
            }
        } else if (op == "XQUERY"){
            int xq = arg1[i];
            int tans = 0;
            for (int j = 1; j <= N; j++){
                if (x[j]==xq){
                    tans = max(val[j], tans);
                }
            }
            ans.push_back(tans);
        } else if (op == "YQUERY"){
            int yq = arg1[i];
            int tans = 0;
            for (int j = 1; j <= N; j++){
                if (y[j]==yq){
                    tans = max(val[j], tans);
                }
            }
            ans.push_back(tans);
        } 
    }
    return ans;
}
