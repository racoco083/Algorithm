/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  N개의 사탕상자가 있고 그 개수는 다 다르다 사탕상자를 두 개씩 짝지어
 *  K로 나누어 떨어지는 모든 사탕상자의 개수를 출력한다.  
 *  
 *  (풀이)
 *  K는 최대 100이다. N개의 사탕상자 모두를 K로 나눈 나머지를 인덱스로 하여
 *  chk배열에 개수를 카운트 한다. 이 배열을 뒤지면서 합이 K가 되는 쌍의
 *  개수를 찾으면 된다.
 *  
 */

#include <iostream>
using namespace std;

#define MXN 102

int N, K;
int chk[MXN + 1];
int min(int a, int b) {
	return a > b ? b : a;
}

int main() {
	cin >> N >> K;
	int a;
	for (int i = 0; i < N; i++) {
		cin >> a;
		chk[a%K]++;
	}
	int ans = chk[0] / 2;
	for (int i = 1; i <= K / 2; i++) {
		if (i == K - i) ans += chk[i] / 2;
		else ans += min(chk[i], chk[K - i]);
	}
	cout << ans * 2 << '\n';
	return 0;
}