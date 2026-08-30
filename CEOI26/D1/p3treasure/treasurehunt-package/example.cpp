#include "treasurehuntlib.h"

#include <bits/stdc++.h>
using namespace std;

int main() {
    // Local testing only. Remove this line before submission.
    InitFromFile("hunts.txt");

    while (true) {
        int N, K;
        NextHunt(N, K);
        if (N == -1) return 0;

        if (K == 1){
            // simple K = 1 solution:
            // binary search twice: (0, *) and (*, 0)
            int l = 0, r = N-1;
            while (l < r){
                int mid = (l+r)>>1;
                int res = Query(mid, 0);
                if (res&DIR_RIGHT){
                    l = mid+1;
                } else if (res&DIR_LEFT){
                    r = mid-1;
                } else {
                    l = r = mid;
                    break;
                }
            }
            int x = l;
            l = 0, r = N-1;
            while (l < r){
                int mid = (l+r)>>1;
                int res = Query(0, mid);
                if (res&DIR_DOWN){
                    l = mid+1;
                } else if (res&DIR_UP){
                    if (l == mid) r = mid; 
                    else r = mid-1;
                } else {
                    l = r = mid;
                }
            }
            int y = l;
            cout << x << ' ' << y << endl;
            Query(x, y);
        } 
        else if (K == 2){
            int xl = 0, xr = n-1;
            while (xl < xr){
                int mid = (xl+xr)>>1;
                int res = Query(mid, 0);
                if (res & DIR_RIGHT){
                    xl = mid+1;
                } else if (res & DIR_LEFT){
                    if (xl == mid) xr = mid;
                    else xr = mid-1;
                } else {
                    xl = xr = mid;
                }
            }
            int x = xl;

            int yl = 0, yr = n-1;
            while (yl < yr){
                int mid = (yl+yr)>>1;
                int res = Query(mid, x);
                if (res & DIR_DOWN){
                    xl = mid+1;
                } else if (res & DIR_UP){
                    if (xl == mid) xr = mid;
                    else xr = mid-1;
                } else {
                    xl = xr = mid;
                }
            }
            int y = yl;

            if (Query(x, y) == TREASURE){
                // Stage 2: the cross is already a treasure
            } else {
                // Stage 2: x contains a treasure, y contains a treasure
                
            }
        }
    }
}



