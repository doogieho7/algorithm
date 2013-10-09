#include <iostream>
#include <fstream>
using namespace std;


//전역변수
const char *input = "input.txt";
const int MAX = 100;
int board[MAX][MAX];
int n;

// jumpgame 성공 실패 여부을 캐쉬한다.
// jumpgame(y, x) 
//	ok => cache[y][x] = 1
//	fail => cache[y][x] = 0
//	default value is -1
int cache[MAX][MAX];

//전역변수 초기화
void init(void) {
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			board[i][j] = -1;
			cache[i][j] = -1;
		}
	}

	n = 0;
}

int jumpgame(int y, int x) {
	//cout << "jumpgame(" << y << ", " << x << ") = " << board[y][x] << endl;

	//기저조건
	if (y == n-1 && x == n-1) return 1;
	if (y >= n || x >= n) return 0;

	//memoization
	int &ret = cache[y][x];
	if (ret != -1) return ret;

	int delta = board[y][x];
	return ret = (jumpgame(y, x+delta) || jumpgame(y+delta, x));
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

		/* read data */
		in >> n;

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				in >> board[i][j];

		if (jumpgame(0, 0))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}


	return 0;
}
