// subtask 3: tree structure

#include "robot.h"
#include <bits/stdc++.h>
using namespace std;
char dir[6] = {'T', 'W', 'S', 'E', 'N', 'H'};

// scheme:
// 0 = unvisited / discarded
// 1 = in stack
// 2 = exploring W
// 3 = exploring S
// 4 = exploring E
// 5 = exploring N
// 6 = exhausted, backtrack

pair<int,char> response(vector<int> &S){
    if (S[0] == 0){
        // found destination, finish coloring
        if (S[2] == -2 && S[3] == -2){
            if (S[1] > 0) return {1, dir[1]};
            if (S[4] > 0) return {1, dir[4]};
        }
        // normal expansion branch: first time here
        for (int i = 1; i <= 4; i++){
            if (S[i] == 0){
                return {i+1, dir[i]};
            }
        }
        // dead end
        return {6, dir[5]};
    }
    bool surroundOne = 0;
    for (int i = 1; i <= 4; i++){
        if (S[i] == 1) surroundOne = 1;
    }
    if (surroundOne){
        // finish
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
        // backtrack
        if (S[0] == 6){
            for (int i = 1; i <= 4; i++){
                if (S[i] > 0) {
                    return {0, dir[i]};
                }
            }
        }
        for (int i = 2; i <= 5; i++){
            if (S[0] != i) continue;
            int lastDir = i-1;
            for (int j = lastDir+1; j <= 4; j++){
                if (S[j] == 0){
                    return {j+1, dir[j]};
                }
            }
        }
        // dead end
        return {6, dir[5]};
    }

    return {0, dir[0]};
}

void program_pulibot()
{
    for (int a = -2; a <= 6; a++){
        for (int b = -2; b <= 6; b++){
            for (int c = -2; c <= 6; c++){
                for (int d = -2; d <= 6; d++){
                    for (int e = -2; e <= 6; e++){
                        vector<int> V = {a,b,c,d,e};
                        pair<int,char> R = response(V);
                        set_instruction(V,R.first,R.second);
                    }
                }
            }
        }
    }
}
