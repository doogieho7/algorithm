#include <iostream>
using namespace std;

const int MAX = 100;
const int TCASE = 3;
const int testcase[TCASE][MAX] = {
	{ 3, 2, 3 },
	{ 5, 4, 5, 4, 5 },
	{ 5, 4, 5, 4, 6 },
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
bool alternate(int start, int size) {
	if (size == 0)
		return true;

	// i : 짝수 a[0]와 같은지 비교
	// i : 홀수 a[1]와 같은지 비교
	if (start % 2 == 0) {
		if (a[0] != a[start])
			return false;
	}
	else {
		if (a[1] != a[start])
			return false;
	}
	
	// 다음 숫자 비교
	return alternate(start+1, size-1);
}


int main(void) {

	init();

	for (int i = 0; i < TCASE; ++i) {
		a = (int *)&testcase[i][0];
		N = testcase_size[i];

		cout << alternate(0, N) << endl;
	}

	return 0;
}
