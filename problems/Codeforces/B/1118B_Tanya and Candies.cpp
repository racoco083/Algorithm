/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  N개의 숫자가 주어지고 이 숫자에서 한 숫자를 제외하고 
 *  짝수의 합과 홀수의 합이 같은 경우의 수의 최대값을 구하여라
 *
 *  (풀이)
 *  일단 숫자들에 대해서 짝수합배열, 홀수합배열을 만들어 준다.
 *  각 자리의 숫자를 뺄때마다 짝수합과 홀수합이 같은지 본다.
 *  코드 참고!
 */

#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 200005

int N;
int es[MXN + 1];// even_sum
int os[MXN + 1];// odd_sum

int main() {
	cin >> N;
	int a;
	for (int i = 1; i <= N; i++) {
		cin >> a;
		// 짝수합, 홀수합배열을 만든다.
		os[i] = (i % 2 == 1)*a + os[i - 1];
		es[i] = (i % 2 == 0)*a + es[i - 1];
	}
	int ans = 0;
	// i를 지웠다는 건 i뒤로 나오는 짝수합은 홀수합이 된다는 것을 알 수 있다.
	// 반대로 i뒤로 나오는 홀수합은 짝수합이 된다는 것을 알 수 있다.
	// i전까지는 짝수합이면 짝수합, 홀수합이면 홀수합 그대로 구해주면된다.
	// 이렇게 i를 기준으로 앞에는 홀수합이면 i 뒤에는 짝수합을 더하면
	// i를 제외한 전체 홀수합이 된다.
	for (int i = 1; i <= N; i++) 
		ans += (os[N] - os[i] + es[i - 1] == es[N] - es[i] + os[i - 1]);
	
	cout << ans << '\n';
	return 0;
}