// subtask 4: min dist guaranteed

#include "robot.h"
#include <bits/stdc++.h>
using namespace std;
char dir[6] = {'T', 'W', 'S', 'E', 'N', 'H'};
int opp[5] = {0, 3, 4, 1, 2};

// scheme:
// 0 = unvisited
// 1 = finish
// 2 = fa = W
// 3 = fa = S
// 4 = fa = E
// 5 = fa = N

bool is_opp(vector<int> &S, int i){
    if (S[i] < 2) return 0;
    int od = S[i]-1;
    return opp[i] == od;
}

pair<int,char> response(vector<int> &S){
    // a finishing state
    if (S[0] == 0 && S[2] == -2 && S[3] == -2){
        for (int i = 1; i <= 4; i++){
            if (S[i] >= 2 && is_opp(S, i)){
                return {1, dir[i]};
            }
        }
    }

    bool surroundOne = 0;
    for (int i = 1; i <= 4; i++){
        if (S[i] == 1) surroundOne = 1;
    }
    if (surroundOne){
        // terminate
        if (S[1] == -2 && S[4] == -2){
            return {1, dir[0]};
        }
        // backtrack
        for (int i = 1; i <= 4; i++){
            if (is_opp(S, i)){
                return {1, dir[i]};
            }
        }
    }

    // i am an ith level new
    if (S[0] == 0){
        if (S[1] == -2 && S[4] == -2){
            return {2, 'H'};
        }

        // go back to the parent
        for (int i = 1; i <= 4; i++){
            if (S[i] >= 2 && is_opp(S, i)){
                return {i+1, dir[i]};
            }
        }
    }

    if (S[0] >= 2 && S[0] <= 5){
        int nxt = S[0]+1;
        if (nxt == 6) nxt = 2;
        if (S[nxt-1] == 0){
            return {nxt, dir[nxt-1]};
        }
        if (S[nxt-1] >= 2 && (is_opp(S, nxt-1))){
            return {nxt, dir[nxt-1]};
        }
        return {nxt, dir[5]};
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
                                                                                                                                                                                                                                                                                                                                                                                                       