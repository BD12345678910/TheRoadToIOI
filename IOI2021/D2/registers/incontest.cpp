#include "registers.h"
#include <bits/stdc++.h>
using namespace std;
static const int M = 100;
static const int B = 2000;

void construct_instructions(int s, int n, int k, int q) {
	if (k == 2){
		vector<bool> FOUR(B, 0); FOUR[2] = 1; 
		append_store(99, FOUR);
		int four = 99;
		vector<bool> ONE(B, 0); ONE[0] = 1;
		append_store(98, ONE);
		int one = 98;
		// vector<bool> THREE(B, 0); 
		// THREE[1] = 1; THREE[0] = 1;
		// append_store(97, THREE);
		// int three = 97;

		// 0: b1 b0 a1 a0
		append_move(1, 0);
		append_right(1, 1, 2);
		// 1:       b0 b1
		append_xor(2, 0, 1);
		// 3: b1<a1 b0<a0
		append_and(3, 0, 2);
		append_print(3);
		// 4: b1=a1 b0=a0
		append_not(4, 2);
		append_or(4, four, 4);
		append_right(4, 4, 1);
		// 4: 1     b1=a1
		append_print(4);
		append_and(5, 3, 4);
		// 5: b1<a1 b1=a1butb0<a0
		append_right(6, 5, 1);
		// 6: ?     b1<a1
		append_or(7, 5, 6);
		append_and(7, one, 7);
		append_print(7);
		// 7: 0000 0 b<a
		append_left(8, 7, 1);
		// 8: 0000 b<a 0
		append_or(9, 7, 8);
		append_print(0);
		append_not(10, 9);
		// append_and(10, 10, three);
		append_print(10);
		append_and(11, 9, 1);
		append_print(11);
		append_and(12, 10, 0);
		append_print(12);
		append_or(0, 11, 12);
	}
	return;
}



