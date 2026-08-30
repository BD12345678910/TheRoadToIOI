#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;

int n, m;
ll bin[22];

void mul(vector<ll> &A, vector<ll> B){
	vector<ll> AA(m, 0);
	for (int i = 0; i < m; i++){
		for (int j = 0; j < m; j++){
			(AA[(i+j)%m]+=A[i]*B[j]%MOD)%=MOD;
		}
	}
	A = AA;
}

vector<ll> power(vector<ll> B, ll nn){
	vector<ll> res(m); res[0] = 1;
	while (nn){
		if (nn & 1) mul(res, B);
		mul(B, B);
		nn >>= 1;
	}
	return res;
}

int main(){
	freopen("team.in", "r", stdin);
	freopen("team.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1; i <= n; i++){
		int a, b; cin >> a >> b;
		bin[b%m] += a;
	}
	vector<ll> P(m, 0);
	P[0] = 1;
	for (int i = 0; i < m; i++){
		if (!bin[i]) continue;
		vector<ll> T(m, 0);
		T[i] += 1; T[0] += 1;
		mul(P, power(T, bin[i]));
	}
	cout << (P[0]-1+MOD)%MOD << endl;

	return 0;
}



