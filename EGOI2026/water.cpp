#include <bits/stdc++.h>
using namespace std;

int n, q;
int h[200005];
bool state[200005];
int last[200005];
int cnt[200005];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; i++){
		cin >> h[i];
		state[i] = (h[i]<h[i-1]);
		last[i] = 0;
	}
	for (int i = 1; i <= q; i++){
		char op; int r, x;
		cin >> op;
		if (op == '!'){
			cin >> r >> x; r++;
			h[r] = x;
			if (r < n){
				// consider how h[r+1] and h[r] change
				bool prev = state[r+1];
				bool neu = (h[r+1]<h[r]);
				if (!prev && neu){
					last[r+1] = i;
				} else if (prev && !neu){
					cnt[r+1] += (i-last[r+1]);
				}
				state[r+1] = neu;
			}
			bool prev = state[r];
			bool neu = (h[r]<h[r-1]);
			if (!prev && neu){
				last[r] = i;
			} else if (prev && !neu){
				cnt[r] += (i-last[r]);
			}
			state[r] = neu;
		} else {
			cin >> r; r++;
			if (state[r]){
				cnt[r] += (i-last[r]);
				last[r] = i;
			}
			cout << cnt[r] << '\n';
		}
	}
	return 0;
}