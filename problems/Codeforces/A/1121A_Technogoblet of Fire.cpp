/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  N개의 학생에 대해서 각각 파워와 학교의 숫자가 주어진다.
 *  파워는 숫자가 클수록 높은 것이다. 어떤 기계는 학교에서 가장
 *  강한 학생 한명씩만 선발한다. K의 수가 주어지며 이 K개의 숫자의
 *  인덱스 학생들이 모두 선택되도록 할 때 추가해야할 학교의 최소 개수는
 *  몇 개인가?
 *
 *  (풀이)
 *  입력 받으면서 해당 학생이 현재 다니는 학교의 짱이 될 수 없는 경우의
 *  개수가 곧 추가해야할 학교의 개수이다.
 *  
 */
#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 100

int N, M, K;
int mv[MXN + 1];
int school[MXN + 1];
int power[MXN + 1];
int main() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) cin >> power[i];
	for (int i = 1; i <= N; i++) {
		cin >> school[i];
		if (mv[school[i]] < power[i]) mv[school[i]] = power[i];
	}
	int a;
	int ans = 0;
	for (int i = 0; i < K; i++) {
		cin >> a;
		if (mv[school[a]] != power[a]) ans++;
	}
	cout << ans << '\n';
	return 0;
}