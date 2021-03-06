/*
 *  BOJ 3098. 소셜네트워크
 *  
 *  시간복잡도 : O(N^3)
 *  
 *  총 사람은 N명이 있다. i번째 사람의 배열에 관계를 체크한다.  
 *  만약 1과 2가 관계를 가지면 chk[1][2], chk[2][1]을 1로 만들어
 *  체크한다. (1,1), (2,2)...(N,N) 도 다 chk[i][i]에 1로 체크한다.
 *  chk[i][1~N]을 확인하면서 관계가 있는 사람을 찾아 그 사람이 관계를
 *  가지고 있는 모든 친구를 확인해 i의 친구로 만들어 준다.
 *  
 *  첫 번째 실수
 *  chk관계 보고 관계를 처리할 때 다른 tmp에 저장해두었다가
 *  나중에 memcpy(chk, tmp)해주어야 한다. 다른 i번째 사람도 현재 
 *  chk의 값을 보고 친구 관계를 만드는데 chk를 수정하면서 찾으면
 *  수정한 값이 다른 사람들에게 영향을 미치면 안 되는데 미치게 된다.
 *
 *  두 번째 실수
 *  내가 짠 프로그램은 i번째 사람이 i+1과 친구여서 i+1의 모든 친구를
 *  친구로 만들어서 친구로 만든 횟수를 세아렸다. 그런데 i+2와도 친구여서
 *  i+2의 모든 친구를 뒤졌는데 i+1과 공동으로 친구인 사람을 세아려 버리면
 *  같은 사람을 여러번 세아려 버린다. 그래서 바뀐 값 tmp와
 *  chk의 바뀐값의 개수를 세아려 해결하였다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define MXN 52

int N, M;
bool chk[MXN + 1][MXN + 1];
bool tmp[MXN + 1][MXN + 1];
int cnt[MXN + 1];
vector<int> date;

bool chk_relation() {
	for (int i = 1; i <= N; i++) {
		if (cnt[i] != N) return false;
	}
	return true;
}

void wide_relation(int c, int n) {
	for (int i = 1; i <= N; i++) {
		if (chk[n][i] && !chk[c][i]) tmp[c][i] = 1;
	}
}

int main() {
	fastio();
	cin >> N >> M;
	int a, b;
	int rc = 0; // relation_cnt
	for (int i = 1; i <= N; i++) rc++;

	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		chk[a][a] = chk[a][b] = 1;
		rc++;
		chk[b][a] = chk[b][b] = 1;
		rc++;
	}

	memcpy(tmp, chk, sizeof(tmp));

	while (true) {
		if (rc >= N*N) break;
		int prc = 0; // partial_relation_count
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (i == j) continue;
				if (chk[i][j]) wide_relation(i, j);
			}
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (chk[i][j] != tmp[i][j]) prc++;
			}
		}
		rc += prc;
		memcpy(chk, tmp, sizeof(tmp));
		date.push_back(prc);
	}
	cout << date.size() << '\n';
	// 무조건 2명씩 관계를 가지므로 각 날짜에 친구를 추가한 횟수/2하여 출력한다.
	// 1과 2의 관계와 2와 1의 관계는 하나로 같기 때문이다.
	for (int i = 0; i < date.size(); i++) cout << date[i] / 2 << '\n';
	return 0;
}

/*
5 4
1 2
2 3
3 4
4 5
*/

/*
2
3
3
*/