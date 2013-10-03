#include <iostream>
#include <fstream>

using namespace std;

#define CITY_MAX	8

const char *input = "input.txt";

//두 도시간의 거리를 저장하는 배열
double dist[CITY_MAX][CITY_MAX];
//각 도시의 방문 유무
bool visited[CITY_MAX];
//지금까지 만든 경로
int path[CITY_MAX];
int path_count;
//현재까지 방문한 도시의 path 길이
double city_pathlen;
//도시수
int city_count;

//전역 변수 초기화
void init() {
	int i, j;

	for (i = 0; i < CITY_MAX; ++i) 
		for (j = 0; j < CITY_MAX; ++j)
			dist[i][j] = 0;

	for (i = 0; i < CITY_MAX; ++i) {
		visited[i] = false;
		path[i] = -1;
	}

	path_count = 0;
	city_pathlen = 0;
	city_count = 0;
}

double shortest_pathlen(int city_num) {
	int i;

	//index 도시을 방문한다
	visited[city_num] = true;

	//city_pathlen 업데이트
	if (path_count > 0)
		city_pathlen += dist[path[path_count-1]][city_num];

	//path에 현재 도시 기록을 한다
	path[path_count++] = city_num;


	//debug
	cout << "visited: " << city_num << ", city_pathlen = " << city_pathlen << endl;

	//기저조건 : 다음 방문할 도시가 없다면 탐색 종료
	bool finished = true;
	for (i = 0; i < city_count; ++i) {
		if (visited[i] == false) {
			finished = false;
			break;
		}
	}

	if (finished) {
		cout << "finished: " << "(" << city_num << ", 0) distance = " << dist[city_num][0] << endl; 

		int ret = city_pathlen + dist[city_num][0];

		visited[city_num] = false;
		path_count--;
		if (path_count > 0)
			city_pathlen -= dist[path[path_count-1]][city_num];

		return ret;
	}

	double shortest= 987654321;

	//나머지 도시에 대해서 shortest_pathlen 구해서 그중 최소값을 선택한다
	for (int j = 0; j < city_count; ++j) {
		if (visited[j] == true)
			continue;

		int pathlen = shortest_pathlen(j);
		cout << "shortest_pathlen(" << j << ") = " << pathlen << endl;

		if (pathlen < shortest)
			shortest = pathlen;
	}

	visited[city_num] = false;
	path_count--;
	if (path_count > 0)
		city_pathlen -= dist[path[path_count-1]][city_num];

	return shortest;
}


double shortestPath(void) {
	//기저 사례: 모든 도시를 다 방문했을 때는 시작도시로 돌아가고 종료한다.
	if (path_count == city_count) {
		return city_pathlen + dist[path[0]][path[path_count-1]];
	}

	double ret = 987654321;	//매우 큰값

	for (int next = 0; next < city_pathlen; ++next)


int main(void) {
	int tcase;

	ifstream in(input);
	if (!in) {
		cout << "fail to open file" << endl;
		return -1;
	}

	in >> tcase;

	while (tcase-- > 0) {
		init();

		in >> city_count;

		// read dist data 
		for (int i = 0; i < city_count; ++i) 
			for (int j = 0; j < city_count; ++j) 
				in >> dist[i][j];
		
		// print shortest path length
		cout << shortest_pathlen(0) << endl;
	}


	return 0;
}

