// subtask 4: min dist guaranteed

#include "robot.h"
#include <bits/stdc++.h>
using namespace std;
char dir[6] = {'T', 'W', 'S', 'E', 'N', 'H'};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// scheme:
// 0 = unvisited / discarded
// 1 = finish
// 2 = exploring S
// 3 = exploring E
// 4 = exploring all
// 5 = exhausted, backtrack

pair<int,char> response(vector<int> &S){
    if (S[0] == 0){
        // found destination, finish coloring
        if (S[2] == -2 && S[3] == -2){
            if (S[1] > 0) return {1, dir[1]};
            if (S[4] > 0) return {1, dir[4]};
        }
        // normal expansion branch: first time here
        if (S[2] == 0 && S[3] == 0){
            // try a random one
            bool two = rng() % 2;
            if (two) {
                return {2, dir[2]};
            } else {
                return {3, dir[3]};
            }
        } else if (S[2] == 0){
            return {4, dir[2]};
        } else if (S[3] == 0){
            return {4, dir[3]};
        }
        // dead end
        return {5, dir[5]};
    }
    bool surroundOne = 0;
    for (int i = 1; i <= 4; i++){
        if (S[i] == 1) surroundOne = 1;
    }
    if (surroundOne){
        // finish!!
        if (S[1] == -2 && S[4] == -2){
            return {1, dir[0]};
        }
        // keep pursuing
        for (int i = 1; i <= 4; i++){
            if (S[i] > 1){
                return {1, dir[i]};
            }
        }
    }
    // normal expansion branch: not the first time here
    if (S[0] > 0){
        if (S[0] == 5){
            for (int i = 1; i <= 4; i++){
                if (S[i] > 0) {
                    return {0, dir[i]};
                }
            }
        }
        if (S[0] == 4) return {5, dir[5]};
        if (S[0] == 3) return {4, dir[2]};
        if (S[0] == 2) return {4, dir[3]};
    }

    return {0, dir[0]};
}

void program_pulibot()
{
    for (int a = -2; a <= 5; a++){
        for (int b = -2; b <= 5; b++){
            for (int c = -2; c <= 5; c++){
                for (int d = -2; d <= 5; d++){
                    for (int e = -2; e <= 5; e++){
                        vector<int> V = {a,b,c,d,e};
                        pair<int,char> R = response(V);
                        set_instruction(V,R.first,R.second);
                    }
                }
            }
        }
    }
}
                                                                                                                                                                                                                                                                                                                                                                                                       