#include "embattle.cpp"

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

int main() {
  int n;
  assert(scanf("%d", &n) == 1);
  std::vector<int> x(n), y(n), e(n);
  for (int i = 0; i < n; ++i) {
    assert(scanf("%d%d%d", &x[i], &y[i], &e[i]) == 3);
  }

  int m;
  assert(scanf("%d", &m) == 1);
  std::vector<std::string> op(m);
  std::vector<int> arg1(m), arg2(m);
  for (int i = 0; i < m; ++i) {
    char buf[16];
    assert(scanf("%15s", buf) == 1);
    op[i] = buf;
    assert(scanf("%d", &arg1[i]) == 1);
    if (buf[1] == 'M' || buf[1] == 'A') {
      assert(scanf("%d", &arg2[i]) == 1);
    } else {
      arg2[i] = 0;
    }
  }

  std::vector<int> ans = embattle(n, x, y, e, op, arg1, arg2);
  for (int v : ans) {
    printf("%d\n", v);
  }
  return 0;
}
