/*
 *  A와 B에 대해서 누적합을 구하고 A와 B에 대해 모든 부분합을 구한
 *  pa, pb배열을 만든다. pb값만 오름 차순 정렬해서 T-a[i]값을 한 fi값에
 *  대한 li와 ui를 구해 ui-li를 ans에 누적으로 더해주면 ans가 곧 답이된다.
 *  pb에서 fi를 찾기만 하면 a[i]값과 더해서 T를 만들 수 있다는 소리이기
 *  때문에 해당 하는 값의 개수를 ui-li로 구할 수 있다.
 *  ans의 자료형을 int로 하여서 여러 번 틀렸다. ans의 값은 pa[i]의 값이
 *  모두 같다고 한다면 10^6개가 되고 이 값에 대해 pb의 값도 모두 같다고
 *  한다면 10^6 * 10^6이 되어 10^12이다. 이것을 생각하지 못 해 여러번
 *  틀렸다.
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 1001

typedef long long ll;

int A[MXN];
int B[MXN];
int pa[MXN*MXN];// possible a의 부분합
int pb[MXN*MXN];// poosible b의 부분합
int T, N, M;
const int INF = 2e9;

int lb(int s, int e, int v) {
	while (s < e) {
		int m = (e + s) / 2;
		if (pb[m] >= v) e = m;
		else s = m + 1;
	}
	return e;
}

int ub(int s, int e, int v) {
	while (s < e) {
		int m = (e + s) / 2;
		if (pb[m] <= v) s = m + 1;
		else e = m;
	}
	return e;
}

int main() {
	fastio();
	cin >> T;
	// A와 B의 누적합을 만든다.
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> A[i];
		A[i] += A[i - 1];
	}
	cin >> M;
	for (int i = 1; i <= M; i++) {
		cin >> B[i];
		B[i] += B[i - 1];
	}

	// A와 B의 부분합이 되는 것의 최대개수는 각각 1000000개이다.
	// 그 값을 다 만들어 저장해 준다.
	int ai = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < i; j++) {
			pa[ai++] = A[i] - A[j];
		}
	}
	int bi = 0;
	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < i; j++) {
			pb[bi++] = B[i] - B[j];
		}
	}

	// 내가 만든 ub와 li로는 ui - li를 하면 ui가 마지막 값+1을 가리켜야 하는데
	// 마지막 값을 가리킬 때가 있다. 그럴때를 대비해 도달할 수 없는 INF값을 pb에
	// 넣어서 ui가 마지막 값+1을 가리킬 수 있도록 하였다.
	// pb값만 오름차순 정렬하고 T값에 pa[i]값을 빼준 fi값을 pb에서 몇개나 있는지
	// 찾으면서 ans에 누적으로 더해준다. 그러면 ans가 답이 된다.
	pb[bi++] = INF;
	sort(pb, pb + bi);
	// 여기서 
	ll ans = 0;
	for (int i = 0; i < ai; i++) {
		ll fi = T - pa[i];
		int li = lb(0, bi - 1, fi);
		int ui = ub(0, bi - 1, fi);
		ans += (ui - li);
	}
	cout << ans << '\n';
	return 0;
}