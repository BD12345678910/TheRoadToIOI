#include "dungeons.cpp"
#include <vector>
#include <cassert>
#include <cstdio>

static int N, q;
static std::vector<int> s, p, z;
static std::vector<int> w, l, x;
static std::vector<long long> answer;

int main() {
	assert(scanf("%d %d", &N, &q) == 2);
	s.resize(N);
	p.resize(N);
	w.resize(N);
	l.resize(N);
    x.resize(q);
    z.resize(q);
    answer.resize(q);

	for (int i = 0; i < N; i++) {
		assert(scanf("%d", &s[i]) == 1);
	}
	for (int i = 0; i < N; i++) {
		assert(scanf("%d", &p[i]) == 1);
	}
	for (int i = 0; i < N; i++) {
		assert(scanf("%d", &w[i]) == 1);
	}
	for (int i = 0; i < N; i++) {
		assert(scanf("%d", &l[i]) == 1);
	}


    init(N, s, p, w, l);

    for (int i = 0; i < q; i++) {
		assert(scanf("%d %d", &x[i], &z[i]) == 2);
		answer[i] = simulate(x[i], z[i]);
    }
    fclose(stdin);

    for (int i = 0; i < q; i++) {
        printf("%lld\n", answer[i]);
    }
    fclose(stdout);
    return 0;
}
