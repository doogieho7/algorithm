#include <iostream>
#include <fstream>
using namespace std;

//전역 변수
const char *input = "input.txt";
const int MAX = 500;	//원소의 수 max
int a[MAX];				//원소 list
int N;					//수열의 원소의 수

int picked[MAX];
int pcount;

int max_len;

//전역 변수 초기화
void init(void) {
	for (int i = 0; i < MAX; ++i) {
		a[i] = -1;
		picked[i] = -1;
	}

	N = 0;
	pcount = 0;
	max_len = 0;
}

void array_print(void) {
	for (int i = 0; i < pcount; ++i)
		cout << a[picked[i]] << " ";
	cout << endl;
}

//picked에 index들어가 있고 pi
bool strongly_subseq(void) {

	if (pcount == 1)
		return true;
	else {
		for (int i = 0; i < pcount-1; ++i) {
			int left = a[picked[i]];
			int right = a[picked[i+1]];
			
			if (left >= right)
				return false;
		}
	}

	return true;
}

void combi(int n, int r) {
	//기저 조건
	if (r == 0) {
		array_print();	
		bool strongly = strongly_subseq();
		if (strongly) {
			max_len = max(max_len, pcount);
			cout << "strongly_subsequence max len = " << max_len << endl;
		}

		return;
	}

	int smallest = (pcount == 0) ? 0 : picked[pcount-1]+1;

	for (int pos = smallest; pos < N; ++pos) {
		picked[pcount++] = pos;

		combi(n, r-1);

		pcount--;
	}
}

int main(void) {
	ifstream in(input);
	if (!in) {
		cout << "fail to open file" << endl;
		return 0;
	}

	int tcase;
	in >> tcase;

	//temp
	tcase = 1;

	while (tcase-- > 0) {
		init();

		in >> N;

		//read 원소 list
		for (int i = 0; i < N; ++i)
			in >> a[i];

		for (int j = N; j > 0; --j)
	}

	return 0;
}
