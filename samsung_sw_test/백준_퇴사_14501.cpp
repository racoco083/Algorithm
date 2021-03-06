/*
 *  BOJ 14501. 퇴사
 *
 *  시간복잡도 : O(?)
 *  
 *  현재날짜와 이익을 매개변수로 넘겨주는 dfs를 통해
 *  현재 날짜로부터 N까지 날짜 i를 다 보면서 i날 상담했을 때
 *  i + 상담 기간이-1(i날도 포함해서 -1하였다.) N보다 작거나 같으면
 *  상담을 할 수 있는 것이므로 상담을 해서 ans에 p+i날 상담할 때
 *  얻는 이익 중에 더 큰 값을 넣는다.
 *  
 *  첫 번째 실수 인덱스 i인데 다른 값을 넣는 실수를 하였다.
 *
 *  두 번째 실수 필요없는 코드를 넣었다.
 *  
 */
#include <iostream>
using namespace std;
typedef pair<int, int> pi;
#define MXN 16

int N;
pi arr[MXN + 1];
int ans = 0;

int max(int a, int b) {
	return a > b ? a : b;
}

void dfs(int c, int p) {// cur_day, pay
	/*if (c > N) {
		ans = max(ans, p);
		return;
	}*/
	// 위의 코드를 넣어서 틀렷다. 밑의 for문 안에서 날짜가 N보다 크면
	// dfs를 실행하지 않는다.
	
	for (int i = c; i <= N; i++) {
		// if (c + arr[i].first-1 <= N)
		// 위의 코드에서 i가 들어갈 자리에 c를 넣어서 틀렸다.
		// i를 넣어야 하는데 초기 값을 넣는 실수를 한다.
		if (i + arr[i].first-1 <= N) {
			ans = max(ans, p + arr[i].second);
			dfs(i + arr[i].first, p + arr[i].second);
		}
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i].first >> arr[i].second;
	}

	dfs(1, 0);
	cout << ans << '\n';
	return 0;
}