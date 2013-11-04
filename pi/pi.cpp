#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define ABS(x) ((x) >= 0 ? (x) : -(x))

const char *input = "input.txt";
const int MAX = 10000;
const int INTMAX = 987654321;

//전역변수
int a[MAX];
int b[MAX], M;
char buf[MAX+1];
int cache[MAX+2];

//전역변수 초기화
void init(void) {
	M = 0;

	for (int i = 0; i < MAX+2; ++i)
		cache[i] = -1;
}

//모든 숫자가 같은지 테스트
bool allsame(int start, int size) {
	if (size == 0)
		return true;

	if (a[0] != a[start])
		return false;

	return allsame(start+1, size-1);
}

//단조 증가하거나 단조감소 테스트
bool monotone(int start, int size) {
	//기저 조건
	if (size == 1)
		return true;

	//한번에 2글자만 테스트 한다.
	//|a[start] - a[start+1]| = 1
	if (a[0]-a[1] != a[start]-a[start+1])
		return false;

	//a[start+1] 비교
	return monotone(start+1, size-1);
}

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

bool others(int start, int size) {
	return true;
}

void print_array(int *p, int size) {
	for (int i = 0; i < size; ++i)
		cout << p[i] << " ";
	cout << endl;
}

//input : A[N] (전역변수)
int pi(void) {
	int ret = INTMAX;	//난이도

#define LEVELS 5

	bool (*level_funcs[LEVELS])(int, int) = {
		&allsame,
		&monotone,
		&alternate,
		&arithmetic_sequence,
		&others,
	};

	char *level_funcs_str[LEVELS] = {
		"allsame",
		"monotone",
		"alternate",
		"arithmetic_sequence",
		"others"
	};

	int score[LEVELS] = { 1, 2, 4, 5, 10 };

	for (int step = 3; step <= 5; ++step) {
		//기저조건 - step으로 나눈 나머지가 3이상이여야함
		int remain = M % step;
		if (remain != 0 && remain < 3)
			continue;

		int levels = 0;

		for (int start = 0; start < M; start += step) {
			int count = min(step, M-start);

			//a[] 배열 준비
			memcpy(a, &b[start], count * sizeof(int));
			//print_array(a, count);

			for (int level = 0; level < LEVELS; ++level) {
				//cout << "step = " << step << ", " << level_funcs_str[level] << "(" << start << ", " << count << ")" << endl;
				bool ok = (*level_funcs[level])(0, count);
				if (ok == true) {
					levels += score[level];
					break;
				}
			}
		}

		//cout << "levels = " << levels << endl;

		ret = min(ret, levels);
	}

	return ret;
}

//책 구현
#include <string>
#include <cmath>

string N;

//N[a..b] 구간의 난이도를 반환한다.
int classify(int a, int b) {
	//숫자 조각을 가져온다.
	string M = N.substr(a, b-a+1);

	//1. 첫 글자만으로 이루어진 무자열과 같으면 난이도는 1
	if (M == string(M.size(), M[0]))
		return 1;

	// 등차수열인지 검사한다.
	bool progressive = true;
	for (int i = 0; i < M.size()-1; ++i) {
		if (M[i+1]-M[i] != M[1] - M[0]) {
			progressive = false;
			break;
		}
	}

	// 등차수열이고 공차가 1혹은 -1이면 난이도는 2
	if (progressive == true && abs(M[1]-M[0]) == 1)
		return 2;

	// 두수가 번갈아 등장하는지 확인
	bool alternating = true;
	for (int i = 0; i < M.size()-1; ++i) {
		if (M[i] != M[i%2]) {
			alternating = false;
			break;
		}
	}

	if (alternating) return 4;		//두수가 번갈아 등장하면 난이도는 4
	if (progressive) return 5;		//공차가 1 아닌 등차수열의 난이도는 5

	return 10;
}


//수열 N[begin..]를 외우는 방법 중 난이도의 최소 합을 출력한다.
int memorize(int begin) {
	//기저 사례: 수열의 끝에 도달했을 경우
	if (begin == N.size())
		return 0;

	//memoization
	int &ret = cache[begin];
	if (ret != -1)
		return ret;

	//초기값 - 최대값
	ret = INTMAX;

	for (int L = 3; L <= 5; ++L) 
		if (begin + L <= N.size())
			ret = min(ret, classify(begin, begin+L- 1)
							+ memorize(begin+L));

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

		//read data
		in >> buf;

		int i = 0;
		while (1) {
			if (buf[i] == '\0') 
				break;

			b[i] = (int)(buf[i] - '0');
			i++;
		}
		M = i;

		//cout << pi() << endl;
		
		N = buf;
		cout << memorize(0) << endl;
	}

	return 0;
}
