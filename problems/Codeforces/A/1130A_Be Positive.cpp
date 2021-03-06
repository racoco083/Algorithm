/*
 *  시간복잡도 : O(N)
 *
 *  (문제 설명)
 *  N개의 수가 주어지고 -1000<=d<=1000, d!=0인 d가 있다.
 *  N개의 숫자들을 d로 나누었을 때 0을 제외한 양수인 개수가
 *  [N/2]상한과 같거나 더 많으면 이때의 d를 출력한다.
 *  그런데 d는 범위가 크지만 페이크다. -1과 1만 있으면 된다.
 *  왜냐하면 모든 수에 1을 곱하든 1000을 곱하든 양수의 개수는 같기 때문이다.
 *
 *  (풀이)
 *  그냥 모든 수가 d(1또는 -1)로 나누었을 때 
 *  [N/2]상한과 같거나 더 많으면 이때의 d를 출력한다.
 *  
 */

#include <iostream>
#include <algorithm>
using namespace std;
#define MXN 102

double N;
double arr[MXN + 1];
int main() {
	cin >> N;
	int wc = ceil(N / 2.0);
	for (int i = 0; i < N; i++) cin >> arr[i];
	for (double i = -1; i <= 1; i++) {
		if (i == 0) continue;
		int cnt = 0;
		for (int j = 0; j < N; j++) {
			if (arr[j] / i > 0) cnt++;
		}
		if (cnt >= wc) {
			cout << i;
			return 0;
		}
	}
	cout << 0;
	return 0;
}
















































//int N, V;
//
//int main() {
//	cin >> N >> V;
//	int cl = 0;
//	int tm = 0;// total money
//	for (int i = 1; i < N; i++) {
//		if (N - i == cl) break;
//		while (cl < V && N-i>cl) {
//			cl++;
//			tm += i;
//		}
//		cl--;
//	}
//	cout << tm << '\n';
//	return 0;
//}