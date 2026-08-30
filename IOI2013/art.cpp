#include <bits/stdc++.h>
using namespace std;

// challenge: open 3/sample3-[01-10]

const string prefix = "3/sample3-";
int n, m;
int main(){
	for (int T = 1; T <= 10; T++){
		cerr << T << '\n';
		string num;
		num.push_back('0'+T/10);
		num.push_back('0'+T%10);
		num = prefix + num;
		string o = num + ".out";
		ifstream fin(num);
		ofstream fout(o);

		fin >> n >> m;
		for (int i = 1; i <= n*m; i++){
			int r, g, b; fin >> r >> g >> b;
		}
		fout << n << ' ' << m << endl;
	}

	return 0;
}