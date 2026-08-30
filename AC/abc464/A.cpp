#include <bits/stdc++.h>
using namespace std;

string S; int w, e;

int main(){
	cin >> S;
	for (char c : S){
		if (c == 'W') w++;
		else e++;
	}
	if (e > w) cout << "East\n";
	else cout << "West\n";

	return 0;
}