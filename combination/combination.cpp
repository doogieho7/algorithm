
// 1 ~ 10까지 순서상관 없이 5개 뽑을 수 있는 경우의 수
// => 조합 (combination) 문제
#include <iostream>
using namespace std;

#define MAX	1000

//조합
//	공식  
//	nCr = n!/r!(n-r)! = nC(n-r)
//	 => 경우의 수을 계산하는 방법은 위 공식으로 바로 계산 가능하다.
//
//	점화식
//	nCr = n-1Cr-1 + n-1Cr
//	nC0 = 1
//
//	 : 예를들어, 0, 1, 2, 3 4개의 숫자에서, 3개의 숫자을 뽑는 경우의 수를 고려해보면,
//		1) 3을 포함한 경우 : 나머지 0, 1, 2 에서 2개 뽑음 => 3C2
//		2) 3을 포함하지 않는 경우 : 나머지 0, 1, 2 에서 3개 뽑음 => 3C3
//		=> 4C3 = 3C2 + 3C3

int values[MAX];
int vcount;
int picked[MAX];	//values[] index을 저장한다.
int pcount;

void init() {
	vcount = 0;
	pcount = 0;
}

void print_picked() {
#if 0
	for (int j = 0 ; j < pcount; ++j) 
		cout << "picked: " << picked[j] << " ";
	cout << endl;
#endif
	for (int i = 0 ; i < pcount; ++i) 
		cout << values[picked[i]] << " ";
	cout << endl;
}

//1. 재귀로 그냥 구현
int combination(int n, int r) {
	//cout << "combination(" << n << ", " << r << ")" << endl;
	if (r == 0) {
		print_picked();
		return 1;
	}

	int smallest = (pcount == 0) ? 0 : picked[pcount-1] + 1;
	//cout << "smallest = " << smallest << endl;

	int ret = 0;
	for (int i = smallest; i < n; ++i) {
		picked[pcount++] = i;

		ret += combination(n, r-1);

		--pcount;
	}

	return ret;
}

//2, 점화식 구현
int combi(int n, int r) {
	int ret = 0;

	//cout << "combi(" << n << ", " << r << ")" << endl;
	
	//기저조건1 : r == 0
	if (r == 0) {
		print_picked();
		return 1; 
	}
	//기저조건2 : n < r
	else if (n < r) {
		return 0;
	}
	else {
		// 3을 선택하는 경우
		picked[pcount++] = vcount - n;
		ret += combi(n-1, r-1);
		pcount--;

		ret += combi(n-1, r);
	}

	return ret;
}


int main(void) {

	init();

	vcount = 4;
	for (int i = 0; i < vcount; ++i) 
		values[i] = i+1;

	int count = combination(vcount, 3);
	cout << "total combination count = " << count << endl;

	cout << endl;

	pcount = 0;

	count = combi(vcount, 3);
	cout << "total combination count = " << count << endl;

	return 0;
}

