#include <iostream>
#include <fstream>
#include <limits>
using namespace std;

const char *input = "input.txt";
const int MAX = 100;
const long long NEGINF = numeric_limits<long long>::min();

//��������
int N, A[MAX];
int M, B[MAX];
//for memoization
//-1 : ����� ���� ����.
int cache[MAX+1][MAX+1];

//�������� �ʱ�ȭ�Ѵ�.
void init(void) {
	N = M = 0;

	for (int i = 0; i < MAX; ++i)
		for (int j = 0; j < MAX; ++j)
			cache[i][j] = -1;
}


//A[indexA] ���� �κ� ����, B[indexB] ���� �κ� ������ ��ģ ������ ���� �� ������ ���̸� ��ȯ
// => JIS
int jlis(int indexA, int indexB) {
	//memoization
	int &ret = cache[indexA+1][indexB+1];
	if (ret != -1)
		return ret;

	//A[indexA], B[indexB]�� �ݵ�� �����ϹǷ� 2���� �׻� �ִ�.
	ret = 2;
	long long a = (indexA == -1) ? NEGINF : A[indexA];
	long long b = (indexB == -1) ? NEGINF : B[indexB];
	int maxEle = max(a, b);

	for (int nextA = indexA + 1; nextA < N; ++nextA) {
		if (maxEle < A[nextA])  {
			ret = max(ret, 1 + jlis(nextA, indexB));
		}
	}

	for (int nextB = indexB + 1; nextB < M; ++nextB) {
		if (maxEle < B[nextB]) {
			ret = max(ret, 1 + jlis(indexA, nextB));
		}
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

		in >> N >> M;

		//read data
		for (int i = 0; i < N; ++i)
			in >> A[i];

		for (int j = 0; j < M; ++j)
			in >> B[j];

		//indexA = -1, indexb = -1 2�� ����.
		cout << jlis(-1, -1) - 2 << endl;
	}

	return 0;
}
