#include <bits/stdc++.h>
using namespace std;

void answer(vector<int> C, vector<int> X, vector<int> Y);

int a[200005];

void create_circuit(int M, vector<int> A) {
    int N = A.size();
    for (int i = 1; i <= N; i++){
        a[i] = A[i-1];
    }

    
    
    vector<int> C, X, Y;
    answer(C, X, Y);
}
