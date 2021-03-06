/*
 *  BOJ 1461. 도서관
 *
 *  시간복잡도 : O(NlogN)
 *
 *  입력으로 들어오는 음수와 양수를 음수벡터, 양수벡터에 담아준다.
 *  이때 음수는 -해주어 넣어준다. 그리고 오름차순 정렬한 다음
 *  각 벡터의 마지막 위치에서 M씩 낮추면서 해당 인덱스의 값*2를
 *  ans에 더해주면 된다. 마지막에 두 벡터 중에 가장 큰 값을 한 번
 *  빼야 한다. 마지막으로 가는 위치는 다시 0으로 돌아올 필요가 없기 때문이다.
 *	
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> pv; // plus_vector
vector<int> mv; // mius_vector
int N, M;

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	fastio();
	cin >> N >> M;
	int a; // 입력 값
	for (int i = 0; i < N; i++) {
		cin >> a;
		// 음수면 mv에 반대면 pv에 값을 넣는다.
		if (a < 0) mv.push_back(-a);
		else pv.push_back(a);
	}

	sort(mv.begin(), mv.end());
	sort(pv.begin(), pv.end());
	int ans = 0;
	int	mi = 0;
	int pi = 0;

	// 각 벡터 뒤에서 부터 시작해서 M씩 인덱스 낮춰가며 해당 인덱스의 값*2를 ans에 더해준다.
	for (int i = mv.size() - 1; i >= 0; i -= M) ans += mv[i] * 2;
	for (int i = pv.size() - 1; i >= 0; i -= M) ans += pv[i] * 2;

	// 두 벡터 중에 가장 큰 값을 찾아 한 번 빼준다. 마지막 값은
	// 돌아오지 않아도 되기 때문이다.
	int mxv = 0;
	if (!pv.empty()) mxv = max(mxv, pv[pv.size() - 1]);
	if (!mv.empty()) mxv = max(mxv, mv[mv.size() - 1]);

	ans -= mxv;
	cout << ans << '\n';
	return 0;
}

/*
6 2
-3 -2 -1 1 2 3
*/