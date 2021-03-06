/*
 *  BOJ 2140. 지뢰찾기
 *
 *  시간복잡도 : O(N^2)
 *  
 *  항상 테두리에는 숫자가 적혀있고 나머지 공간은 #이다.
 *  첫 번째 #부터 시작해서 주위 9방향에 숫자가 있는지 파악하고 있는데 0이면
 *  이 곳에는 지뢰를 놓을 수 없다. 또한 9방향 전부다 #이면 지뢰의 최대값을
 *  찾는 것이므로 여긴 무조건 지뢰를 두면 된다. 만약 숫자가 있는데 0이 없다면
 *  현재 위치에 지뢰를 깔고 주위 숫자들만 1씩 감소시켜 주면 된다.
 *  이렇게 지뢰를 설치한 개수를 마지막에 리턴해주면 된다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
using namespace std;
#define MXN 101

int N;
char area[MXN + 1][MXN + 1];
int dy[9] = { -1, -1, -1, 0, 1, 1, 1, 0 };
int dx[9] = { -1, 0, 1, 1, 1, 0, -1, -1 };

int main() {
	fastio();
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> area[i][j];
		}
	}

	int ans = 0;
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < N - 1; j++) {
			bool islm = true;
			for (int k = 0; k < 9; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (area[ny][nx] == '#') continue;
				if (area[ny][nx] == '0') {// 인접한 칸에 0이 쓰여있으면 i,j는 지뢰가 아니다.
					islm = false;
					break;
				}
			}

			if (!islm) continue;
			ans++;
			for (int k = 0; k < 9; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];
				if (area[ny][nx] == '#') continue;
				area[ny][nx]--;
			}
		}
	}

	cout << ans << '\n';
	return 0;
}