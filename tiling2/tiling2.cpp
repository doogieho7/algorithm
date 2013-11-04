#include <iostream>
#include <fstream>
using namespace std;

const char *input = "input.txt";
const int MOD = 1000000007;
const int MAX = 100;

//전역변수
int N;
int cache[MAX+1];

void init(void) {
	N = 0;

	for (int i = 0; i < MAX+1; ++i)
		cache[i] = -1;
}

//2*width 크기의 사각형을 채우는 방법의 수를 MOD로 나눈 나머지를 반환한다.
int tiling(int width) {
	//기저사례: width가 1 이하일 때
	if (width <= 1)
		return 1;
	
	//메모이제이션
	int &ret = cache[width];
	if (ret != -1)
		return ret;

	return ret = (tiling(width-2) + tiling(width-1)) % MOD;
}

int main(void) {
	ifstream in(input);
	if (!in) {
		cout << "fail to open file" << endl;
		return -1;
	}

	int tcase;
	in >> tcase;

	while (tcase-- > 0) {
		init();		//전역변수 초기화

		in >> N;

		cout << tiling(N) << endl;
	}

	return 0;
}


