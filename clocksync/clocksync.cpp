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

//책 코드 start
const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
int clocks[CLOCKS];

//문자열 사용하면 +1 해줘야함.
const char linked[SWITCHES][CLOCKS+1] = {
//0123456789012345
 "xxx.............",	//0
 "...x...x.x.x....",	//1
 "....x.....x...xx",	//2
 "x...xxxx........",	//3
 "......xxx.x.x...",	//4
 "x.x...........xx",	//5
 "...x..........xx",	//6
 "....xx.x......xx",	//7
 ".xxxxx..........",	//8
 "...xxx...x...x.."		//9
};

//전역 변수 초기화 
static void init2() {
	int i;

	for (int i = 0; i < CLOCKS; ++i)
		clocks[i] = 0;

}

//모든 시계가 12시를 가르키고 있는지 확인한다.
bool areAligned(void) {
	bool aligned = true;

	for (int i = 0; i < CLOCKS; ++i) {
		if (clocks[i] != 12) {
			aligned = false;
			break;
		}
	}

	return aligned;
}

//swtch번 스위치를 누른다.
void push(int swtch) {
	for (int clock = 0; clock < CLOCKS; ++clock) {
		if (linked[swtch][clock] == 'x') {
			clocks[clock] += 3;

			if (clocks[clock] == 15)
				clocks[clock] = 3;
		}
	}
}

//swtc: 이번에 누를 스위치의 번호
int solve(int swtch) {
	if (swtch == SWITCHES)
		return areAligned() ? 0 : INF;

	//이 스위치를 0번 누르는 경우부터 세 번 누르는 경우까지를 모두 시도한다.
	int ret = INF;
	for (int cnt = 0; cnt < 4; ++cnt) {
		// 아무거도 안누르는 경우 처리하기 위해서 push() 함수가 뒤에 있음
		ret = min(ret, cnt + solve(swtch + 1));
		push(swtch);
	}

	//push(swtch)가 네번 호출되었으니 clocks는 원래와 같은 상태가 된다.
	return ret;
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
		init2();

		//read times data 
		for (int i = 0; i < CLOCK_COUNT; ++i)
			in >> clocks[i];

		int ret = solve(0);
		if (ret == INF)
			cout << "-1" << endl;
		else
			cout << ret << endl;
	}

	return 0;
}
//책 소스 끝

#if 0
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

		int ret = solve(0);
		if (ret == INF)
			cout << "-1" << endl;
		else
			cout << ret << endl;
	}

	return 0;
}
#endif
