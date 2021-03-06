/*
 *  BOJ 2110. 공유기 설치
 *
 *  시간복잡도 : O(Nlog(1e9))
 *  공간복잡도 : O(N)
 *  
 *  이분탐색을 통해 mid를 인접한 공유기 사이 거리의 최소값으로 설정한다.
 *  mid값을 기준으로 house를 선형탐색하면서 공유기 설치한 개수를 cnt에 저장한다.
 *  이때 좌표상 0에 제일 가까운 집은 공유기를 무조건 설치해야한다. 이 집 다음에
 *  처음 공유기를 설치한다고 하면 같은 거리에서 더 적거나 같은 공유기의 개수를
 *  구한다. cnt의 값이 C보다 같거나 더 크다면 distance를 늘린다. 반대의 경우에는
 *  distance를 줄힌다.
 *
 */

#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 200002

int N, C;
int house[MXN];

int get_cnt(int d) {// distance
	int cnt = 1;
	int cur = house[0];
	for (int i = 1; i < N; i++) {
		if (house[i] - cur >= d) {
			cnt++;
			cur = house[i];
		}
	}
	return cnt;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int bs(int s, int e) {
	int ans = 0;
	while (s <= e) {
		int m = (e + s) / 2;
		int cnt = get_cnt(m);
		if (cnt >= C) {
			ans = max(ans, m);
			// 밑의 코드하면 틀린다.
			// if(cnt == C) ans = max(ans, m);
			// 4 3
			// 1 2 3 4 를 예로들면
			// cnt의 값은 3이 나올 수 없다.
			// 하지만 cnt의 값이 4가 될 수는있다.
			// 특정 공유기 사이의 거리 값을 더 크게 하면 된다.
			// 공유기를 1,2,4에 설치하는 식으로 말이다.
			// 그래도 가장 인접한 두 공유기 사이의 최대 값은 바뀌지 않지만
			// cnt를 4개에서 3개로 만들 수 있다. 그러므로 cnt == 4는
			// cnt == 3 을 포함한다.
			s = m + 1;
		}
		else e = m - 1;
	}
	return ans;
}

int main() {
	cin >> N >> C;
	for (int i = 0; i < N; i++) {
		cin >> house[i];
	}
	sort(house, house + N);
	cout << bs(1, 1000000000) << '\n';
	return 0;
}


























