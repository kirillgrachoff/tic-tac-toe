#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using str = string;
using pll = pair<ll, ll>;
template <class K, class V>
using umap = unordered_map<K, V>;
template <class T>
using uset = unordered_set<T>;

umap<string, vector<str>> transparent(const umap<str, vector<str>> &adj) {
	umap<string, vector<string>> b;
	for (const auto &[str, v] : adj) {
		for (auto &it : v) b[it].push_back(str);
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
	for (auto &it : winPos) {
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
			v.push_back(s);
			radj[s].push_back(s_copy);
			recursiveMake(s, cntX, cntO + 1);
		} else {
			s[i] = 'X';
			v.push_back(s);
			radj[s].push_back(s_copy);
			recursiveMake(s, cntX + 1, cntO);
		}
		s[i] = '.';
	}
}

void initAdj(string s) {
	adj["looseVrtx"] = vector<string>();
	recursiveMake(s, count(s.begin(), s.end(), 'X'), count(s.begin(), s.end(), 'O'));
}

void solve() {
	string s;
	for (ll i = 0; i < 9; i++) s.push_back(0);
	for (auto &it : s) cin >> it;
	initAdj(s);
	umap<string, ll> cnt;
	for (auto &it : adj) cnt[it.first] = it.second.size();
	{ /// bfs || retroanalysis
		deque<string> q;
		for (auto &it : radj) if (cnt[it.first] == 0) {
			q.push_back(it.first);
			dist[it.first] = 0;
		}
		while (!q.empty()) {
			str v = q.front(); q.pop_front();
			if (dist[v] % 2 == 0) { /// v is loose vrtx
				for (auto &it : radj[v]) {
					if (dist[it] % 2 == 1) continue;
					dist[it] = dist[v] + 1;
					q.push_back(it);
				}
			} else { /// v is win vrtx
				for (auto &it : radj[v]) {
					cnt[it]--;
					if (cnt[it] == 0) {
						dist[it] = dist[v] + 1;
						q.push_back(it);
					}
				}
			}
		}
	}
	assert(dist[s] != 0);
	if (dist[s] % 2 == 0) {
#ifdef PREDICT
		cout << "I won't win\n";
#endif
		pair<ll, str> next = make_pair(-1LL, "");
		for (auto &it : adj[s]) {
			next = max(next, make_pair(dist[it], it));
		}
		outField(next.second);
		return;
	}
#ifdef PREDICT
	cout << "Haha! I've won!!\n";
#endif
	for (auto &it : adj[s]) {
		if (!dist.count(it)) continue;
		if (dist[it] == dist[s] - 1) {
			outField(it);
			return;
		}
	}
	assert(false);
}

int main() {
	cout << setprecision(10) << fixed;
	solve();
	return 0;
}
