#include <bits/stdc++.h>
using namespace std;

int n, k;
pair<int,int> T[200005];

int main(){
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        cin >> T[i].second >> T[i].first;
    }
    sort(T+1, T+n+1);
    multiset<int> avai;
    int ans = 0;
    for (int i = 1; i <= k; i++) avai.insert(0);
    for (int i = 1; i <= n; i++){
        auto it = avai.upper_bound(T[i].second);
        if (it == avai.begin()) continue;
        it--;
        avai.erase(it);
        avai.insert(T[i].first);
        ans++;
    }
    cout << ans << endl;

    return 0;
}