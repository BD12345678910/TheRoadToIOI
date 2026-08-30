#include <bits/stdc++.h>
using namespace std;

int n;

int main(){
	freopen("unequal.in", "r", stdin);
	freopen("unequal.out", "w", stdout);
	cin >> n;
	if (n == 1){
		cout << "00" << endl;
	} else if (n == 2){
		cout << "0001" << endl;
	} else if (n == 3){
		cout << "00000111" << endl;
	} else {
		for (int i = 0; i < (1<<n); i++){
			if (__builtin_popcount(i) % 2){
				cout << '1';
			} else {
				cout << '0';
			}
		}
		cout << endl;
	}
	return 0;
}