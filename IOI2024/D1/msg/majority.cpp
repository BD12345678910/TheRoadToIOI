#include <bits/stdc++.h>
#include "message.h"
using namespace std;

void send_message(vector<bool> M, vector<bool> C) { 
    for (bool c: M){
        vector<bool> Q(31, c);
        send_packet(Q);
    }
}

vector<bool> receive_message(vector<vector<bool>> R) {
    vector<bool> Ret;
    for (auto V : R){
        int zero = 0, one = 0;
        for (bool b: V){
            if (b) one++;
            else zero++;
        }
        if (one > zero) Ret.push_back(1);
        else Ret.push_back(0);
    }
    return Ret;
}





/*

Further thoughts:

in 89, it is possible to give the places naively

however, when communicating the places, some places may still be used!!!

*/

