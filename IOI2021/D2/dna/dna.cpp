#include "dna.h"
#include <bits/stdc++.h>
using namespace std;

// int freq[2][100005][3];
int cnt[100005][9];

void init(string a, string b) {
	int n = a.length();
	a = "#"+a; b = "#"+b;
	for (int i = 1; i <= n; i++){
		// for (int j = 0; j < 3; j++){
		// 	freq[0][i][j] = freq[0][i-1][j];
		// 	freq[1][i][j] = freq[1][i-1][j];
		// }
		// freq[0][i][a[i]-'A']++;
		// freq[1][i][b[i]-'A']++;
		for (int j = 0; j < 9; j++) cnt[i][j] = cnt[i-1][j];
		if (a[i]=='A'&&b[i]=='A') cnt[i][0]++;
		if (a[i]=='A'&&b[i]=='C') cnt[i][1]++;
		if (a[i]=='A'&&b[i]=='T') cnt[i][2]++;
		if (a[i]=='C'&&b[i]=='A') cnt[i][3]++;
		if (a[i]=='C'&&b[i]=='C') cnt[i][4]++;
		if (a[i]=='C'&&b[i]=='T') cnt[i][5]++;
		if (a[i]=='T'&&b[i]=='A') cnt[i][6]++;
		if (a[i]=='T'&&b[i]=='C') cnt[i][7]++;
		if (a[i]=='T'&&b[i]=='T') cnt[i][8]++;
	}
}

int get_distance(int x, int y) {
	x++, y++;
	int ab = cnt[y][1]-cnt[x-1][1];
	int bc = cnt[y][5]-cnt[x-1][5];
	int ca = cnt[y][6]-cnt[x-1][6];
	int ba = cnt[y][3]-cnt[x-1][3];
	int cb = cnt[y][7]-cnt[x-1][7];
	int ac = cnt[y][2]-cnt[x-1][2];
	int ans = 0;
	int abab = min(ab, ba);
	ab -= abab; ba -= abab; ans += abab;
	int bcbc = min(bc, cb);
	bc -= bcbc; cb -= bcbc; ans += bcbc;
	int caca = min(ac, ca);
	ac -= caca; ca -= caca; ans += caca;
	if (ab == bc && bc == ca && ba == cb && cb == ac){
		ans += ab*2;
		ans += ba*2;
	} else {
		ans = -1;
	}
	return ans;
}


