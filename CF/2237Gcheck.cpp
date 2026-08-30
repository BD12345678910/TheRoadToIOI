#include <bits/stdc++.h>
using namespace std;
const int N = 1000000;
int prime[112];
bool sieve[N+5];

void findP(){
	int cnt = 0;
	for (int i = 2; i <= N; i++){
		if (!sieve[i]){
			prime[++cnt] = i;
			if (cnt == 110) return;
			for (int j = i+i; j <= N; j+=i){
				sieve[j] = 1;
			}
		}
	}
}

bool isLarge(int x){
	for (int i = 1; i <= 110; i++){
		while (x % prime[i] == 0) x /= prime[i];
	}
	return (x > 1);
}

int main(){
	findP();
	for (int i = 1; i <= 110; i++) cout << prime[i] << ' ';
	cout << '\n';
	int cnt = 0;
	for (int i = 1; i <= N; i++){
		cnt += isLarge(i);
	}
	cout << cnt << endl;
}

