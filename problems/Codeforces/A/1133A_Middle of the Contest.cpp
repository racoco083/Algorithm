/*
 *  시간복잡도 : O(1)
 *
 *  (문제 설명)
 *  입력으로 주어진 두 시간의 중간시간을 출력하라.
 *
 *  (풀이)
 *  코드보면 쉽게 이해간다.
 *  
 */
#include <iostream>
using namespace std;
#define MXN 5

char a[MXN + 1];
char b[MXN + 1];

int calc(char a[]) {
	return ((a[0] - '0') * 10 + (a[1] - '0')) * 60 + (a[3] - '0') * 10 + (a[4] - '0');
}

int main() {
	cin >> a >> b;
	int am = calc(a);
	int bm = calc(b);
	int sum = (am + bm) / 2;

	cout << sum / 600;
	sum %= 600;
	cout << sum / 60<<':';
	sum %= 60;
	cout << sum / 10;
	sum %= 10;
	cout << sum;
	return 0;
}