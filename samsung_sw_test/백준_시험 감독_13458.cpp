/*
 *  BOJ 13458. 시험 감독
 *
 *  시간복잡도 : O(N)
 *
 *	모든 시험장에는 총감독관이 있어야 한다. 그러므로 각 시험장 A[i]에
 *  총감독관이 감시할 수 있는 수 B를 빼면 된다. 그래서 ans = N을 넣어주고
 *  이때의 A[i]값을 C로 나눠 올림한 값을 ans에 +=해주면 된다.
 *  
 *  첫 번째 실수 ans의 최대값은 10^12인데 int로 하여 한 번 틀렸다.
 *
 *  두 번째 실수 int a=3, b=4하고 ceil(a/b)하면 원하는 값을 못 얻는다.
 *  왜냐하면 a와 b는 int형이라 int형으로 처리된 결과가 나온다.
 *  답은 1인데 0이 나온다. a와 b의 자료형을 double로 바꾸면 해결된다.
 *  
 */
#include <iostream>
#include <cmath>
using namespace std;
#define MXN 1000000
typedef long long ll;
double A[MXN + 1];
double N, B, C;

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> A[i];
	cin >> B >> C;
	ll ans = N;
	for (int i = 0; i < N; i++) {
		A[i] -= B;
		if (A[i] > 0) {
			ans += ceil(A[i] / C);
		}
	}
	cout << ans << '\n';
	return 0;
}