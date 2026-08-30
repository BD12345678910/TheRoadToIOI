#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>

#include "multi.h"

namespace {

using u64 = unsigned long long;
const int RN = 5120, N_MAX = 256;
const u64 A_MAX = (1ULL << 48) - 1;

enum {
  INVALID_B_LENGTH = 1,
  WRONG_ANSWER = 2,
  NO_ANSWER = 3,
  INCONSISTENT = 4,
};

void wrong(int code) {
  std::cout << "Wrong Answer [" << code << "]" << std::endl;
}

void accepted(int round) {
  std::cout << "Accepted: " << round << std::endl;
}

u64 get(std::string var) {
  u64 x;
  std::cin >> x;
  if (std::cin.fail()) {
    std::cerr << "Error while reading input for " << var << ".\n";
    std::abort();
  }
  return x;
}

u64 find_X(const int N, const std::vector<std::vector<u64>>& A) {
  u64 x = 0;
  std::vector<bool> near(N);
  near[0] = true;
  for (int t = 0; t < N - 1; t++) {
    u64 mn = -1;
    int i_mn = -1, j_mn = -1;
    for (int i = 0; i < N; i++) {
      if (!near[i]) continue;
      for (int j = 0; j < N; j++) {
        if (near[j]) continue;
        u64 w = A[i][j] * N * N + i * N + j;
        if (mn > w) {
          mn = w;
          i_mn = i;
          j_mn = j;
        }
      }
    }
    x += A[i_mn][j_mn];
    near[j_mn] = true;
  }
  return x;
}

bool is_inconsistent(int N, int r, int i, std::vector<u64> A,
                     std::vector<u64> B, std::vector<u64> res) {
  static std::map<std::tuple<int, int, int, std::vector<u64>, std::vector<u64>>,
                  std::vector<u64>>
      m;
  auto [p, f] = m.try_emplace({N, r, i, A, B}, res);
  return !f && p->second != res;
}

void game() {
  // input
  const int N = (int)get("N");
  assert(2 <= N && N <= N_MAX);
  const int R = RN / N;
  std::vector A(N, std::vector<u64>(N));
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      std::string var =
          "A[" + std::to_string(i) + "][" + std::to_string(j) + "]";
      A[i][j] = A[j][i] = get(var);
      assert(A[i][j] <= A_MAX);
    }
  }
  const u64 X = find_X(N, A);
  // rounds
  std::vector B(N, std::vector<u64>(N));
  for (int r = 0; r < R; r++) {
    std::vector<std::vector<u64>> C(N);
    for (int i = 0; i < N; i++) {
      auto& res = C[i];
      res = strategy(N, r, i, A[i], B[i]);
      if (res.size() != 1 && (int)res.size() != N) {
        return wrong(INVALID_B_LENGTH);
      }
      if (is_inconsistent(N, r, i, A[i], B[i], res)) {
        return wrong(INCONSISTENT);
      }
      if (res.size() == 1) {
        if (res[0] == X) return accepted(r + 1);
        return wrong(WRONG_ANSWER);
      }
    }
    // Update B for the next round
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        B[i][j] = C[j][i];
      }
    }
  }
  return wrong(NO_ANSWER);
}

}  // namespace

int main() {
  const int T = (int)get("T");
  for (int t = 0; t < T; t++) {
    game();
  }
}
