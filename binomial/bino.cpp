#include <iostream>

using namespace std;

int bino(int n, int r) {
	if (r == 0 || n == r)	return 1;
	return bino(n-1, r-1) + bino(n-1, r);
}

//memoization 을 이용한 이항 계수의 계산
//ex) bino(n,r) -> cache[n][r]
int cache[30][30];

void cache_init() {
	for (int i = 0; i < 30; ++i)
		for (int j = 0; j < 30; ++j)
			cache[i][j] = -1;
}

int bino2(int n, int r) {
	//기저사례
	if (r == 0 || n == r)	return 1;

	//-1이 아니라면 한번 계산했던 값이니 곧장 반환
	if (cache[n][r] == -1)
		return cache[n][r];

	return cache[n][r] = (bino(n-1, r-1) + bino(n-1, r));
}

int main(void) {
	cout << "bino(4, 2) = " << bino2(4, 2) << endl;
	cout << "bino(8, 4) = " << bino2(8, 4) << endl;

	return 0;
}

