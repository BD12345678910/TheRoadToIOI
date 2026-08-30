#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P = 998244353;

ll d[100005];

int main(){
	int n; string s;
	cin >> n >> s;
	d[0] = s[0]-'0';
	ll a = d[0];
	ll b = 10*d[0]*d[0];
	ll cur = d[0];
	for (int i = 1; i < n; i++){
		cur = (cur*10+(s[i]-'0'))%P;
		d[i] = (cur*a-b+P)%P;
		a = (a+d[i])%P;
		b = (b*10+cur*d[i]%P)%P;
	}
	cout << d[n] << endl;

	return 0;
}