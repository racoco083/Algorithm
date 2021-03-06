/*
 *  시간복잡도 : O(N^2logN)
 *
 *  (문제 설명)
 *  어떤 교차점을 기준으로 가로의 모든 값에 대한 순번을 매기고
 *  세로의 모든 값에 대한 순번을 매긴다. 이렇게 구한 순번에서
 *  교차점의 순번은 가로, 세로 중 더큰 순번을 가지고 이 때의
 *  가로, 세로 중 가장 큰 순번을 모든 교차점에 대해서 구하면 된다.
 *
 *  (풀이)
 *  처음에 N^3으로 풀 생각을 했는데 시간초과, 그래서 입력값에 대한
 *  대칭 행렬도 추가로 만들었다. 그냥 행렬은 각 열에대해서 순번을 매겼고
 *  대칭 행렬은 각 행에 대해서 순번을 매겼다. 이 때 각 열과 행에 대해 가장 큰 순번을
 *  따로 저장해두었다. 그러면 i,j에 대한 해당 순번을
 *  ans = max(mat[i][j], symmat[j][i])로 O(1)에 알 수 있다.
 *  그리고 가로 줄 제일 큰 값과 mat[i][j]와의 차이와 세로 줄 제일 큰 값과
 *  symmat[j][i]의 차이 중에 더큰 값을 ans에 더해주면 답이된다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MXN 1002

typedef pair<int, int> pi;
int N, M;
int mat[MXN + 1][MXN + 1];
int symmat[MXN + 1][MXN + 1];

void solve(int *p, int range) {
	pi temp[MXN + 1];
	for (int i = 0; i < range; i++) temp[i] = { p[i], i };
	sort(temp, temp + range);
	int num = 1;
	p[temp[0].second] = num;
	for (int i = 1; i < range; i++) p[temp[i].second] = num += temp[i - 1].first < temp[i].first;
	p[range] = num;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	fastio();
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> mat[i][j];
			symmat[j][i] = mat[i][j];
		}
	}
	for (int i = 0; i < N; i++) solve(mat[i], M);
	for (int i = 0; i < M; i++) solve(symmat[i], N);
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << max(mat[i][j], symmat[j][i]) + max(mat[i][M] - mat[i][j], symmat[j][N] - symmat[j][i]) << ' ';
		}
		cout << '\n';
	}
	return 0;
}