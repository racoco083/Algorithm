/*
 *  BOJ 1141. 접두사
 *  
 *  시간복잡도 : O(NlogN * L) (L : 문자열 길이)
 *
 *  문자열에 대해 정렬을 한 다음 (0 base) 인덱스 1부터 시작해
 *  i-1번째 문자열과 i번째 문자열을 비교해서 i번째에 i-1번째 문자열이
 *  포함되어 있으면 find 함수는 i번째 문자열에서 i-1번째 문자열의 시작
 *  위치를 리턴한다. 만약 이것이 0이면 i-1은 i의 접두사라고 보면 된다.
 *  이런 식으로 전체 문자열의 개수에서 접두사가 되는 문자열을 빼 주면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int N;
vector<string> vc;

int main() {
	fastio();
	cin >> N;
	string str;
	for (int i = 0; i < N; i++) {
		cin >> str;
		vc.push_back(str);
	}
	sort(vc.begin(), vc.end());
	int ans = vc.size();
	for (int i = 1; i < vc.size(); i++) {
		if (vc[i].find(vc[i-1]) == 0) {
			ans--;
		}
	}
	cout << ans << '\n';
	return 0;
}