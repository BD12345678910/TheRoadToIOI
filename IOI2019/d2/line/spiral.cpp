#include <bits/stdc++.h>
using namespace std;

int n, X, Y, cnt, ans;
vector<pair<int,int>> ANS;
void write(){
	ANS.push_back({X,Y});
}

struct point{
	int x, y;
} A[100005];

int find_xmax(){
	int ret = 1;
	for (int i = 2; i <= cnt; i++){
		if (A[i].x > A[ret].x) swap(i, ret);
	}
	return ret;
}

int find_xmin(){
	int ret = 1;
	for (int i = 2; i <= cnt; i++){
		if (A[i].x < A[ret].x) swap(i, ret);
	}
	return ret;
}

int find_ymax(){
	int ret = 1;
	for (int i = 2; i <= cnt; i++){
		if (A[i].y > A[ret].y) swap(i, ret);
	}
	return ret;
}

int find_ymin(){
	int ret = 1;
	for (int i = 2; i <= cnt; i++){
		if (A[i].y < A[ret].y) swap(i, ret);
	}
	return ret;
}


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("10.in", "r", stdin);
	freopen("10.out", "w", stdout);

	cin >> n; ans = 0; cnt = n;
	for (int i = 1; i <= n; i++){
		cin >> A[i].x >> A[i].y;
	}

	X = 0, Y = 0;
	while (cnt){
		if (ans % 4 == 0){
			int i = find_xmax();
			if (find_ymax()==i){
				X = A[i].x;
				write();
				Y = A[i].y;
				write();
				ans += 2;
			} else {
				X = A[i].x;
				write();
				ans += 1;
			}
			swap(A[i], A[cnt]);
			cnt--;
		} else if (ans % 4 == 1){
			int i = find_ymax();
			if (find_xmin()==i){
				Y = A[i].y;
				write();
				X = A[i].x;
				write();
				ans += 2;
			} else {
				Y = A[i].y;
				write();
				ans += 1;
			}
			swap(A[i], A[cnt]);
			cnt--;
		} else if (ans % 4 == 2){
			int i = find_xmin();
			if (find_ymin()==i){
				X = A[i].x;
				write();
				Y = A[i].y;
				write();
				ans += 2;
			} else {
				X = A[i].x;
				write();
				ans += 1;
			}
			swap(A[i], A[cnt]);
			cnt--;
		} else if (ans % 4 == 3){
			int i = find_ymin();
			if (find_xmax()==i){
				Y = A[i].y;
				write();
				X = A[i].x;
				write();
				ans += 2;
			} else {
				Y = A[i].y;
				write();
				ans += 1;
			}
			swap(A[i], A[cnt]);
			cnt--;
		}
	}
	cout << ans << '\n';
	for (auto [x, y]: ANS){
		cout << x << ' ' << y << '\n';
	}


	return 0;
}



