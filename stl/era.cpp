#include <iostream>
using namespace std;
#define MXN 100

bool chk[MXN];// 인덱스가 소수이면 false, 아니면 true
int prime[MXN];// 소수를 담는다.
int idx;

void era() {
	for (int i = 2; i <= MXN; i++) {
		if (chk[i] == false) {
			prime[idx++] = i;
			// i는 소수가 되고 i의 배수들을 chk값을 true로 바꾸어 준다.
			for (int j = i + i; j <= MXN; j += i) {
				chk[j] = true;
			}
		}
	}
}

int main() {
	idx = 0;
	era();
	for (int i = 0; i < idx; i++) cout << prime[i] << ' ';
	return 0;
}