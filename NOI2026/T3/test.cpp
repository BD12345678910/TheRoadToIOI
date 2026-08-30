#include <bits/stdc++.h>
using namespace std;

const int N = 3000;
bool prime[N+1];

int main(){
	for (int i = 1; i <= N; i++){
		prime[i] = 1;
	}
	for (int i = 2; i <= N; i++){
		if (prime[i]){
			for (int j = 2*i; j <= N; j+=i){
				prime[j] = 0;
			}
		}
	}
	int cnt = 0;
	for (int i = 2; i <= N; i++){
		if (prime[i]) {
			cout << i << endl;
		}	
	}
	cout << cnt << endl;

	return 0;
}