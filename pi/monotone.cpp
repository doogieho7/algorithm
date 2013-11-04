#include <iostream>
using namespace std;

#define ABS(x) ((x) >= 0 ? (x) : -(x))

const int MAX = 100;
const int TCASE = 3;
const int testcase[TCASE][MAX] = {
	{ 2, 3, 4, 5, 6 },
	{ 3, 2, 1, 0 },
	{ 2, 3, 4, 5, 8 }
};
const int testcase_size[TCASE] = {
	5,
	4,
	6
};

int *a, N;

void init(void) {
	a = NULL;
	N = 0;
};

//단조 증가/감소 테스트
bool monotone(int start, int size) {
	//기저 조건
	if (size == 1)
		return true;

	//한번에 2글자만 테스트 한다.
	//|a[start] - a[start+1]| = 1
	if (ABS(a[start]-a[start+1]) != 1)
		return false;

	//a[start+1] 비교
	return monotone(start+1, size-1);
}

int main(void) {

	init();

	for (int i = 0; i < TCASE; ++i) {
		a = (int *)&testcase[i][0];
		N = testcase_size[i];

		cout << monotone(0, N) << endl;
	}

	return 0;
}
