#include <bits/stdc++.h>
using namespace std;

int n;
bool a[100005];
bool s[100005], tp;

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++){
		if (tp == 0) s[++tp] = a[i];
		else {
			if (a[i] == 0){
				if (s[tp] == 0){
					if (tp > 1 && s[tp-1] == 0) tp--;
					else s[++tp] = 0;
				} else {
					s[++tp] = 0;
				}
			} else {
				if (s[tp]){
					if (tp <= 1) s[++tp] = 1;
				} 
			}
		}
	}

	return 0;
}