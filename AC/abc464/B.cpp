#include <bits/stdc++.h>
using namespace std;

int H, W;
char a[52][52];
int xmx, xmn, ymx, ymn;

int main(){
	cin >> H >> W;
	xmx = 0, xmn = 100;
	ymx = 0, ymn = 100;
	for (int i = 1; i <= H; i++){
		for (int j = 1; j <= W; j++){
			cin >> a[i][j];
			if (a[i][j] == '#'){
				xmx = max(xmx, i);
				xmn = min(xmn, i);
				ymx = max(ymx, j);
				ymn = min(ymn, j);
			}
		}
	}
	for (int i = xmn; i <= xmx; i++){
		for (int j = ymn; j <= ymx; j++){
			cout << a[i][j];
		}
		cout << '\n';
	}
	return 0;
}