#include <iostream>
#include <fstream>

using namespace std;

const char *input = "input.txt";

#define CLOCK_COUNT			16
#define SWITCH_COUNT		10
#define SWITCH_CLICK_MAX	3

//각 시계의 시간
int times[CLOCK_COUNT];
//각 스위치 누른 횟수
int counts[SWITCH_COUNT];
//각 스위치와 연결되 시계번호 (-1 은 종료)
int switchs[SWITCH_COUNT][5] = {
	{ 0,  1,  2, -1, -1 },	//0
	{ 3,  7,  9, 11, -1 },	//1
	{ 4, 10, 14, 15, -1 },	//2
	{ 0,  4,  5,  6,  7 },	//3
	{ 6,  7,  8, 10, 12 },	//4
	{ 0,  2, 14, 15, -1 },	//5
	{ 3, 14, 15, -1, -1 },	//6
	{ 4,  5,  7, 14, 15 },	//7
	{ 1,  2,  3,  4,  5 },	//8
	{ 3,  4,  5,  9, 13 },	//9
};

//눌러야할 스위치의 최소 수
int switch_click_min;

//전역 변수 초기화 
static void init() {
	int i;

	for (i = 0; i < CLOCK_COUNT; ++i)
		times[i] = 0;

	for (i = 0; i < SWITCH_COUNT; ++i)
		counts[i] = 0;

	switch_click_min = 987654321;
}

//num 스위치와 연결된 시계의 시간을 업데이트 한다.
static void switch_click(int num, int delta) {
	cout << "switch_click: num = " << num << ", delta = " << delta << endl;

	for (int i = 0; i < 5; ++i) {
		if (switchs[num][i] == -1)
			break;

		int time_num = switchs[num][i];

		times[time_num] += delta;
	}
}


static void clocksync_count(int switch_click_cur) {
	bool finish = true;

	//기저조건: 모든 시계의 시간이 12의 배수이면 종료
	for (int i = 0; i < CLOCK_COUNT; ++i) {
		if (times[i] % 12 != 0) {
			finish = false;
			break;
		}
	}

	if (finish) {
		cout << "finish: switch_click_min = " << switch_click_min << ", switch_click_cur = " << switch_click_cur << endl;
		switch_click_min = min(switch_click_min, switch_click_cur);
		return;
	}

	//다음번 스위치 클릭  
	for (int j = 0; j < SWITCH_COUNT; ++j) {
		// 한 스위치는 3번까지 클릭 가능
		if (counts[j] == SWITCH_CLICK_MAX) continue;

		//cout << "counts[" << j << "] = " << counts[j] << endl;

		counts[j]++;
		switch_click(j, 3);

		clocksync_count(switch_click_cur + 1);

		counts[j]--;
		switch_click(j, -3);
	}
}


int main() {
	ifstream in(input);
	if (!in) {
		cout << "fail to open file" << endl;
		return -1;
	}

	int tcase;
	in >> tcase;

	while (tcase-- > 0) {
		init();

		//read times data 
		for (int i = 0; i < CLOCK_COUNT; ++i)
			in >> times[i];

		clocksync_count(0);

		//스위치 눌러야 할 최소 회숫 계산
		if (switch_click_min == 987654321)
			cout << "-1" << endl;
		else
			cout << switch_click_min << endl;
	}

	return 0;
}

