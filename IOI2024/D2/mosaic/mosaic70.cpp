// CASE T = B

#include "mosaic.h"
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int D = 200002;
bool row[5][200005];
bool col[200005][5];
int rows[5][200005];
int cols[200005][5];

int diff[400010];
int su[400010];

vector<long long> mosaic(vector<int> X, vector<int> Y,
    vector<int> T, vector<int> B,
    vector<int> L, vector<int> R) {
    int Q = (int)T.size();
    int N = (int)X.size();

    for (int i = 1; i <= N; i++){
        row[1][i] = X[i-1];
        col[i][1] = Y[i-1];
        rows[1][i] = rows[1][i-1]+row[1][i];
        cols[i][1] = col[i][1];
    }
    row[2][1] = rows[2][1] = Y[1];
    row[3][1] = rows[3][1] = Y[2];
    row[4][1] = rows[4][1] = Y[3];
    col[1][2] = X[1]; cols[1][2] = cols[1][1] + col[1][2];
    col[1][3] = X[2]; cols[1][3] = cols[1][2] + col[1][3];
    col[1][4] = X[3]; cols[1][4] = cols[1][3] + col[1][4];

    for (int i = 2; i <= 4; i++){
        for (int j = 2; j <= N; j++){
            row[i][j] = (!row[i-1][j] && !row[i][j-1]);
            rows[i][j] = rows[i][j-1] + row[i][j];
        }
    }

    // for (int i = 1; i <= 3; i++){
    //     for (int j = 1; j <= N; j++){
    //         cout << rows[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    for (int i = 2; i <= 4; i++){
        for (int j = 2; j <= N; j++){
            col[j][i] = (!col[j][i-1] && !col[j-1][i]);
            cols[j][i] = cols[j][i-1] + col[j][i];
        }
    }

    // for (int j = 1; j <= N; j++){
    //     for (int i = 1; i <= 3; i++){
    //         cout << cols[j][i] << ' ';
    //     }
    //     cout << '\n';
    // }

    for (int i = N; i >= 4; i--){
        diff[4-i+D] = row[4][i];
    }
    for (int i = 5; i <= N; i++){
        diff[i-4+D] = col[i][4];
    }
    for (int i = 1; i <= 400009; i++){
        su[i] = su[i-1] + diff[i];
    }

    vector<ll> ans;
    for (int i = 0; i < Q; i++){
        int t = T[i]+1, l = L[i]+1, r = R[i]+1;
        if (t <= 4){
            ans.push_back(rows[t][r]-rows[t][l-1]);
            continue;
        } else {
            ll tmp = 0;
            if (r <= 4){
                ans.push_back(cols[t][r]-cols[t][l-1]);
                continue;
            } else if (l <= 4){
                tmp += (cols[t][4]-cols[t][l-1]);
                l = 5;
            }
            int ldiff = t-l;
            int rdiff = t-r;
            tmp += (su[ldiff+D]-su[rdiff+D-1]);
            ans.push_back(tmp);
        }
    }

    return ans;
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


