/*
 *  BOJ 16637. 괄호 추가하기
 *
 *  시간복잡도 : O(N)
 *
 *  i번째 연산자를 처리를 해주거나 처리를 하지 않으면
 *  i+1번째 연산자를 처리한다. 예를 들어 3+8*7-9이 있다고 한다면
 *  첫 번째 연산자를 처리하지 않으면 다음 연산자는 8*7을 처리하여
 *  56을 얻고 3+56을 해 준다. 이 값을 다음 매개변수로 넘겨서
 *  다음 자식이 처리하도록 한다. 항상 1~i번째 까지의 연산자를
 *  모두 처리하고 넘기는 방식이다.
 *
 */
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;
int N, n;
string s;
ll ans = -1e14;

ll max(ll a, ll b) {
	return a > b ? a : b;
}

ll operation(int op, int a, int b) {
	if (s[op] == '+') a += b;
	else if (s[op] == '*') a *= b;
	else if (s[op] == '-') a -= b;
	return a;
}

void solve(int pos, ll sum, int op) {
	if (pos >= N) {
		ans = max(ans, sum);
		return;
	}

	// operation 부분이 연산을 하는 부분으로 if, else 둘다에서 operation의
	// 두 번째 매개변수로 sum이 들어간다. 이때까지 계산한 값에 연산을 적용한다는 말이다.
	if (op) {
		n = operation(pos - 1, s[pos - 2] - '0', s[pos] - '0');
		n = operation(op, sum, n);
		solve(pos + 2, n, 0);
	}
	else {
		// pos+1번째 연산을 처리하고 pos-1번째 연산을 처리한다.
		// 이 solve는 다음 자식에서 if (op) {}안에서 처리된다.
		if (pos < N - 1) solve(pos + 2, sum, pos - 1);

		// pos-1번째 연산을 처리한다. 현재까지 계산되 sum값과 pos번째 값을 pos-1번째 연산자로 연산한다.
		n = operation(pos - 1, sum, s[pos] - '0');
		solve(pos + 2, n, 0);
	}
}

int main() {
	cin >> N;
	cin >> s;
	solve(2, s[0] - '0', 0);
	cout << ans << '\n';
	return 0;
}