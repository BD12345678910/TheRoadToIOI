#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, x;
map<ll,int> m;
 
int main(){
    cin >> n >> x;
    ll s = 0, ans = 0;
    m[0] = 1;
    for (int i = 1; i <= n; i++){
        int a; cin >> a;
        s += a;
        if (m.count(s-x)) ans += m[s-x];
        m[s]++;
    }
    cout << ans << endl;
    return 0;
}