
#include <iostream>
using namespace std;

#define NUM_MAX	20
#define WHITE	0
#define BLACK	1

int board[NUM_MAX][NUM_MAX];
int width, height;


//주어진 칸을 덮을 수 있는 네가지 방법
//블록을 구성하는 세간의 상대적 위치 (dx, dy)의 목록
const int coverType[4][3][2] = {
	{ {0, 0}, {1, 0}, {0, 1} },
	{ {0, 0}, {1, 0}, {1, 1} },
	{ {0, 0}, {0, 1}, {1, 1} },
	{ {0, 0}, {0, 1}, {1, -1} },
};

//board의 (y,x)를 type번 방법으로 덮거나, 덮었던 블록을 없앤다.
//delta=1이면 덮고, -1이면 덮었던 블록을 없앤다
//만약 블록이 제대로 덮이지 않은 경우 (게임판 밖으로 나가거나,
//겹치거나, 검은 칸을 덮을때 false을 반환한다)
bool set(int y, int x, int type, int delta) {
	bool ok = true;

	for (int i = 0; i < 3; ++i) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];

		if (ny < 0 || ny >= width || nx < 0 || nx >= height)
			ok = false;
		else if ((board[ny][nx] += delta) > 1)
			ok = false;
	}

	return ok;
}

//board의 모든 빈 칸을 덮을 수 있는 방법의 수를 반환한다.
//board[i][j] = 1, 이미 덮인 칸 혹은 검은 칸
//board[i][j] = 0, 아직 덮이지 않은 칸
int cover(void) {
	int y, x;

	y = x = -1;

	// 아직 채우지 못한 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다.
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (!board[i][j]) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1)
			break;
	}

	//기저 사례: 모든 칸을 채웠으면 1을 반환한다.
	if (y == -1 && x == -1)
		return 1;

}

