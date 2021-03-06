/*
 *  BOJ 17135. 캐슬 디펜스
 *
 *  시간복잡도 : O((M)C(3) * N^2 * M)
 *  while문 의 시간 N, 넥퍼뮤 (M)C(3), 적의 최대 수 N*M
 *
 *  넥퍼뮤를 통해 궁수의 위치를 정해주고 해당 궁수의 가장 가까우면서
 *  가장 왼쪽에 있는 적을 찾아 벡터 die에 담아준다. 이렇게 모든 궁수가 적을
 *  찾았으면 die를 for문으로 돌며 해당 적을 죽인다. die를 활용하지 않고 바로 죽이면
 *  궁수는 같은 적을 사살할 수 있는데 무조건 다른적을 죽이게 되어 다른 값이 나온다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> pi;

int N, M, D;
vector<int> perm;
vector<pi> enem;

int abs(int a) {
	return a < 0 ? -a : a;
}

int taxi(pi a, pi b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	fastio();
	cin >> N >> M >> D;
	int a;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> a;
			if (a) enem.push_back({ i,j });
		}
	}
	for (int i = 0; i < M; i++) {
		if (i >= M - 3) perm.push_back(1);
		else perm.push_back(0);
	}

	int ans = 0;
	do {
		vector<pi> our;
		vector<pi> tmp = enem;
		int te = enem.size(); // total_enem
		int de = 0; // die_enem
		for (int i = 0; i < M; i++) {
			if (perm[i] == 1) our.push_back({ N, i });
		}

		while (te) {
			vector<int> die;
			for (int i = 0; i < our.size(); i++) {
				int cei = -1; // closest_enem_index
				int ced = 2e9; // closest_enem_dist

				for (int j = 0; j < tmp.size(); j++) {
					if (tmp[j].first == -1) continue;
					int dist = taxi(tmp[j], our[i]);
					if (dist > D) continue;
					if (dist < ced) {
						cei = j;
						ced = dist;
					}
					else if (dist == ced && tmp[cei].second > tmp[j].second) {
						cei = j;
					}
				}
				if (cei != -1) die.push_back(cei);
			}
			for (int i = 0; i < die.size(); i++) {
				int idx = die[i];
				if (tmp[idx].first == -1) continue;
				tmp[idx].first = -1;
				te--;
				de++;
			}
			for (int i = 0; i < tmp.size(); i++) {
				if (tmp[i].first == -1) continue;
				tmp[i].first++;
				if (tmp[i].first == N) {
					tmp[i].first = -1;
					te--;
				}
			}
		}
		ans = max(ans, de);
	} while (next_permutation(perm.begin(), perm.end()));
	cout << ans << '\n';
	return 0;
}