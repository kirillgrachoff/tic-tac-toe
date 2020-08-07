#define FASTIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
//#define PBDS
//#define POINT

#ifndef BZ
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("no-stack-protector")
//#pragma GCC target ("tune=native")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
//#pragma GCC optimize ("conserve-stack")
//#pragma GCC optimize ("no-stack-limit")
#endif

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
//using xll = __int128;
//using xld = __float128;
using str = string;
using pll = pair<ll, ll>;
template <class K, class V>
using umap = unordered_map<K, V>;
template <class T>
using uset = unordered_set<T>;

#ifdef POINT
using point = complex<ll>;
#define X real
#define Y imag
#endif

#ifdef PBDS
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
//using namespace __gnu_pbds::detail;
template <class T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#endif

const ll INF = 0x7fffffffffffffffLL;
const ll BASE =  1000000007LL; // 3 * 10**9 + 19 // 998244353 - rev pow(n, BASE - 2) - root=15311432 - root_pw = 1LL << 23
template <class T>
T MAX() {
	return std::numeric_limits<T>::max();
}
template <class T>
T MIN() {
	return std::numeric_limits<T>::min();
}

#ifdef Debug
#define LOG(v) cout << #v << " " << v << "\n";
#else
#define LOG(v) ;
#endif

#define pb push_back
#define eb emplace_back
#define all(c) c.begin(), c.end()
#define rall(c) c.rbegin(), c.rend()
#define F first
#define S second
#define forEach(c) for (auto &it : c)
#define loop while (true)
#define mp make_pair
#define mt make_tuple

template <class T>
void chMax(T &a, T b) {
	if (a < b) a = b;
}

template <class T>
void chMin(T &a, T b) {
	if (b < a) a = b;
}

inline ll divUp(ll a, ll b) {
	return (a + b - 1) / b;
}

umap<string, vector<str>> transparent(const umap<str, vector<str>> &adj) {
	umap<string, vector<string>> b;
	for (const auto &[str, v] : adj) {
		forEach(v) b[it].pb(str);
	}
	return b;
}

umap<str, vector<str>> adj;
umap<str, vector<str>> radj;
umap<string, ll> dist;

/* field format:
 * 3 * 3 chars;
 * '.' - empty
 * 'X' - cross
 * 'O' - zero
 *
 * let computer plays for 'O'
 * so, you plays for 'X'
 *
 * retroanalysis is written with these rules (win is 'O', loose is 'X')
 */

void outField(const string &s) {
	for (ll i = 0; i < 3; i++) {
		for (ll j = 0; j < 3; j++) {
			cout << s[i * 3 + j];
		}
		cout << "\n";
	}
}

bool isWinning(const string &s, char c) {
	vector<tuple<ll, ll, ll>> winPos {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 4, 8},
		{2, 4, 6}
	};
	forEach(winPos) {
		if (s[get<0>(it)] == c && s[get<1>(it)] == c && s[get<2>(it)] == c) return true;
	}
	return false;
}

#ifndef O
#ifndef X
#error "define -DO or -DX"
#endif
#endif

void recursiveMake(string &s, ll cntX, ll cntO) {
	auto &v = adj[s];
	if (isWinning(s, 'O')) {
#ifdef O
		dist[s] = 0;
#endif
#ifdef X
		dist[s] = 1;
#endif
		return;
	}
	if (isWinning(s, 'X')) {
#ifdef O
		dist[s] = 1;
#endif
#ifdef X
		dist[s] = 0;
#endif
		return;
	}
	str s_copy = s;
	for (ll i = 0; i < s.size(); i++) {
		if (s[i] != '.') continue;
		if (cntX > cntO) {
			s[i] = 'O';
			v.pb(s);
			radj[s].pb(s_copy);
			recursiveMake(s, cntX, cntO + 1);
		} else {
			s[i] = 'X';
			v.pb(s);
			radj[s].pb(s_copy);
			recursiveMake(s, cntX + 1, cntO);
		}
		s[i] = '.';
	}
}

void initAdj(string s) {
	adj["looseVrtx"] = vector<string>();
	recursiveMake(s, count(all(s), 'X'), count(all(s), 'O'));
}

void solve() {
	string s;
	for (ll i = 0; i < 9; i++) s.pb(0);
	forEach(s) cin >> it;
	initAdj(s);
	umap<string, ll> cnt;
	forEach(adj) cnt[it.F] = it.S.size();
	{ /// bfs || retroanalysis
		deque<string> q;
		forEach(radj) if (cnt[it.F] == 0) {
			q.pb(it.F);
			dist[it.F] = 0;
		}
		while (!q.empty()) {
			str v = q.front(); q.pop_front();
			if (dist[v] % 2 == 0) { /// v is loose vrtx
				forEach(radj[v]) {
					if (dist[it] % 2 == 1) continue;
					dist[it] = dist[v] + 1;
					q.pb(it);
				}
			} else { /// v is win vrtx
				forEach(radj[v]) {
					cnt[it]--;
					if (cnt[it] == 0) {
						dist[it] = dist[v] + 1;
						q.pb(it);
					}
				}
			}
		}
	}
	assert(dist[s] != 0);
	LOG(dist[s])
	if (dist[s] % 2 == 0) {
#ifdef PREDICT
		cout << "I won't win\n";
#endif
		pair<ll, str> next = mp(-1LL, "");
		forEach(adj[s]) {
			chMax(next, mp(dist[it], it));
		}
		outField(next.S);
		return;
	}
#ifdef PREDICT
	cout << "Haha! I've won!!\n";
#endif
	forEach(adj[s]) {
		if (!dist.count(it)) continue;
		if (dist[it] == dist[s] - 1) {
			outField(it);
			return;
		}
	}
	assert(false);
}

int main() {
	FASTIO
	cout << setprecision(10) << fixed;
#ifdef LOCAL
	auto start = std::chrono::system_clock::now();
#endif
#ifdef VI
	freopen("in.txt", "r", stdin);
#endif
	solve();
#ifdef LOCAL
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<ld> elapsed_seconds = end - start;
	cout << "\ntime: " << elapsed_seconds.count() << " s\n";
#endif
	return 0;
}
