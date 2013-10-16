#include <iostream>
using namespace std;

#define ABS(x) ((x) >= 0 ? (x) : -(x))

const int MAX = 100;
const int TCASE = 3;
const int testcase[TCASE][MAX] = {
	{ 1, 1, 1 },
	{ 2, 2, 2, 2, 1 },
	{ 3, 3, 3, 3, 3 },
};
const int testcase_size[TCASE] = {
	3,
	5,
	5
};

int *a, N;

void init(void) {
	a = NULL;
	N = 0;
};

//두 숫자가 번갈아 가며 나타나는지 테스트
bool allsame(int start, int size) {
	if (size == 0)
		return true;

	if (a[0] != a[start])
		return false;

	return allsame(start+1, size-1);
}


int main(void) {

	init();

	for (int i = 0; i < TCASE; ++i) {
		a = (int *)&testcase[i][0];
		N = testcase_size[i];

		cout << allsame(0, N) << endl;
	}

	return 0;
}
