#include <bits/stdc++.h>
using namespace std;

void answer(vector<int> C, vector<int> X, vector<int> Y);

int leaf[400005];
int dfn[400005], cnt = 0;
int X[400005], Y[400005];

int build(int x, int l, int r, int b){
    if (r < b) return 1;
    if (l == r) return -leaf[l];
    dfn[x] = ++cnt;
    int mid = (l+r)>>1;
    X[dfn[x]] = -build(x<<1, l, mid, b);
    Y[dfn[x]] = -build(x<<1|1, mid+1, r, b);
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
        answer(C, vector<int>(), vector<int>());
        return;
    }
    A.push_back(0);
    int B = 1, bb = 0; while (B < N) {B <<= 1; bb++;}
    int K = B - N;
    int ptr = 0;
    for (int t = 0; t < B; t++){
        int p = rev(t, bb); // physical leaf visited at time t
        if (p >= K) leaf[p] = A[++ptr];
    }

    build(1, 0, B-1, K);
    vector<int> C(M+1, -1); C[0] = A[0];
    answer(C, vector<int>(X+1, X+cnt+1), vector<int>(Y+1, Y+cnt+1));
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
