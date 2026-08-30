#include <bits/stdc++.h>
#include "parrots.cpp"
using namespace std;

const int MAXN = 128;
const int MAXL = 10000;

int message[MAXN];
int encoded[MAXL];
int decoded[MAXN];

int L = 0;
int decodedLength = 0;

void send(int x) {
    encoded[L++] = x;
}

void output(int x) {
    decoded[decodedLength++] = x;
}

int main() {
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> message[i];
    }

    // Produce encoded[0 ... L-1].
    encode(N, message);

    cout << "Encoded message:\n";
    for (int i = 0; i < L; i++) {
        cout << encoded[i] << ' ';
    }
    cout << '\n';

    // Simulate parrots arriving in an arbitrary order.
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    shuffle(encoded, encoded + L, rng);

    cout << "Shuffled message:\n";
    for (int i = 0; i < L; i++) {
        cout << encoded[i] << ' ';
    }
    cout << '\n';

    // Recover decoded[0 ... N-1].
    decode(N, L, encoded);

    cout << "Decoded message:\n";
    for (int i = 0; i < decodedLength; i++) {
        cout << decoded[i] << ' ';
    }
    cout << '\n';

    bool correct = (decodedLength == N);

    for (int i = 0; i < N; i++) {
        if (decoded[i] != message[i]) {
            correct = false;
        }
    }

    cout << (correct ? "Correct\n" : "Incorrect\n");
}