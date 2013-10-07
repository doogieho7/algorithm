
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

int solve(int left, int right) {
	//기저사례 : 판자가 하나밖에 없는 경우
	if (left == right)	return h[left];

	//[left, mid], [mid+1, right]의 두 구간으로 문제를 분할한다.
	int mid = (left + right) / 2;

	//분할한 문제를 각개 격파
	int sleft = solve(left, mid);
	int sright = solve(mid+1, right);
	int ret = max(sleft, sright);

	cout << "solve(" << left << ", " << mid << ") = " << sleft;
	cout << ", solve(" << mid+1 << ", " << right << ") = " << sright << endl;
	cout << "max = " << ret << endl;

	//분할 문제 3: 두 부분에 모두 걸치는 사각형 중 가장 큰 것을 찾는다.
	int lo = mid, hi = mid+1;
	int height = min(h[lo], h[hi]);

	//[mid, mid+1]만 포함하는 너비 2인 사각형을 고려한다.
	ret = max(ret, height * 2);

	//사각형이 입력 전체를 덮을 때까지 확장해 나간다.
	while (left < lo || hi < right) {
		//항상 높이가 더 높은 쪽으로 확장한다.
		if (hi < right && (lo == left || h[lo-1] < h[hi+1])) {
			++hi;
			height = min(height, h[hi]);
		}
		else {
			--lo;
			height = min(height, h[lo]);
		}

		//확장한 후 사각형의 넓이
		ret = max(ret, height * (hi - lo + 1));
	}

	cout << "after intersection(" << left << ", " << right << ") ret = " << ret << endl;

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

		cout << solve(0, n-1) << endl;
	}


	return 0;
}

