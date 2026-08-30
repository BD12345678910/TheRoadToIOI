#include <bits/stdc++.h>
using namespace std;
const int sX = 5261;
const int sY = 4945;
int n, X, Y, cnt, ans;
vector<pair<int,int>> ANS;
void write(){
	ans++;
	ANS.push_back({X,Y});
}

struct point{
	int x, y;
} A[100005];

vector<point> Q3;
vector<point> Q4;

bool cmp(point A, point B){
	return A.x < B.x;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	freopen("02.in", "r", stdin);
	freopen("02.out", "w", stdout);
	cin >> n; ans = 0;
	for (int i = 1; i <= n; i++){
		cin >> A[i].x >> A[i].y;
		if (A[i].x > sX){
			if (A[i].y > sY) Q4.push_back(A[i]);
			else Q3.push_back(A[i]);
		} else {
			if (A[i].y > sY) Q3.push_back(A[i]);
			else Q4.push_back(A[i]);
		}
	}

	sort(Q4.begin(), Q4.end(), cmp);
	bool turn = 1;
	for (auto v : Q4){
		if (turn) X = v.x;
		else Y = v.y;
		turn = !turn;
		write();
	}
	if (turn) X = 10002;
	else Y = 10000;
	write();
	Y = 10001;
	write();
	X = 0;
	write();

	sort(Q3.begin(), Q3.end(), cmp);
	turn = 0;
	for (auto v : Q3){
		if (turn) X = v.x;
		else Y = v.y;
		turn = !turn;
		write();
	}
	if (turn) X = 10002;
	else Y = 0;
	write();
	
	cout << ans << '\n';
	for (auto [x, y]: ANS){
		cout << x << ' ' << y << '\n';
	}

	return 0;
}



