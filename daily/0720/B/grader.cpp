#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)

#include "graph.cpp"

static const int maxn = 210;

static int _n;
static bool _adj[maxn + 5][maxn + 5];
static int _quota;

void init(int n)
{
	_n = n;
	_quota = 0;
	int m;
	assert(scanf("%d", &m) == 1);
	memset(_adj, 0, sizeof _adj);
	REP(i, 0, m)
	{
		int u, v;
		assert(scanf("%d%d", &u, &v) == 2);
		_adj[u][v] = _adj[v][u] = 1;
	}
}

static int _pa[maxn + 5];

static int _get(int x) { return _pa[x] == x ? x : _pa[x] = _get(_pa[x]); }

bool query(vector<pair<int, int> > banned_edges)
{
	++_quota;
	static bool banned[maxn + 5][maxn + 5];
	memset(banned, 0, sizeof banned);
	REP(i, 0, (int)banned_edges.size())
	{
		assert(banned_edges[i].first >= 0 && banned_edges[i].first < _n);
		assert(banned_edges[i].second >= 0 && banned_edges[i].second < _n);
		assert(banned_edges[i].first != banned_edges[i].second);
		banned[banned_edges[i].first][banned_edges[i].second] = 1;
		banned[banned_edges[i].second][banned_edges[i].first] = 1;
	}
	REP(i, 0, _n) _pa[i] = i;
	REP(i, 0, _n) REP(j, 0, _n - 1)
		if (_adj[i][j] && !banned[i][j]) _pa[_get(i)] = _get(j);
	REP(i, 1, _n) if (_get(i) != _get(0)) return 0;
	return 1;
}

static int col[maxn + 5];
static bool adj[maxn + 5][maxn + 5];

static bool dfs(int x)
{
	REP(y, 0, _n) if (adj[x][y])
	{
		if (~col[y])
		{
			if (col[y] == col[x]) return 0;
		}
		else
		{
			col[y] = !col[x];
			if (!dfs(y)) return 0;
		}
	}
	return 1;
}

int main()
{
	int n;
	assert(scanf("%d", &n) == 1);
	init(n);
	memcpy(adj, _adj, sizeof adj);

	vector<int> out = check_bipartite(n);

	printf("%d\n", (int)out.size());
	REP(i, 0, (int)out.size()) printf("%d%c", out[i], " \n"[i + 1 == (int)out.size()]);

	memset(col, -1, sizeof col);
	col[0] = 0;
	bool ok = dfs(0);
	static bool mark[maxn + 5];
	memset(mark, 0, sizeof mark);
	REP(i, 0, (int)out.size()) mark[out[i]] = 1;

	if (ok != (out.size() > 0))
	{
		fprintf(stderr, "Wrong Answer.\n");
		return 0;
	}
	if (out.size())
	{
		REP(i, 1, _n) if ((mark[i] ^ col[i]) != (mark[0] ^ col[0]))
		{
			fprintf(stderr, "Wrong Answer.\n");
			return 0;
		}
	}
	if (_quota > 2000)
	{
		fprintf(stderr, "Too many queries: %d\n", _quota);
		return 0;
	}
	fprintf(stderr, "OK. Queries: %d\n", _quota);
	return 0;
}
