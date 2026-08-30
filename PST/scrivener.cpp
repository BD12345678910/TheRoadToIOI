#include <bits/stdc++.h>
using namespace std;

int n;
int go[1000006][21];
char c[1000006];
int len[1000006];

int main(){
	cin >> n;
	int currvs = 0;
	// go[0][*] = 0
	while (n--){
		char op; cin >> op;
		if (op == 'T'){
			cin >> c[++currvs];
			len[currvs] = len[currvs-1]+1;
			go[currvs][0] = currvs-1;
			for (int i = 1; i <= 20; i++){
				go[currvs][i] = go[go[currvs][i-1]][i-1];
			}
		} else if (op == 'U'){
			int x; cin >> x;
			// copy everything from currvs-x-1
			currvs++;
			for (int i = 0; i <= 20; i++){
				go[currvs][i] = go[currvs-x-1][i];
			}
			c[currvs] = c[currvs-x-1];
			len[currvs] = len[currvs-x-1];
		} else if (op == 'P'){
			int x; cin >> x;
			int curr = currvs;
			for (int i = 20; i >= 0; i--){
				if (len[curr]-1-x >= (1<<i)){
					curr = go[curr][i];
				}
			}
			cout << c[curr] << '\n';
		}
	}
	return 0;
}