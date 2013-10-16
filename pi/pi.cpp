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

//전역변수 초기화
void init(void) {
	M = 0;
	//N = 0;
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

		cout << pi() << endl;
	}

	return 0;
}
