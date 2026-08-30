// CASE T = B

#include "mosaic.h"
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int D = 200002;
vector<long long> mosaic(vector<int> X, vector<int> Y,
    vector<int> T, vector<int> B,
    vector<int> L, vector<int> R) {
    int Q = (int)T.size();
    int N = (int)X.size();

    vector<ll> V;
    for (int i = 0; i < Q; i++){
        int t = T[i], b = B[i], l = L[i], r = R[i];
        if (l == 0) l = 1;
        if (t == 0) t = 1;
        if (l > r) {V.push_back(0); continue;}
        if (t > b) {V.push_back(0); continue;}
        ll area = 1LL* (b-t+1) * (r-l+1);
        if (area % 2) {
            if (t % 2 == l % 2) area = area / 2 + 1;
            else area = area / 2;
        }
        else area = area / 2;
        V.push_back(area);
    }
    return V;
}



/*

1 0 0 0 1 1 1 1 0 1 
0 1 0 1 0 0 0 0 1 0 
1 0 1 0 1 0 1 0 0 1 
0 1 0 1 0 1 0 1 0 0 
1 0 1 0 1 0 1 0 1 0 
0 1 0 1 0 1 0 1 0 1 
1 0 1 0 1 0 1 0 1 0 
0 1 0 1 0 1 0 1 0 1 
0 0 1 0 1 0 1 0 1 0 
1 0 0 1 0 1 0 1 0 1 

*/


