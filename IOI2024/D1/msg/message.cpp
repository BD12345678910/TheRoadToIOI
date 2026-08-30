#include <bits/stdc++.h>
#include "message.h"
using namespace std;

bool scheme[100][16];
bool final[100][31];
bool vis[100][16];

int c[18] = {1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 12, 6};
// vector<vector<bool>> VV;

// void send_packet(vector<bool> V){
//     VV.push_back(V);
// }

void send_message(vector<bool> M, vector<bool> C) { 
    int n = M.size();
    vector<int> pos;
    bool flag = 1; int first = 0;
    for (int i = 0; i < 31; i++){
        if (!C[i] && flag){
            // cout << i << endl;
            for (int j = 0; j <= 4; j++){
                bool bit = (i>>j)&1;
                for (int k = 0; k < 16; k++){
                    scheme[j][k] = bit;
                    vis[j][k] = 1;
                }
            }
            flag = 0;
            first = i;
            pos.push_back(i);
        } else if (!C[i]) pos.push_back(i);
    }
    int x = 0, y = 0;
    for (int p : pos){
        if (p == first) continue;
        // cout << p << endl;
        for (int i = 4; i >= 0; i--){
            // cout << x << ' ' << y << '\n';
            bool bit = (p >> i) & 1;
            scheme[x+5][y] = bit;
            vis[x+5][y] = 1;
            if (y == c[x]-1) y = 0, x++;
            else y++;
        }
    }
    int curr = 0;
    for (int i = 5; i < 74; i++){
        int lo = 0, hi = 15;
        if (i < 23) lo = c[i-5];
        for (int j = lo; j <= hi; j++){
            scheme[i][j] = M[curr++];
            vis[i][j] = 1;
            if (curr >= n) break;
        }
        if (curr >= n) break;
    }
    // for (int j = 0; j <= i; j++){
    //     for (int k = 0; k < 16; k++){
    //         cout << vis[j][k] << ' ';
    //     }
    //     cout << '\n';
    // }

    for (int i = 0; i < 11; i++){
        scheme[74][i] = (n>>i)&1;
    }

    // for (int i = 0; i <= 74; i++){
    //     for (int j = 0; j < 16; j++){
    //         cout << scheme[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    for (int i = 0; i <= 74; i++){
        for (int j = 0; j < 16; j++){
            final[i][pos[j]] = scheme[i][j];
        }
    }

    // for (int i = 0; i <= 74; i++){
    //     for (int j = 0; j < 31; j++){
    //         cout << final[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    for (int i = 0; i <= 74; i++){
        vector<bool> V;
        for (int j = 0; j < 31; j++){
            V.push_back(final[i][j]);
        }
        send_packet(V);
    }
}

vector<bool> receive_message(vector<vector<bool>> R) {
    // cout << "RECEIVE\n";
    vector<bool> RET;
    vector<int> pos;
    int first = 0;
    for (int i = 0; i < 5; i++){
        int one = 0, zero = 0;
        for (int j = 0; j < 31; j++){
            if (R[i][j]) one++;
            else zero++;
        }
        if (one > zero) first |= (1<<i);
    }
    pos.push_back(first);
    // cout << first << endl;

    int po = 4, s = 0;
    for (int i = 0; i < 18; i++){
        int row = i+5;
        vector<int> neu;
        for (int j : pos){
            if (R[row][j]) s += (1<<po);
            po--;
            if (po == -1){
                po = 4;
                neu.push_back(s);
                s = 0;
            }
        }
        for (int j : neu){
            if (pos.size()<16) pos.push_back(j);
        }
    }

    // for (int p : pos) cout << p << ' ';
    // cout << '\n';

    // recover the scheme
    for (int i = 0; i <= 74; i++){
        for (int j = 0; j < 16; j++){
            scheme[i][j] = R[i][pos[j]]; // FATAL BUG!!!!!!!! 
        }
    }

    // for (int i = 0; i <= 74; i++){
    //     for (int j = 0; j < 16; j++){
    //         cout << scheme[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    int n = 0;
    for (int i = 0; i < 11; i++){
        if (scheme[74][i]) n |= (1<<i);
    }

    int curr = 0;
    for (int i = 5; i < 74; i++){
        int lo = 0, hi = 15;
        if (i < 23) lo = c[i-5];
        for (int j = lo; j <= hi; j++){
            RET.push_back(scheme[i][j]);
            curr++;
            if (curr >= n) break;
        }
        if (curr >= n) break;
    }
    return RET;
}

// int main(){
//     freopen("01.in", "r", stdin);
//     freopen("01.out", "w", stdout);
//     int n; cin >> n;
//     vector<bool> V1, V2;
//     for (int i = 1; i <= n; i++) {
//         bool b; cin >> b; V1.push_back(b);
//     }
//     for (int i = 0; i < 31; i++){
//         bool b; cin >> b; V2.push_back(b);
//     }
//     send_message(V1, V2);

//     vector<bool> result = receive_message(VV);
//     for (bool b: result){
//         cout << b << ' ';
//     }
//     cout << endl;

//     return 0;
// }
