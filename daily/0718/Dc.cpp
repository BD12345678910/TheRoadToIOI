#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int P=998244353;

int main(){
    int n; string s;
    cin >> n >> s;
    ll dp = 0, sum = 1;
    for (char c: s){
    	int x = c-'0';
    	dp = (10*dp+x*sum%P)%P;
    	sum = (sum+dp)%P;
    }
    cout << dp << endl;
}