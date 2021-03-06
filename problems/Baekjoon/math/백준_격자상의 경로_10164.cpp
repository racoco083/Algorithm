// 고등학생 때 배운 최단 경로 기법을 사용하였다.
// dp[i][j] : 특정 시작점으로 부터 i, j까지의 최단 경로 수
// dp는 0으로 초기화 되어 있다. dp[1][1]에 1을 주어
// dp[i][j] = dp[i][j - 1] + dp[i - 1][j];를 해 주면 된다.
// K가 0일 때는 1,1부터 탐색하며 N,M까지 가는 모든 경로를
// 구하면 되고,  K가 0이 아닐 때는 
// K의 값을 2차원 배열의 인덱스로 구한다. E라고 하겠다.
// 1,1부터 E까지의 모든 경로 구하고 E부터 N,M까지의 
// 모든 경로를 구했다. 답은 dp[N][M]이 된다. 

#include <iostream>
using namespace std;

class Pos {
public:
	int y, x;
	Pos(int _y, int _x) : y(_y), x(_x) {}
	Pos() {}
};

int dp[16][16];
int N, M, K;
Pos S, E;

void fill() {
	for (int i = S.y; i <= E.y; i++) {
		for (int j = S.x; j <= E.x; j++) {
			if (i == 1 && j == 1) continue; // 1,1일 때는 값이 이미 있으니 무시
			dp[i][j] = dp[i][j - 1] + dp[i - 1][j];
		}
	}
}

// 일차원 배열로 된 인덱스를 2차원 배열의 인덱스로 바꾼다.
Pos OtoT(int k) {
	return Pos(k / M + 1, k%M + 1);
}

void swap(Pos &a, Pos &b) {
	Pos tmp = a;
	a = b;
	b = tmp;
}

int main() {
	cin >> N >> M >> K;
	dp[1][1] = 1;
	if (K == 0) {
		S.y = 1, S.x = 1;
		E.y = N, E.x = M;
		fill();
	}
	else {
		K--;
		S.y = 1, S.x = 1;
		E = OtoT(K);
		fill();
		S.y = N, S.x = M;
		swap(S, E);
		fill();
	}
	cout << dp[N][M] << '\n';

	return 0;
}