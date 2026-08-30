
// put a pin in this:
// we understand that it is H(y)-H(Rb)+H(Rb-1)+... alternatingly till H(2)

#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353; 

struct Mint {
	int v;
	Mint(long long _v = 0) {
		_v %= MOD;
		if (_v < 0) _v += MOD;
		v = _v;
	}
	Mint& operator += (const Mint& o) {
		v += o.v;
		if (v >= MOD) v -= MOD;
		return *this;
	}
	Mint& operator -= (const Mint& o) {
		v -= o.v;
		if (v < 0) v += MOD;
		return *this;
	}
	Mint& operator *= (const Mint& o) {
		v = 1LL * v * o.v % MOD;
		return *this;
	}
	friend Mint qpow(Mint a, long long b) {
		Mint res = 1;
		while (b) {
			if (b & 1) res *= a;
			a *= a;
			b >>= 1;
		}
		return res;
	}
	friend Mint inv(Mint a) {
		return qpow(a, MOD - 2); // MOD must be prime
	}
	Mint& operator /= (const Mint& o) {
		return *this *= inv(o);
	}
	friend Mint operator + (Mint a, const Mint& b) {
		return a += b;
	}
	friend Mint operator - (Mint a, const Mint& b) {
		return a -= b;
	}
	friend Mint operator * (Mint a, const Mint& b) {
		return a *= b;
	}
	friend Mint operator / (Mint a, const Mint& b) {
		return a /= b;
	}
	friend bool operator == (const Mint& a, const Mint& b) {
		return a.v == b.v;
	}
	friend bool operator != (const Mint& a, const Mint& b) {
		return a.v != b.v;
	}
	friend ostream& operator << (ostream& os, const Mint& x) {
		return os << x.v;
	}
	friend istream& operator >> (istream& is, Mint& x) {
		long long y;
		is >> y;
		x = Mint(y);
		return is;
	}
};

int n, a, b;

int main(){
	cin >> n >> a >> b;


	return 0;
}





