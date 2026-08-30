#include <bits/stdc++.h>
using namespace std;

int n;
int sta[1000006], tp;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T;
	while (T--){
		string s; cin >> s;
		n = s.length();
		tp = 0;
		for (int i = n-1; i >= 0; i--){
			int cur = s[i]-'A'+1;
			sta[++tp] = cur;
			if (sta[tp] == 1){
				if (tp > 1 && sta[tp-1] == 2){
					if (tp > 2 && sta[tp-2] == 3){
						tp -= 3;
					} else {
						tp -= 2;
					}
				} else {
					tp -= 1;
				}
			}
		}
		cout << tp << '\n';
	}

	return 0;
}