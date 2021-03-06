/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  두개의 숫자가 공백을 두고 시간 순서대로 A, B팀의 점수를 N개 나타낸다.
 *  시간에 따른 점수를 보고 비길 수 있는 횟수의 최대값을 구한다.
 *  0,0도 비긴것으로 간주한다.
 *  
 *  (풀이)
 *  선분(fa, ca)와 선분(fb, cb)가 교차하는 것의 개수를 구하면 되며
 *  그것을 min과 max를 이용하여 min(ca, cb) - max(fa, fb)이렇게 구하였다.
 *  나머진 밑의 코드와 설명을 참조하자!
 *  
 */
#include <iostream>
using namespace std;

// f로 시작하는 것은 이전 값, c는 현재 값
int N, fa, fb, ca, cb;

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int main() {
	cin >> N;
	int ans = 1;
	for (int i = 0; i < N; i++) {
		cin >> ca >> cb;
		// (fa != fb)이게 (ca != cb)로 바뀌면 틀린다.
		// 예제3을 예로들어 0,0 에서 5,4로 가면 ans에 4를 더해주어야 하는데
		// 5,4가 서로 다르기 때문에 0,0은 비긴걸로 세었는데 또 세어버린다.
		// 만약 ans를 0에서 시작하고 ca != cb로 바꾼다고 하면 
		// 0,0 에서 0,0은 결과 값이 1이 나와야 하는데 0이 나온다.
		// 시작은 항상 0,0인 비긴 상태로 시작한다는 것에 유의하자!
		// 그리고 min(ca, cb) - max(fa, fb)이 값이 -가 나올 수 있는데
		// 그럴 때는 선분(fa, ca)와 선분(fb, cb)가 교차하는 것이 없으므로
		// ans에는 0을 더해 줄 수 있도록 max(0, bla)를 해 놓았다.
		ans += max(0, min(ca, cb) - max(fa, fb) + (fa != fb));
		fa = ca, fb = cb;
	}
	cout << ans << '\n';
	return 0;
}