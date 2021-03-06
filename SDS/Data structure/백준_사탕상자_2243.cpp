/*
 *  BOJ 2243. 사탕상자
 *
 *  시간복잡도 : O(Nlog(10^6))
 *
 *  맛있는 사탕의 순서의 바구니를 단말노드로 하여 인덱스 트리를 구성한다.
 *  a가 2이면 b 순서의 사탕 바구니에 사탕 c개를 담는다. 그리고 update한다.
 *  각 노드는 s~e까지의 사탕의 개수 총합을 갖는다.
 *  a가 1이면 b 번째로 맛있는 사탕을 하나 뽑아낸다. b순서랑은 다르다.
 *  1번째로 맛있는 사탕 바구니에 사탕 100개가 있다면 99번째로 맛있는
 *  사탕은 1번 사탕 바구니에 있는 것이다. 루트부터 시작하여 루트의 
 *  왼쪽 자식의 개수와 오른쪽 자식의 개수를 비교하여 b가 왼쪽 자식의
 *  사탕 개수 보다 크면 오른쪽으로 이동하고 아니면 왼쪽으로 이동하는
 *  것을 반복하여 b번째로 맛있는 사탕의 바구니를 찾는다.
 *  
 */

#include <iostream>
using namespace std;
#define MXN 1000001

int N;
// 노드는 최악의 경우 최대 N*4의 개수가 필요할 수 있다.
int tree[MXN * 4];
int pli;// parent_last_index

void init() {
	pli = 1;
	// while (pli < N)을 해서 틀렸다. 여기서 사탕의 맛은 총 1000000개가 있다.
	// 이 숫자값 만큼의 단말 노드가 필요 했다. 왜냐하면 1000000번째 맛의 바구니에
	// 사탕을 언제든지 넣을 수 있기 때문이다.
	while (pli < 1000000) pli *= 2;
	pli--;
}

// 단말에 추가 된 사탕의 개수 cnt를 증가시켜주고 이 단말 노드를 자손으로 갖는
// 모든 노드에 사탕개수 cnt를 증가시켜 준다.
void update(int idx, int cnt) {
	idx += pli;
	while (idx) {
		tree[idx] += cnt;
		idx /= 2;
	}
}

int get_kth(int kth) {
	int idx = 1;
	// kth로 맛있는 사탕을 찾기 위해 현재 idx의 왼쪽자식의 사탕 개수보다
	// 크면 다음은 오른쪽 자식을 뒤진다. 이때 kth에서 왼쪽 자식의 개수만큼을
	// 빼준다. 예를 들어 왼쪽 자식이 5이고 오른쪽 자식이 3, kth는 7이라고 치자
	// kth가 왼쪽 자식의 사탕 개수보다 많으니 오른쪽 자식을 방문하게 되고
	// 이 때 kth에 왼쪽 자식의 개수 5를 뺀다. 그래서 오른쪽 자식에서 2번째로
	// 맛있는 사탕을 찾으면 된다.
	// while의 조건문을 좀 복잡하게 만들었는데 idx <= pli이렇게만 하면 된다.
	// 이 조건이 만족하여 계속 while을 수행하게 되면 언젠가 단말 노드에 접근하게
	// 되는데 그 뒤로는 수행할 필요가 없기 때문이다.
	while (idx <= pli) {
		if (tree[idx * 2] < kth) {
			kth -= tree[idx * 2];
			idx = idx * 2 + 1;
		}
		else idx = idx * 2;
	}
	// 여기서 update대신 tree[idx]--를 해서 단말노드의 사탕의 개수만 -1 해주는 실수를 했다.
	update(idx - pli, -1);
	return idx - pli;
}

int main() {
	cin >> N;
	init();
	int a, b, c;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		if (a == 1) cout << get_kth(b) << '\n';// b순위의 사탕을 하나 꺼낸다.	
		else {// 넣거나 뺀다.
			cin >> c;
			update(b, c);
		}
	}
	return 0;
}
