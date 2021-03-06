#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX 30000

extern int makeBlock(int module[][4][4]);

template <typename T>
class vector {
public:
	int sz, ca;
	T* arr;
	vector<T>() {
		ca = 16;
		arr = new T[ca];
		sz = 0;
	}
	void push_back(T v) {
		if (sz == ca) {
			ca *= 2;
			T* tmp = new T[ca];
			for (int i = 0; i < sz; i++) tmp[i] = arr[i];
			delete[] arr;
			arr = tmp;
		}
		arr[sz++] = v;
	}
	void pop_back() { sz--; }
	T back() { return arr[sz - 1]; }
	void clear() { sz = 0; }
	bool empty() { return (sz == 0) ? true : false; }
	T &operator[](int idx) { return arr[idx]; }
};

class Vi {
public:
	int v, i;
	Vi(int _v, int _i) : v(_v), i(_i) {}
	Vi() {}
};

Vi vi[MAX + 1], t_vi[MAX + 1]; // value_index
int base[MAX + 1], sv[MAX + 1], t_sv[MAX + 1], diff[MAX + 1], tri[MAX + 1]; // search_value, tri는 3진수
vector<int> mp[MAX + 1]; // map을 해시처럼 사용하기 위한 자료구조

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void merge_vi(int s, int e) {
	if (s >= e) return;
	int m = (e + s) / 2;
	int l = s, r = m + 1, k = l;
	merge_vi(s, m);
	merge_vi(r, e);

	while (l <= m && r <= e) {
		t_vi[k++] = (vi[l].v <= vi[r].v) ? vi[l++] : vi[r++];
	}
	while (l <= m) t_vi[k++] = vi[l++];
	while (r <= e) t_vi[k++] = vi[r++];

	for (int i = s; i <= e; i++) vi[i] = t_vi[i];
}

void merge_sv(int s, int e) {
	if (s >= e) return;
	int m = (e + s) / 2;
	int l = s, r = m + 1, k = l;
	merge_sv(s, m);
	merge_sv(r, e);

	while (l <= m && r <= e) {
		t_sv[k++] = (sv[l] <= sv[r]) ? sv[l++] : sv[r++];
	}
	while (l <= m) t_sv[k++] = sv[l++];
	while (r <= e) t_sv[k++] = sv[r++];

	for (int i = s; i <= e; i++) sv[i] = t_sv[i];
}

int lb(int s, int e, int v) {
	//lower_bound로 해야한다 같은 값이 여러개 존재할 수 있고 그 중에서 제일 인덱스가 작은 값만 계속 리턴해주어야 하기 때문이다.
	while (s<e) {
		int m = (e + s) / 2;
		if (sv[m] < v) s = m + 1;
		else e = m;
	}
	return e;
}

// sv는 여기서만 쓰인다.
int get_idx(int a) {
	int i = lb(0, MAX - 1, a);
	// a가 sv의 값들 보다 클 수 있다. i==MAX를 넣어주어야 한다. 근데 e는 아무리 커도 MAX-1를 리턴하는데 이해가 잘 안가네 필요 없는 것 같다.
	// i==MAX를 쓸 만한 테케가 없나보다 lb에서 e가 리턴될 때도 MAX-1가 값이 같다면 return MAX를 하도록 하면 된다.
	if (i == MAX || sv[i] != a) return -1;
	return i;
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void flip(int mat[4][4]) {
	for (int i = 0; i < 4; i++) {
		swap(mat[i][0], mat[i][3]);
		swap(mat[i][1], mat[i][2]);
	}
}

void rotate(int mat[4][4]) {
	int tmp[4][4];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[j][3 - i] = mat[i][j];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mat[i][j] = tmp[i][j];
}

int makeBlock(int module[][4][4]) {
	for (int i = 0; i < MAX; i++) mp[i].clear();
	bool visited[MAX + 1] = { 0, };

	for (int m = 0; m < MAX; m++) {
		int minV = 10;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				minV = min(minV, module[m][i][j]);
		// main안의 base와 다르게 7,8도 될 수 있다.
		base[m] = minV;
	}
	for (int m = 0; m < MAX; m++) {
		tri[m] = 0;
		diff[m] = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				int c = module[m][i][j] - base[m];
				diff[m] = max(diff[m], c);
				tri[m] = tri[m] * 3 + c;
			}
		}
		vi[m] = Vi(diff[m] + base[m], m);
		sv[m] = tri[m];
	}
	merge_vi(0, MAX - 1);
	merge_sv(0, MAX - 1);
	for (int i = 0; i < MAX; i++) {
		int idx = vi[i].i;
		mp[get_idx(tri[idx])].push_back(idx);
	}

	int ans = 0;
	// 가장 큰 블럭을 선택하고 회전시키면서 대응되는 블럭 중에 가장 큰 것을 구해 
	// 합쳐진 블럭의 길이를 구한다. 여기서 baactree님의 풀이는 대응만 되면 블럭 합 길이를 구하는데
	// 그렇게 하면 가장 큰 블럭 합을 구하지 못 한다. swea의 tc가 엄청 허술하다는 것을 볼 수 있다.
	for (int m = MAX - 1; m >= 0; m--) {
		int idx = vi[m].i;
		if (visited[idx]) continue;
		visited[idx] = true;
		mp[get_idx(tri[idx])].pop_back();
		int t_mat[4][4];
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				t_mat[i][j] = module[idx][i][j];

		flip(t_mat);
		int maxV = -1;
		int maxI = -1;
		int maxM = -1;
		for (int r = 0; r < 4; r++) {
			if (r) rotate(t_mat);
			int c_tri = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					int c = diff[idx] - (t_mat[i][j] - base[idx]);
					c_tri = c_tri * 3 + c;
				}
			}
			int c_idx = get_idx(c_tri);
			if ((c_idx == -1) || mp[c_idx].empty() /*|| visited[c_idx]*/) continue;
			int it = mp[c_idx].back();

			if (maxV < vi[it].v) {
				maxV = vi[it].v;
				maxI = it;
				maxM = c_idx;
			}
		}
		if (maxV != -1) {
			// 한쪽 블럭이 올라온 만큼만 다른쪽 블럭이 올라오므로 diff[idx]를 한 번만 더해주면 된다.
			ans += base[idx] + base[maxI] + diff[idx];
			visited[maxI] = true;
			mp[maxM].pop_back();
		}
	}
	return ans;
}

int main(void) {
	static int module[MAX][4][4];

	srand(3); // 3 will be changed

	for (int tc = 1; tc <= 10; tc++) {
		for (int c = 0; c < MAX; c++) {
			int base = 1 + (rand() % 6);
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					module[c][y][x] = base + (rand() % 3);
				}
			}
		}
		cout << "#" << tc << " " << makeBlock(module) << endl;
	}
	return 0;
}