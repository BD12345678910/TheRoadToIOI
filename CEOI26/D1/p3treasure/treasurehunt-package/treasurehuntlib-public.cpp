#include "treasurehuntlib.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::cerr;
using std::ifstream;
using std::pair;
using std::string;
using std::vector;

namespace {

struct Hunt {
    int n;
    vector<pair<int, int>> treasure;
};

vector<Hunt> hunts;
int current_hunt = -1;
int query_count = 0;
vector<unsigned char> found;
bool initialized = false;
bool finished = false;

[[noreturn]] void fail(const string &message) {
    cerr << "[treasurehuntlib] RTE: " << message << '\n';
    std::exit(1);
}

void report_current() {
    if (current_hunt < 0 || current_hunt >= (int)hunts.size()) return;

    int got = 0;
    for (unsigned char x : found) got += x != 0;

    cerr << "[treasurehuntlib] hunt " << current_hunt + 1
         << ": found " << got << "/" << hunts[current_hunt].treasure.size()
         << ", queries " << query_count << '\n';
}

bool valid_hunt(const Hunt &h) {
    if (h.n < 2 || h.n > 1000000) return false;
    if (h.treasure.empty() || h.treasure.size() > 3) return false;

    std::set<pair<int, int>> seen;
    for (auto [x, y] : h.treasure) {
        if (x < 0 || x >= h.n || y < 0 || y >= h.n) return false;
        if (!seen.insert({x, y}).second) return false;
    }
    return true;
}

vector<long long> read_all_numbers(const char *fileName) {
    ifstream in(fileName);
    if (!in) fail(string("cannot open file: ") + fileName);

    vector<long long> a;
    long long x;
    while (in >> x) a.push_back(x);

    if (!in.eof()) fail("input file contains a non-integer token");
    return a;
}

bool parse_with_count(const vector<long long> &a, vector<Hunt> &out) {
    if (a.empty()) return false;

    long long H = a[0];
    if (H < 0 || H > 100000) return false;

    size_t p = 1;
    vector<Hunt> tmp;
    tmp.reserve((size_t)H);

    for (long long tc = 0; tc < H; ++tc) {
        if (p + 1 >= a.size()) return false;

        long long N = a[p++], K = a[p++];
        if (N < 2 || N > 1000000 || K < 1 || K > 3) return false;
        if (p + 2 * (size_t)K > a.size()) return false;

        Hunt h;
        h.n = (int)N;
        for (int i = 0; i < K; ++i) {
            h.treasure.push_back({(int)a[p], (int)a[p + 1]});
            p += 2;
        }

        if (!valid_hunt(h)) return false;
        tmp.push_back(std::move(h));
    }

    if (p != a.size()) return false;
    out = std::move(tmp);
    return true;
}

bool parse_until_eof(const vector<long long> &a, vector<Hunt> &out) {
    size_t p = 0;
    vector<Hunt> tmp;

    while (p < a.size()) {
        if (p + 1 >= a.size()) return false;

        long long N = a[p++], K = a[p++];
        if (N < 2 || N > 1000000 || K < 1 || K > 3) return false;
        if (p + 2 * (size_t)K > a.size()) return false;

        Hunt h;
        h.n = (int)N;
        for (int i = 0; i < K; ++i) {
            h.treasure.push_back({(int)a[p], (int)a[p + 1]});
            p += 2;
        }

        if (!valid_hunt(h)) return false;
        tmp.push_back(std::move(h));

        if (tmp.size() > 100000) return false;
    }

    if (tmp.empty()) return false;
    out = std::move(tmp);
    return true;
}

void make_default_hunts() {
    // Deterministic local tests used only when InitFromFile() was not called.
    std::mt19937 rng(2026);
    hunts.clear();

    const int sizes[] = {4, 8, 31, 100, 1000, 1000000};
    for (int N : sizes) {
        for (int K = 1; K <= 3; ++K) {
            Hunt h;
            h.n = N;
            std::set<pair<int, int>> used;

            while ((int)h.treasure.size() < K) {
                int x = (int)(rng() % N);
                int y = (int)(rng() % N);
                if (used.insert({x, y}).second)
                    h.treasure.push_back({x, y});
            }
            hunts.push_back(std::move(h));
        }
    }
}

} // namespace

void InitFromFile(const char *fileName) {
    if (initialized || current_hunt != -1)
        fail("InitFromFile must be called before the first NextHunt");
    if (fileName == nullptr)
        fail("InitFromFile received a null filename");

    vector<long long> a = read_all_numbers(fileName);
    vector<Hunt> parsed;

    if (!parse_with_count(a, parsed) && !parse_until_eof(a, parsed))
        fail("invalid hunt-file format");

    hunts = std::move(parsed);
    initialized = true;
}

void NextHunt(int &N, int &K) {
    if (finished)
        fail("NextHunt called after it already returned N = K = -1");

    if (!initialized) {
        make_default_hunts();
        initialized = true;
    }

    report_current();

    ++current_hunt;
    query_count = 0;
    found.clear();

    if (current_hunt >= (int)hunts.size()) {
        N = K = -1;
        finished = true;
        cerr << "[treasurehuntlib] all hunts finished\n";
        return;
    }

    const Hunt &h = hunts[current_hunt];
    N = h.n;
    K = (int)h.treasure.size();
    found.assign(K, 0);
}

int Query(int x, int y) {
    if (!initialized || current_hunt < 0)
        fail("Query called before the first NextHunt");
    if (finished || current_hunt >= (int)hunts.size())
        fail("Query called after all hunts finished");

    const Hunt &h = hunts[current_hunt];

    if (x < 0 || x >= h.n || y < 0 || y >= h.n)
        fail("Query coordinates out of range");

    ++query_count;
    if (query_count > 1000)
        fail("more than 1000 queries in one hunt");

    for (int i = 0; i < (int)h.treasure.size(); ++i) {
        if (h.treasure[i].first == x && h.treasure[i].second == y) {
            found[i] = 1;
            return TREASURE;
        }
    }

    long long best = std::numeric_limits<long long>::max();
    for (auto [tx, ty] : h.treasure) {
        long long d = std::llabs((long long)tx - x)
                    + std::llabs((long long)ty - y);
        best = std::min(best, d);
    }

    int result = 0;
    for (auto [tx, ty] : h.treasure) {
        long long d = std::llabs((long long)tx - x)
                    + std::llabs((long long)ty - y);
        if (d != best) continue;

        if (tx > x) result |= DIR_RIGHT;
        if (tx < x) result |= DIR_LEFT;
        if (ty > y) result |= DIR_DOWN;
        if (ty < y) result |= DIR_UP;
    }

    if (result == 0)
        fail("internal error: non-treasure query produced no direction");

    return result;
}
