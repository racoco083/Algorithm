/*
 *  시간복잡도 : O(NlogN)
 *
 *  (문제 설명)
 *  N은 항상 짝수이고 N개의 수가 주어지는데 1, 2..N/2이 두개 씩 있다.
 *  인덱스 0 1 2 3 4 5
 *  값     1 1 2 2 3 3
 *  위와 같이 값이 있을 때 A,B가 인덱스 0인 위치에 있다.
 *  각각 숫자를 오름차순 순으로 방문할 때 이동한 거리의 최소 값을 구한다.
 *  거리는 인덱스 차이이다. 인덱스 0에서 2로 가면 2의 거리 비용이 든다.
 *  (풀이)
 *  입력받은 값과 인덱스를 쌍으로 해서 pi 배열 a에 담는다.
 *  그리고 값에 대해 정렬 한 다음 A, B가 각각 1에 가고 
 *  A가 두개의 2의 값 중 첫 번째에 간 거리 + B가 2의 값 두 번째에
 *  간 거리와 A가 2의 값 두 번째에 간 거리 + B가 2의 값 첫 번째에
 *  간 거리 중에 더 작은 값을 그리디 하게 구하는 것을 3, 4..N/2
 *  에 대해 반복해 주면 된다.
 *  
 */
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 200002
typedef pair<int, int> pi;

int N;
pi a[MXN + 1];

int min(int a, int b) {
	return a > b ? b : a;
}

int abs(int a) {
	return a < 0 ? -a : a;
}

int main() {
	cin >> N;
	N *= 2;
	int b;
	for (int i = 0; i < N; i++) {
		cin >> b;
		a[i] = { b, i };
	}
	sort(a, a + N);
	long long ans = a[0].second + a[1].second;
	for (int i = 2; i < N; i += 2) {
		ans += min(
			abs(a[i - 2].second - a[i].second) + abs(a[i - 1].second - a[i + 1].second)
			, abs(a[i - 1].second - a[i].second) + abs(a[i - 2].second - a[i + 1].second)
		);
	}
	cout << ans << '\n';
	return 0;
}