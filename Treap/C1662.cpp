#include <bits/stdc++.h>
using namespace std;
 
int n;
long long bin[200005];
 
int main(){
    cin >> n;
    long long suma = 0; bin[0]++;
    for (int i = 1; i <= n; i++){
        int a; cin >> a;
        suma = ((suma+a)%n+n)%n;
        bin[suma]++;
    }
    long long ans = 0;
    for (int i = 0; i <= n; i++){
        ans += bin[i] * (bin[i]-1) / 2;
    }
    cout << ans << endl;
    
    return 0;
}