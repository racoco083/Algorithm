/*
 *  BOJ 17071. 숨바꼭질 5
 *
 *  시간복잡도 : O(N)
 *
 *  discovered 배열을 이용해 수빈이가 이동하며 해당 위치에 홀수시간에 방문한 최소시간과 
 *  짝수 시간에 방문한 최소시간을 담는다. 동생이 t초 후에 방문한 곳에서
 *  discovered배열을 뒤져 만약 t가 짝수시간이면 해당 위치의 수빈이가 방문한
 *  짝수시간의 값과 현재 t의 값의 차이가 짝수이면 수빈이는 진동을 하여 동생을
 *  t시간에 만날 수 있다는 것을 뜻한다. 만약 t가 홀수이면 discovered의 홀수시간을
 *  뒤져서 이것도 역시 t와의 시간차이가 짝수면 동생은 진동해서 수빈이를 만날 수
 *  있으니 답은 t가 된다.
 *  
 *  처음에 discovered[MXN + 1][2]를 discovered[MXN + 1]로만 하면 구할 수 있을 줄 알았다.
 *  하지만 수빈이의 초기 위치가 15이면 15->14->28->29로 홀수시간(3초) 만에 29를 방문할 수 있다.
 *  하지만 1차원 discovered로 하면 15->30->29로 먼저 방문되어 짝수시간(2초)만에 29를 방문한 것만
 *  알 수 있다. 즉, 15->14->28->29의 홀수시간(3초)은 무시된다. 동생이 23의 위치에 있으면 23->24->26->29로 
 *  홀수 시간에 29를 방문한다. 이때 29에는 2가 저장되어 있어 동생이 방문한 시간 3과 차이가 1이다. 
 *  그러므로 진동을 해도 만날 수 없다고 판단하여 답을 출력할 수 없다. 
 *
 */

#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <queue>
#include <string.h>
using namespace std;
#define MXN 500000

int N, K;
int discovered[MXN + 1][2];

void subin(int s) {
	queue<int> qu;
	discovered[s][0] = 0;
	qu.push(s);
	int t = 0;
	while (!qu.empty()) {
		int qsize = qu.size();
		if (t % 2 == 0) t = 1;
		else t = 0;

		for (int i = 0; i < qsize; i++) {
			int cur = qu.front();
			qu.pop();

			if (cur - 1 >= 0 && discovered[cur - 1][t] == -1) {
				discovered[cur - 1][t] = discovered[cur][(t + 1) % 2] + 1;
				qu.push(cur - 1);
			}
			if (cur + 1 <= MXN && discovered[cur + 1][t] == -1) {
				discovered[cur + 1][t] = discovered[cur][(t + 1) % 2] + 1;
				qu.push(cur + 1);
			}
			if (cur * 2 <= MXN && discovered[cur * 2][t] == -1) {
				discovered[cur * 2][t] = discovered[cur][(t + 1) % 2] + 1;
				qu.push(cur * 2);
			}
		}
	}
}

int bro(int s) {
	int cur = s;
	int t = 0;// time
	for (int i = 0; cur + i <= MXN; i++) {
		cur += i;
		if (discovered[cur][t%2] <= t) 
			if ((t - discovered[cur][t%2]) % 2 == 0) return t;
		t++;
	}
	return -1;
}

int main() {
	fastio();
	cin >> N >> K;
	memset(discovered, -1, sizeof(discovered));
	subin(N);
	cout << bro(K) << '\n';
	return 0;
}