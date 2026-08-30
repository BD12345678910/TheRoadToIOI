#include "hieroglyphs.h"
#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<int> ucs(vector<int> A, vector<int> B) {
    n = A.size(); m = B.size();
    for (int i = 0; i < n; i++){
        if (A[i] != B[i]){
            vector<int> voi; voi.push_back(-1);
            return voi;
        }
    }
    return A;
}
