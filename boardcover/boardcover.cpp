
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#define NUM_MAX		20

#define BLACK 1
#define WHITE 0

#define NUM_BLOCKS	4

int board[NUM_MAX][NUM_MAX];
int width, height;

int blocks[NUM_BLOCKS][2][2] = {
	{
		{ 1, 0 },
		{ 1, 1 },
	},
	{
		{ 0, 1 },
		{ 1, 1 },
	},
	{
		{ 1, 1 },
		{ 0, 1 },
	},
	{
		{ 1, 1 },
		{ 1, 0 },
	},
};


static void init() {
	width = height = 0;

	for (int i = 0; i < height; ++i) 
		for (int j = 0; j < width; ++j) 
			board[i][j] = WHITE;
}

static void board_read(ifstream &in) {
	char buf[NUM_MAX+1];

	for (int i = 0; i < height; ++i) {
		in >> buf;

		//cout << "read data: " << buf << endl;

		for (int j = 0; j < width; ++j) {
			if (buf[j] == '#')
				board[i][j] = BLACK;
		}
	}
}

static bool board_is_full(void) {
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (board[i][j] == WHITE)
				return false;
		}
	}

	return true;
}

static bool block_can_put(int block_num, int y, int x) {
	int (*block)[2] = &blocks[block_num][0];

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (y+i >= height || x+j >= width)
				return false;

			if (block[i][j] == BLACK && board[y+i][x+j] != WHITE)
				return false;
		}
	}

	return true;
}

void board_display() {
#if 1
	for (int i = 0; i < NUM_MAX; ++i) {
		for (int j = 0; j < NUM_MAX; ++j) {
			if (board[i][j] == BLACK)
				cout << '#';
			else
				cout << '.';
		}
		cout << endl;
	}
#endif
}

void block_display(int block_num) {
#if 1
	int (*block)[2] = &blocks[block_num][0];

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (block[i][j] == 1)
				cout << 'X';
			else
				cout << '.';
		}
		cout << endl;
	}
#endif
}

static void block_put(int block_num, int y, int x) {
	int (*block)[2] = &blocks[block_num][0];

	for (int i = 0; i < 2; ++i) { 
		for (int j = 0; j < 2; ++j) {
			if (block[i][j] == BLACK) {
				assert(board[y+i][x+j] == WHITE);

				board[y+i][x+j] = BLACK;
			}
		}
	}
}

static void block_reset(int block_num, int y, int x) {
	int (*block)[2] = &blocks[block_num][0];

	for (int i = 0; i < 2; ++i) { 
		for (int j = 0; j < 2; ++j) {
			if (block[i][j] == BLACK) {
				assert(board[y+i][x+j] == BLACK);

				board[y+i][x+j] = WHITE; 
			}
		}
	}

}


int boardcover_count() {
	/*board가 꽉차면 다 block을 모두 놓았다 */
	if (board_is_full()) {
		cout << "board is full" << endl;
		return 1;
	}

	int ret = 0;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {

			for (int block_num = 0; block_num < NUM_BLOCKS; ++block_num) {
				if (block_can_put(block_num, y, x)) {
					block_display(block_num);

					block_put(block_num, y, x);

					//cout << "after block_put:" << endl;
					board_display();
					
					ret += boardcover_count();

					block_reset(block_num, y, x);

					//cout << "after block_reset:" << endl;
					board_display();
				}
			}
		}
	}

	return ret;
}

int main(void) {
	const char *input = "input.txt";

	ifstream in(input);
	if (!in) {
		cout << "fail to open file" << endl;
		return -1;
	}

	int tcase;

	in >> tcase;
	cout << "test case = " << tcase << endl;

	while (tcase > 0) {
		init();

		in >> height >> width;
		cout << "height = " << height << ", width = " << width << endl;
	    board_read(in);	

		board_display();

		cout << boardcover_count() << endl;

		tcase--;
	}

	return 0;
}





		



