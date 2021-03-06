/*
 *  BOJ 16235. 나무 재테크
 *
 *  시간복잡도 : O(?)
 *
 *  봄에는 나무가 자신의 나이만큼 양분을 먹고 나이가 1 증가한다.
 *  여름에는 봄에 죽은 나무가 양분으로 변해 해당 영역에 죽은 나무 나이/2
 *  의 값이 양분이 된다.
 *  가을에는 나무의 나이가 5의 배수이면 번식하며 인접한 8개 영역에 나이
 *  1인 나무가 생긴다. 
 *  겨울에는 그냥 정해진 양분을 모든 영역에 추가해주면 된다.
 *  나무를 담는 자료구조를 벡터로 쓰면 모든 것이 해결된다.
 *  입력으로 받은 나무를 담아서 벡터에 담은 뒤 이 벡터의 사이즈 vs를 구해
 *  vs-1부터 0까지 나무를 체크하면서 죽으면 죽은 표시, 나이가 증가해야 하면 나이를 먹이고
 *  동시에 번식하는 것 까지 해결이 가능하다. 번식하면 그냥 벡터에 push_back
 *  하면 된다. 벡터의 사이즈는 바뀌어도 vs는 바뀌지 않기 때문이고,
 *  그리고 나중에 다시 봄이 되어도 vs를 똑같이 구해 vs-1부터 0까지 나무를
 *  체크하면 된다. 여름에는 벡터를 처음부터 뒤지면서 죽은나무를 찾아
 *  양분으로 만들어 주면 된다. 이 과정에서 다른 벡터 tmp에 산 나무만
 *  담아주어 벡터가 tmp를 복사하면 된다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
using namespace std;
#define MXN 11

class Tree {
public:
	int x, y, z;
	bool die;
	Tree(int _x, int _y, int _z) : x(_x), y(_y), z(_z) { die = false; }
	Tree() { die = false; }
};

int N, M, K;
int food[MXN + 1][MXN + 1];
int area[MXN + 1][MXN + 1];

int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

vector<Tree> vc;

// 나무가 번식한다.
void grow(int y, int x) {
	for (int i = 0; i < 8; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny<1 || ny>N || nx<1 || nx>N) continue;
		vc.push_back(Tree(nx, ny, 1));
	}
}

int main() {
	fastio();
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> food[i][j];
			area[i][j] = 5;
		}
	}

	int x, y, z;
	for (int i = 0; i < M; i++) {
		cin >> y >> x >> z;
		vc.push_back(Tree(x, y, z));
	}

	while (K--) {
		int vs = vc.size();
		// vector vc의 맨 뒤 값 부터 보면서 나이를 먹을 수 있으면 먹이면서 이게 또 번식할 수 있으면 번식시킨다.
		// 나이를 먹을 수 없으면 죽었다는것을 표시만 해준다.
		for (int i = vs - 1; i >= 0; i--) {
			int cy = vc[i].y;
			int cx = vc[i].x;
			int cz = vc[i].z;

			if (area[cy][cx] >= cz) {
				area[cy][cx] -= cz;
				vc[i].z++;
				if ((vc[i].z % 5) == 0) {
					grow(cy, cx);
				}
			}
			else {
				vc[i].die = true;
			}
		}

		vector<Tree> tmp;
		// 죽은 표시를 이용해 죽은 나무는 양분이 되고 산 나무는 tmp에 담는다.
		for (int i = 0; i < vc.size(); i++) {
			if (vc[i].die) {
				area[vc[i].y][vc[i].x] += (vc[i].z / 2);
			}
			else {
				tmp.push_back(vc[i]);
			}
		}

		// tmp의 값을 vc로 복사
		vc.clear();
		vc = tmp;
		tmp.clear();

		// 겨울이므로 양분업!
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				area[i][j] += food[i][j];
			}
		}
	}
	// K년이 지난 후 나무의 개수는 곧 vc의 개수이다.
	cout << vc.size() << '\n';
	return 0;
}