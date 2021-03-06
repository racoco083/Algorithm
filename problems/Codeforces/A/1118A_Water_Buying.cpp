/*
 *  시간복잡도 : O(query)
 *
 *  (문제 설명)
 *  i번째 query마다 필요한 물의 리터 n, 1리터의 물 살 때 비용 a
 *  2리터 물 살 때 비용 b가 주어진다. 이 때 딱 n리터의 물만 살 때의
 *  최소 비용을 출력하면 된다.
 *
 *  (풀이)
 *  n리터가 홀수이며 1리터의 물로 n리터를 채웠을 때 비용과 1리터 하나와
 *  나머지를 2리터로 채웠을 때 비용중에 더 작은 값을 구하고
 *  n리터가 짝수이면 1리터의 물로 n리터 채웠을 때와 2리터의 물로
 *  n리터 채웠을 때의 중에 더 작은 값을 구해서 출력하면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include<iostream>
using namespace std;
typedef long long ll;

int Q;

ll min(ll a, ll b) {
	return a > b ? b : a;
}

int main() {
	fastio();
	cin >> Q;
	ll n, a, b;
	while (Q--) {
		cin >> n >> a >> b;
		ll ans;
		if (n % 2) ans = min(n*a, a + (n - 1)/2*b);
		else ans = min(n*a, n / 2 * b);
		cout << ans << '\n';
	}
	return 0;
}