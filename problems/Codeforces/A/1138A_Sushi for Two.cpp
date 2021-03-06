/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  N개의 입력으로 1과 2가 주어지는데 1이나 2가 연속하게 주어진 것만
 *  생각하여 이런 연속한 1과 2가 붙어 있을 때 각 개수는 같아야한다.
 *  이 때 이 길이를 출력하라. 예를 들어 11212122이면 답은 12나 21이다.
 *
 *  (풀이)
 *  입력받은 값 처음부터 끝까지 연속한 것의 개수를 벡터 vc에 담았다.
 *  2221122라면 벡터에는 3,2,2가 된다는 것을 알 수 있다. 그리고
 *  벡터의 i-1번째와 i번째는 항상 숫자가 다른 것을 알 수 있다.
 *  연속해야하지만 벡터에 담기니 말이다. 이렇게 구해서 벡터의
 *  i-1값과 i값중에 더 작은 개수의 최대값을 구하면 된다.
 *  
 */
#include <iostream>
#include <vector>
using namespace std;
#define MXN 100002

int N;
vector<int> vc;
int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int main() {
	cin >> N;
	int f = 0, c = 0, cnt = 1;// former, cur
	cin >> f;
	for (int i = 1; i < N; i++) {
		cin >> c;
		if (c == f) cnt++;
		else {
			vc.push_back(cnt);
			cnt = 1;
		}
		f = c;
	}
	vc.push_back(cnt);
	int ans = 0;
	for (int i = 1; i < vc.size(); i++) 
		ans = max(ans, min(vc[i - 1], vc[i]));
	
	cout << ans * 2 << '\n';
	return 0;
}