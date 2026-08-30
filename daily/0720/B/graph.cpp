#include "graph.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> A;
vector<int> B;
vector<int> C;
vector<pair<int,int>> V;

void check(int rb){
	V.clear();
	for (int i = 0; i <= rb; i++){
		int c = C[i];
		for (int j : A){
			V.push_back({c, j});
		}
		for (int j : B){
			V.push_back({c, j});
		}
	}
}

vector<int> check_bipartite(int n){
	for (int i = 1; i < n; i++) C.push_back(i);
	A.push_back(0);

	// do n-1 insertions
	for (int t = 1; t < n; t++){
		// binary search for first disconnect [1, mid]
		int l = 0, r = n-t-1;
		while (l < r){
			int mid = (l+r)>>1;
			// query(x) returns connected
			check(mid);
			if (query(V)) l = mid+1;
			else r = mid;
		}
		int p = l;
		// cout << p << endl;
		// check remove A;
		check(p-1);
		for (int a : A) V.push_back({C[p], a});
		bool conna = query(V);
		check(p-1);
		for (int b : B) V.push_back({C[p], b});
		bool connb = query(V);
		if (conna == connb){ vector<int> MT; return MT;}
		vector<int> tmp;
		if (!conna){
			B.push_back(C[p]);
		} else {
			A.push_back(C[p]);
		}
		for (int i = 0; i < p; i++){
			tmp.push_back(C[i]);
		}
		for (int i = p+1; i < (int)C.size(); i++){
			tmp.push_back(C[i]);
		}
		C = tmp;
	}	

	return A;
}


