#include <bits/stdc++.h>
using namespace std;

void answer(vector<int> C, vector<int> X, vector<int> Y);
// {
//     cout << "C:\n";
//     for (int x : C) cout << x << ' ';
//     cout << "\nX:\n";
//     for (int x : X) cout << x << ' ';
//     cout << "\nY:\n";
//     for (int x : Y) cout << x << ' ';
//     cout << '\n';
// }

int leaf[400005];
int dfn[800005], cnt = 0;
int nxt[800005][2];

int build(int x, int l, int r, int b){
    if (r < b) return 1;
    if (l == r) return -leaf[l];
    dfn[x] = ++cnt;
    int mid = (l+r)>>1;
    nxt[dfn[x]][0] = -build(x<<1, l, mid, b);
    nxt[dfn[x]][1] = -build(x<<1|1, mid+1, r, b);
    return dfn[x];
}

int rev(int x, int B){
    int y = 0;
    for (int i = 0; i < B; i++){
        if ((x>>i)&1) y |= (1<<(B-i-1));
    }
    return y;
}

void create_circuit(int M, vector<int> A) {
    int N = A.size();
    if (N == 1){
        vector<int> C; C.push_back(A[0]); C.push_back(0);
        vector<int> X, Y; answer(C, X, Y);
        return;
    }
    vector<int> AA;
    for (int i = 1; i < N; i++) 
        AA.push_back(A[i]);
    AA.push_back(0);

    int B = 1, bb = 0; while (B < N) {B <<= 1; bb++;}
    int K = B - N;
    int ptr = 0;
    for (int t = 0; t < B; t++){
        int p = rev(t, bb); // physical leaf visited at time t
        if (p >= K){
            leaf[p] = AA[ptr++];
        }
    }

    build(1, 0, B-1, K);
    vector<int> C;
    C.push_back(A[0]);
    for (int i = 1; i <= M; i++){
        C.push_back(-1);
    }
    vector<int> X;
    for (int i = 1; i <= cnt; i++){
        X.push_back(nxt[i][0]);
    }
    vector<int> Y;
    for (int i = 1; i <= cnt; i++){
        Y.push_back(nxt[i][1]);
    }
    answer(C, X, Y);
}


// int main(){
//     int M, N; vector<int> A;
//     cin >> M >> N;
//     for (int i = 1; i <= N; i++){
//         int x; cin >> x;
//         A.push_back(x);
//     }
//     create_circuit(M, A);
//     return 0;
// }
