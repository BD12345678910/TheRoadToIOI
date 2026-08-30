#include <bits/stdc++.h>
using namespace std;

int press(string s);

string nextchar(string S, string A, string B, string C){
	int res = press(S+A+A+S+A+B+S+A+C+S+B);
	int k = (int)S.length();
	if (res == k+1){
		return S + B;
	} else if (res == k+2){
		return S + A; 
	} else {
		return S + C;
	}
}

string guess_sequence(int N){
	int r1 = press("AX"), r2;
	string S, A, B, C; 
	if (r1){
		r2 = press("A");
		if (r2) S = "A";
		else S = "X";
	} else {
		r2 = press("B");
		if (r2) S = "B";
		else S = "Y";
	}
	if (N == 1) return S;
	if (S == "A") A = "B", B = "X", C = "Y";
	if (S == "B") A = "A", B = "X", C = "Y";
	if (S == "X") A = "B", B = "A", C = "Y";
	if (S == "Y") A = "B", B = "X", C = "A";
	for (int i = 2; i <= N-1; i++){
		S = nextchar(S, A, B, C);
	}
	r1 = press(S+A+S+B);
	if (r1 == N){
		r2 = press(S+A);
		if (r2==N) S = S+A;
		else S = S+B;
	} else {
		S = S+C;
	}
	return S;
}