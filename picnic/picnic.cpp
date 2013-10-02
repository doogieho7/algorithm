
#include <iostream>
#include <fstream>
using namespace std;

#define NUM_MAX		10

static bool areFriends[NUM_MAX][NUM_MAX];
/* 현재 선택된 학생은 taken[i] = true로 설정됨 */
static bool taken[NUM_MAX];
/* 학생 수 */
static int nums = 0;

static void init() {
	int i, j;

	nums = 0;

	for (i = 0; i < NUM_MAX; ++i) 
		for (j = 0; j < NUM_MAX; ++j) 
			areFriends[i][j] = false;

	for (i = 0; i < NUM_MAX; ++i)
		taken[i] = false;
}

static void set_friends(int lhs, int rhs) {
	areFriends[lhs][rhs] = areFriends[rhs][lhs] = true;
}
	

int countPairs(bool taken[NUM_MAX]) {
	static int depth = 0;
	int ret = 0;

	depth++;

	/* 작은 번호의 친구부터 선택 */
	int lowerNum = -1;
	for (int k = 0; k < nums; ++k) {
		if (!taken[k]) {
			lowerNum = k;
			break;
		}
	}
	/* 선택할 친구가 없는 경우 -> pair 완료 */
	if (lowerNum == -1)	{
		ret = 1;
		goto out;
	}

	taken[lowerNum] = true;
	for (int pairNum = lowerNum + 1; pairNum < nums; ++pairNum) {
		if (!taken[pairNum] && areFriends[lowerNum][pairNum]) {
			cout << "(" << lowerNum << ", " << pairNum << ") ";

			taken[pairNum] = true; 
			int count = countPairs(taken);
			ret += count;
			taken[pairNum] = false;

			if (count == 1) 
				cout << endl;

			/* insert space based on depth */
			int spaceCount = depth * 7;
			while(spaceCount--)
				cout << " ";
		}
	}
	taken[lowerNum] = false;

out:
	depth--;
	return ret;
}

int main(void) {
	int tcase;
	int pairs;

	ifstream in("input.txt");
	if (!in) {
		cout << "fail to open file";
		return -1;
	}

	in >> tcase;

	while (tcase > 0) {
		init();

		in >> nums >> pairs;

		/* read friend pairs */
		for (int i = 0; i < pairs; ++i) {
			int lhs, rhs;

			in >> lhs >> rhs;

			set_friends(lhs, rhs);
		}

		int count = countPairs(taken);

		cout << count << endl;

		tcase--;
	}

	return 0;
}
