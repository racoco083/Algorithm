/*
 *  arr[i].fisrt에는 입력으로 들어온 값을 담고 arr[i].second와 ans[i]에는
 *  인덱스 i를 담았다. arr[i].first값에 따라 내림차순이 되는데 각 값의
 *  원래 인덱스를 알기 위해 arr[i].second에 인덱스를 저장했다. 이 값을 통해
 *  원래 인덱스의 달리기 순위를 올릴수 있으면 ans를 통해 원래 순위 보다 앞설수
 *  있으면 그 순위가 되도록 등수를 낮추었다. 투 포인터를 통해 merge의 l인덱스와
 *  r인덱스를 비교해 r이 l보다 크다면 l보다 앞설 수 있으므로 r은 현재 k번째
 *  인덱스에 들어갈 수 있으므로 r-k만큼 해당 r의 등수를 낮추었다. 하지만 
 *  k가 r보다 크다면 등수가 더 뒤로 가므로 이런 건 diff가 -1이 저장되어
 *  무시한다. 이 문제는 자기보다 앞에 있는 숫자중에 자기보다 낮은 숫자의 개수를
 *  찾는 문제로 투 포인터로 풀어야 한다. r이 l보다 앞설 수 있으면 r-l이 되야
 *  하지 않는지 의문이 들 수 있다. 만약 (8 2) (10 7)이라는 숫자가 병합된다고 하면
 *  l=0, r=2, k=0, r이 가리키는 10 값이 l이 가리키는 8값 보다 크므로 10이 k자리에 가고
 *  r값과 k값이 1씩 증가하여 l = 0, r = 3, k = 1이 된다. 8과 7중에서는 8이 크므로 
 *  k값과 l값이 1씩 증가한여 l = 1, r = 3, k = 2이 된다. 2와 7중에는 7이 크니 
 *  7값을 앞에 넣고 2값이 맨 뒤에 들어간다. 7은 2하나만 제쳤는데 r-k는 7이 
 *  몇 개의 숫자를 제쳤는지를 나타낸다. 만약 r-l이 되면 2가 되어 7이 2는 물론
 *  10도 제친 꼴이 된다.
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 500003

typedef pair<int, int> pi;

int N;
pi arr[MXN];
int ans[MXN];
pi tmp[MXN];

void merge(int s, int e) {
	if (e - s < 1) return;
	int m, l, r, k;
	m = (e + s) / 2;
	l = s, r = m + 1, k = l;
	merge(s, m);
	merge(r, e);

	while (l <= m && r <= e) {
		if (arr[l].first >= arr[r].first) tmp[k++] = arr[l++];
		else {
			// diff값은 r번째 사람이 앞에 있는 사람을 제친 개수를 나타낸다.
			int diff = (k < r) ? (r - k) : -1;
			if (diff != -1) ans[arr[r].second] -= diff;
			tmp[k++] = arr[r++];
		}
	}
	while (l <= m) tmp[k++] = arr[l++];
	while (r <= e) tmp[k++] = arr[r++];

	for (int i = s; i <= e; i++) arr[i] = tmp[i];
}

int main() {
	fastio();
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i].first;
		arr[i].second = ans[i] = i;
	}
	merge(0, N - 1);
	
	for (int i = 0; i < N; i++) cout << ans[i] + 1 << '\n';
	return 0;
}