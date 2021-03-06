/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  N개의 숫자가 있고, M개의 숫자를 사용해서 가장 큰 숫자를 만든다.
 *  숫자는 K번까지만 연속해서 사용할 수 있다. 
 *
 *  (풀이)
 *  숫자 중에 가장 큰 숫자 두개만 사용하면 된다. 예를 들어 
 *  1 3 3 7 4 2 라는 숫자가 있고 숫자를 9번 사용할 수 있고
 *  2번까지 연속해서 사용할 수 있다면 7 7 4 7 7 4 7 7 4로 9개를 쓰면
 *  54로 최대 숫자를 만들 수 있다. 그러면 sum = k개의 가장 큰 수 +
 *  1개의 두번째로 큰 수를 의 개수는 k+1이다. m을 k+1로 나누어서
 *  나눈 수 만큼 sum에 곱해준다. 그리고 m을 k+1로 나눈 나머지 * 가장 큰 수
 *  를 sum에 더해주면 된다.
 *  
 */
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 200002
typedef long long ll;

ll N, M, K;
ll a[MXN + 1];

int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) cin >> a[i];
	sort(a, a + N);
	ll f = a[N - 1], s = a[N - 2];
	ll ans = K * f + s;
	ans *= (M / (K + 1));
	ans += (M % (K + 1)) * f;
	cout << ans << '\n';
	return 0;
}