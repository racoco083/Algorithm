/*
 *  BOJ 3190. 뱀
 *
 *  시간복잡도 : O(NL)
 *  뱀은 한 방향으로 최대 N번 갈 수 있으면 방향이 변할때 마다
 *  N번 갈 수 있다는 뜻이다.
 *
 *  시뮬레이션 설명대로 코드를 짜면 된다. 하지만 서로 영향을 미치는 코드와
 *  변수를 재정의 하여 사용하여 몇 번 틀렸다. 주의하자!
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <string.h>
using namespace std;
#define MXN 101
typedef pair<int, int> pi;

int N, K, R, Y, L, X;
char C;
int area[MXN + 1][MXN + 1];
bool apple[MXN + 1][MXN + 1];
char dir[MXN + 1];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int main() {
	fastio();
	cin >> N >> K;
	memset(area, -1, sizeof(area));
	for (int i = 0; i < K; i++) {
		// cin >> R >> C;로 해서 C를 재정의 해서 틀렸다.	 
		cin >> R >> Y;
		apple[R][Y] = true;
	}

	cin >> L;
	for (int i = 0; i < L; i++) {
		cin >> X >> C;
		dir[X] = C;
	}

	area[1][1] = 1;
	pi f, r;
	f = r = { 1,1 };

	int turn = 0;
	while (1) {
		turn++;
		int ry = r.first;
		int rx = r.second;

		int ny = r.first + dy[area[ry][rx]];
		int nx = r.second + dx[area[ry][rx]];
		if (ny<1 || ny>N || nx<1 || nx>N || area[ny][nx] != -1) break;

		if (dir[turn] == 'D') area[ny][nx] = (area[ry][rx] + 1) % 4;
		else if (dir[turn] == 'L') area[ny][nx] = (area[ry][rx] + 3) % 4;
		else area[ny][nx] = area[ry][rx];
		
		r = { ny, nx };
		if (!apple[ny][nx]) { // 다음 위치에 사과가 없으면 꼬리를 줄인다.
			// f = { f.first + dy[area[f.first][f.second]], f.second + dx[area[f.first][f.second]] };
			// area[f.first][f.second] = -1;
			// 밑으 코드를 위의 주석 친 코드로 바꾸면 틀린다. 서로의 값에 영향을 미쳐서
			// swap처럼 tmp => fy, fx를 만들어서 값을 따로 보관해두고 처리해야 한다.

			int fy = f.first;
			int fx = f.second;
			f = { f.first + dy[area[fy][fx]], f.second + dx[area[fy][fx]] };
			area[fy][fx] = -1;
		}
		else apple[ny][nx] = false; // 다음 위치에 사과가 있으면 해당 값을 flase로 바꿔준다.
	}
	cout << turn << '\n';
	return 0;
}