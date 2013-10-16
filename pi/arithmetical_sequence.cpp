#include <iostream>
using namespace std;

const int MAX = 100;
const int TCASE = 3;
const int testcase[TCASE][MAX] = {
	{ 1, 4, 7 },
	{ 8, 6, 4, 2 },
	{ 8, 6, 4, 1 },
};
const int testcase_size[TCASE] = {
	3,
	4,
	4
};

int *a, N;

void init(void) {
	a = NULL;
	N = 0;
};

//두 숫자가 번갈아 가며 나타나는지 테스트
bool arithmetic_sequence(int start, int size) {
	if (size == 1)
		return true;

	//공비 d이면
	int delta1 = a[0] - a[1];
	
	if (delta1 != (a[start] - a[start+1]))
		return false;
	
	return arithmetic_sequence(start+1, size-1);
}


int main(void) {

	init();

	for (int i = 0; i < TCASE; ++i) {
		a = (int *)&testcase[i][0];
		N = testcase_size[i];

		cout << arithmetic_sequence(0, N) << endl;
	}

	return 0;
}
