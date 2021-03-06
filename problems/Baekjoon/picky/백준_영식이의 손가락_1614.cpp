/*
 *  BOJ 1614. 영식이의 손가락
 *
 *  시간복잡도 : O(1)
 *
 *  다친 손가락이 첫 번째 인지, 마지막인지, 아니면 2,3,4번째 손가락인지
 *  경우를 나누어서 계산해야 한다. 입력이 5 1 이면 답이 12가 나와야 하는데
 *  ans += 8 * (C / 2) + 8 - N;이렇게 해버리면 4가 나온다. => 2,3,4번째 손가락
 *  처리 할때처럼 마지막 손가락 처리하면 틀린다! 주의!
 *  
 */
#include <iostream>
using namespace std;
typedef long long ll;

ll N, C;

int main() {
	cin >> N >> C;
	ll ans = 0;
	if (N == 1) ans = 8 * C;
	else if (N == 5) ans = 4 + 8 * C;
	else {
		ans++;// 첫 검지
		if (C % 2 == 0) ans += 8 * (C / 2) + N - 2;
		else ans += 8 * (C / 2) + 8 - N;
	}
	cout << ans << '\n';
	return 0;
}