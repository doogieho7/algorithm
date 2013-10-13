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
int cache[MAX];

//전역 변수 초기화
void init(void) {
	for (int i = 0; i < MAX; ++i) {
		a[i] = -1;
		picked[i] = -1;
		cache[i] = -1;
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

//책 소스 코드
#include <vector>

int lis(const vector<int>& A) {
	//기저 사례: A가 텅 비어 있을 때
	if (A.empty())
		return 0;

	int ret = 0;
	for (int i = 0; i < A.size(); ++i) {
		vector<int> B;
		for (int j = 0; j < A.size(); ++j) {
			//A[i] 선택, A[i] 보다 큰 수 배열을 만든다.
			if (A[i] < A[j])
				B.push_back(A[j]);
		}

		ret = max(ret, 1 + lis(B));
	}

	return ret;
}

//a[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환
int lis2(int start) {
	//cout << "lis2(" << start << ")" << endl; 

	int& ret = cache[start];
	if (ret != -1) {
		//cout << "return lis2(" << start << ") = " << ret << endl;
		return ret;
	}

	//항상 a[start]는 있기 때문에 길이는 최하 1
	ret = 1;
	for (int next = start+1; next < N; ++next)
		if (a[start] < a[next])
			ret = max(ret, lis2(next) + 1);

	return ret;
}

int main(void) {
	ifstream in(input);
	if (!in) {
		cout << "fail to open file" << endl;
		return 0;
	}

	int tcase;
	in >> tcase;

	while (tcase-- > 0) {
		init();

		in >> N;

		vector<int> A;

		//read 원소 list
		for (int i = 0; i < N; ++i) {
			in >> a[i];

			A.push_back(a[i]);
		}

		//cout << lis(A) << endl;
		cout << lis2(0) << endl;
	}

	return 0;
}
