#include <iostream>
#include <fstream>
using namespace std;

const char *input = "input.txt";
const int MOD = 1000000007;
const int MAX = 100;

//��������
int N;
int cache[MAX+1];	//memoization
int cache2[MAX+1];

//�������� �ʱ�ȭ
void init(void) {
	N = 0;

	for (int i = 0; i < MAX+1; ++i) {
		cache[i] = -1;
		cache2[i] = -1;
	}
}

//2*width ũ���� �簢���� ä��� ����� ���� MOD�� ���� �������� ��ȯ�Ѵ�.
int tiling(int width) {
	//�������: width�� 1 ������ ��
	if (width <= 1)
		return 1;
	
	//�޸������̼�
	int &ret = cache[width];
	if (ret != -1)
		return ret;

	return ret = (tiling(width-2) + tiling(width-1)) % MOD;
}

// ��ü tiling ���� - ��Ī tiling ����
int asymtiling(int width) {
	if (width % 2 == 1)	//Ȧ��
		return (tiling(width) - tiling(width/2) + MOD) % MOD;

	//width ¦��
	int ret = tiling(width);
	ret = (ret - tiling(width/2) + MOD) % MOD;
	ret = (ret - tiling(width/2-1) + MOD) % MOD;

	return ret;
}

//���� ���Ī Ÿ�ϸ��� ���� ���� ���
//2*width ũ���� �簢���� ä��� ���Ī ����� ���� ��ȯ�Ѵ�.
int asymtiling2(int width) {
	//�������: �ʺ� 2 ������ ���
	if (width <= 2) return 0;

	//�޸������̼�
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

