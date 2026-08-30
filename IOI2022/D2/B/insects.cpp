#include "insects.h"
#include <bits/stdc++.h>
using namespace std;

// In one sweep, N for all, we can find the number of different
// bugs, D. We binary search for the smallest occurrence, suppose
// k, we sweep through and admit all as long as max <= k, let
// I be the number of attained bugs. If I == k*D, then l = mid+1
// otherwise, that was too high r = mid-1;

bool yes[2005];
bool skip[2005];

int min_cardinality(int N) {
    vector<int> taken;
    for (int i = 0; i < N; i++){
        move_inside(i);
        if (press_button() > 1){
            move_outside(i);
        } else {
            taken.push_back(i);
        }
    }
    int D = taken.size();
    for (int x : taken) move_outside(x);

    if (D == 1) return N;
    if (D == N) return 1;

    int l = 2, r = N/D, ans = 1;
    int I = 0;
    while (l <= r){
        int mid = (l+r)>>1;
        vector<int> thistime;
        for (int i = 0; i < N; i++){
            if (skip[i]) continue;
            move_inside(i);
            yes[i] = 1;
            if (press_button() > mid){
                move_outside(i);
                yes[i] = 0;
            } else {
                thistime.push_back(i);
                I++;
            }
        }
        if (I == mid * D) {
            ans = mid;
            l = mid+1;
            for (int i = 0; i < N; i++){
                if (yes[i]) skip[i] = 1;
            }
        } else {
            r = mid-1;
            for (int i = 0; i < N; i++){
                if (!yes[i]) skip[i] = 1;
            }
            for (int x : thistime){
                I--;
                move_outside(x);
                yes[x] = 0;
            }
        }
    }
    return ans;
}




