#include <iostream>
#include <string.h>
using namespace std;
#define MXN 23
typedef long long ll;
ll N;

int ans[MXN];
// N(4라고 하자)개의 수가 있다고 하면 각 자리에서 1,2,3,4를 사용했는지 안 했는지 체크
bool used[MXN];
ll fac[MXN];

int main() {
	fac[0] = 1;// 0! = 1이다.
	for (int i = 1; i < MXN; i++) fac[i] = fac[i - 1] * i;
	memset(used, 0, sizeof(used));
	cin >> N;
	int query;
	cin >> query;
	if (query == 1) {
		ll seq;
		cin >> seq;// N순열의 순서번호를 받는다.
		// i는 fac[N-1]~fac[N-N]까지를 차례대로 보기 위해 사용
		for (int i = 1; i <= N; i++) {
			// j는 1~N까지의 숫자를 의미, pno = possible_number_order
			// pno는 가능한 숫자의 순서를 나타내며 3번째 순열은 1,3,2,4이다.
			// 1이 이미 선택되어 있다고 한다면 두 번째 자리는 3이어야 한다.
			// 이때 1은 이미 used이므로 pno를 증가시키면 안 되고,
			// 2는 사용은 할 수 있지만 seq가 3이므로 앞에 1은 선택되었으니 무시하고
			// {2,3,4}, {2,4,3} 이 두 순열은 seq가 1일 때 2일 때이고 3일 때는
			// 2를 선택하면 안 된다. 그걸 체크하는 것이 seq <= pno * fac[N - i]이다.
			// 3 <= 1*fac[2]이므로 이 조건의 if문에 걸리지 않고 pno값을 증가시킨다.
			// 다음은 3 <= 1*fac[2]이므로 조건에 만족하여 ans[2]에 3을 넣고 3은
			// 사용 되었으니 used[3]을 true로 해 주고, 올라간 순서만큼 seq에서 2를 빼주고
			// seq의 남은 값은 다음 i번째 인덱스에서 숫자를 구한 후 또 빼주는 것을 반복한다.
			// 4!이니 첫 번째 수는 1,2,3,4숫자마다 fac[3] = 3! = 6칸씩 차이가 나고
			// 두 번째 수는 숫자마다 fac[2] = 2! = 2칸씩 차이가 난다. 그래서
			// seq -= (pno - 1) * fac[N - i]로 처리가 가능한다.
			for (ll j = 1, pno = 1; j <= N; j++) {
				if (used[j]) continue;
				if (seq <= pno * fac[N - i]) {
					seq -= (pno - 1) * fac[N - i];
					ans[i] = j;
					used[j] = true;
					break;
				}
				pno++;
			}
		}
		for (int i = 1; i <= N; i++) cout << ans[i] << ' ';
	}
	else {
		// 현재 순열이 몇 번째 순열인지를 알아낸다.
		ll ans = 1;
		// 현재 순열의 각 자리의 숫자를 입력 받는다.
		ll num;
		for (int i = 1; i <= N; i++) {
			cin >> num;
			int pno = 0;
			// j의 숫자를 보며 사용되지 않은 숫자의 개수를 구한다.
			// 만약 N이 4라고 하고 맨 앞 숫자가 3이라면 현재의 자리는 ans=1이니까
			// 12를 더해 ans를 13으로 만들어 주어야 한다. 그러기 위해서 fac[3]을
			// pno를 곱한값을 ans에 누적합 시켜주면 되는데 이때 pno는
			// 사용되지 않은 값 중에서 num보다 작은 값의 개수를 구하면 된다.
			// 위와 똑같은 예를 들어 3을 넣는다고 하면 1,2는 다 사용되지 않았다.
			// 그래서 pno는 2가 되고 ans에 fac[3] * 2가 누적되어 13이 된다.
			// 3으로 시작하는 순열의 순번은 13~18로서 옳은 방법인 것을 알 수 있다.
			for (ll j = 1; j < num; j++) 
				if(used[j] == 0) pno++;
			used[num] = true;
			ans += pno * fac[N - i];
		}
		cout << ans << '\n';
	}
	return 0;
}