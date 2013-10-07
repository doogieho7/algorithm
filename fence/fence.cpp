#include <iostream>
#include <fstream>
using namespace std;

const char *input = "input.txt";

const int HEIGHT_MAX = 20000;
int h[HEIGHT_MAX];
//판자의 수
int n;

//전역변수 초기화
void init() {
	for (int i = 0; i < HEIGHT_MAX; ++i)
		h[i] = 0;

	n = 0;
}

//판자의 높이를 담은 배열 h[]가 주어질 때 사각형의 최대 넓이 반환한다.
int rectangle_extent_max() {
	int ret = 0;

	for (int start = 0; start < n; ++start) {
		int minHeight = h[start];
		/* find min height from start to end */
		for (int end = start; end < n; ++end) {
			minHeight = min(minHeight, h[end]);
			ret = max(ret, (end - start + 1) * minHeight);
		}
	}

	return ret;
}


int main() {
	ifstream in(input);
	if (!in) {
		cout << "fail to open" << endl;
		return 0;
	}

	int tcase;
	in >> tcase;

	while (tcase-- > 0) {
		init();

		in >> n;

		for (int i = 0; i < n; ++i)
			in >> h[i];

		cout << rectangle_extent_max() << endl;
	}


	return 0;
}

