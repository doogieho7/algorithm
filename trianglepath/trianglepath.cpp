#include <iostream>
#include <fstream>
using namespace std;

//��������
const char *input = "input.txt";
const char MAX = 100;
int board[MAX][MAX];
int cache[MAX][MAX];
int n;
int sum_max;

//�������� �ʱ�ȭ
void init() {
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			board[i][j] = -1;
			cache[i][j] = -1;
		}
	}

	n = 0;
	sum_max = 0;
}

//���� Ž��
int trianglepath(int y, int x, int sum) {
	//cout << "trianglepath(" << y << ", " << x << ")" << endl;
	//���� ����
	if (y >= n || x >= y+1) {
		return sum;
	}

	int value = board[y][x];

	//�Ʒ��� �������� ���
	int sum1 = trianglepath(y+1, x, sum+value);
	//������ �Ʒ��� �������� ���
	int sum2 = trianglepath(y+1, x+1, sum+value);

	return max(sum1, sum2);
}

int trianglepath_memoization(int y, int x) {
	//cout << "trianglepath(" << y << ", " << x << ")" << endl;

	//���� ����1
	if (y >= n || x >= y+1) {
		return 0;
	}

	//���� ����2
	int& ret = cache[y][x];
	if (ret != -1) {
		//cout << "return cache[" << y << "][" << x << "] = " << ret << endl;
		return ret;
	}

	int ret1 = trianglepath_memoization(y+1, x);
	int ret2 = trianglepath_memoization(y+1, x+1);

	ret = (board[y][x] + max(ret1, ret2));
	//cout << "return trianglepath(" << y << ", " << x << ") = " << ret << endl;
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

		in >> n;

		//read triangle data
		for (int y = 0; y < n; ++y)
			for (int x = 0; x < y+1; ++x)
				in >> board[y][x];

		//cout << sum_max << endl;
		//cout << trianglepath(0, 0, 0) << endl;
		cout << trianglepath_memoization(0, 0) << endl;
	}

	return 0;
}
