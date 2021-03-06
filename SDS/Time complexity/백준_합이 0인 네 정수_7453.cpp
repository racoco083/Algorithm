/*
 *  A 배열과 B배열의 값들 중 더한 모든 경우를 AB배열에 넣는다. 
 *  최대 4000*4000개의 개수가 된다. C배열과 D배열도 마찬가지로
 *  CD배열을 만든다. CD배열을 오름차순 정렬한 후 AB배열의 원소 
 *  하나하나를 보고 CD배열에서 -AB[i]값을 찾으면 4배열의 각 원소의
 *  합이 0인 경우가 된다. ub와 lb를 사용하여서 개수를 구하면 된다.
 *  이 때 만약 AB 4000*4000의 원소가 다 -1이고 CD 4000*4000의 원소가
 *  다 1이면 4000*4000*4000*4000개의 경우가 답이 된다.
 *  ans의 자료형을 long long으로 하였다.
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 4002

typedef long long ll;

int N;
int A[MXN], B[MXN], C[MXN], D[MXN];
int AB[MXN*MXN];
int CD[MXN*MXN];
const int INF = 2e9;

int lb(int s, int e, int v) {
	while (s < e) {
		int m = (e + s) / 2;
		if (CD[m] >= v) e = m;
		else s = m + 1;
	}
	return e;
}

int ub(int s, int e, int v) {
	while (s < e) {
		int m = (e + s) / 2;
		if (CD[m] <= v) s = m + 1;
		else e = m;
	}
	return e;
}

int main() {
	fastio();
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> A[i] >> B[i] >> C[i] >> D[i];
	}
	int abi = 0;
	int cdi = 0;

	// AB배열을 구한다.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			AB[abi++] = A[i] + B[j];
		}
	}
	
	// CD배열을 구한다.
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			CD[cdi++] = C[i] + D[j];
		}
	}

	// 도달할 수 없는 INF값을 하나 넣어서
	// lb, ub의 인덱스가 여기를 가르킬 수 있도록 한다.
	CD[cdi++] = INF;
	sort(CD, CD + cdi);

	// AB의 각 원소의 -값을 CD배열에서 몇개가있는 개수를
	// 구래 ans에 누적한다.
	ll ans = 0;
	for (int i = 0; i < abi; i++) {
		int li = lb(0, cdi - 1, -AB[i]);
		int ui = ub(0, cdi - 1, -AB[i]);
		ans += (ui - li);
	}
	cout << ans << '\n';
	return 0;
}