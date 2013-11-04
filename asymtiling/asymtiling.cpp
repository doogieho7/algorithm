#include <iostream>
#include <fstream>
using namespace std;

const char *input = "input.txt";
const int MOD = 1000000007;
const int MAX = 100;

//전역변수
int N;
int cache[MAX+1];	//memoization
int cache2[MAX+1];

//전역변수 초기화
void init(void) {
	N = 0;

	for (int i = 0; i < MAX+1; ++i) {
		cache[i] = -1;
		cache2[i] = -1;
	}
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

// 전체 tiling 개수 - 대칭 tiling 개수
int asymtiling(int width) {
	if (width % 2 == 1)	//홀수
		return (tiling(width) - tiling(width/2) + MOD) % MOD;

	//width 짝수
	int ret = tiling(width);
	ret = (ret - tiling(width/2) + MOD) % MOD;
	ret = (ret - tiling(width/2-1) + MOD) % MOD;

	return ret;
}

//직접 비대칭 타일링의 수를 세는 방법
//2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymtiling2(int width) {
	//기저사례: 너비가 2 이하인 경우
	if (width <= 2) return 0;

	//메모이제이션
	int &ret = cache2[width];
	if (ret != -1)	return ret;

	ret = asymtiling2(width-2) % MOD;	//A)
	ret = (ret + asymtiling2(width-4)) % MOD;	//B)
	ret = (ret + tiling(width-3)) % MOD;	//C)
	ret = (ret + tiling(width-3)) % MOD;	//D)

	return ret;
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
		init();

		in >> N;

		cout << asymtiling(N) << endl;
		cout << asymtiling2(N) << endl;
	}

	return 0;
}

