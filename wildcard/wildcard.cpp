#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//전역변수
const char *input = "input.txt";
const int MAX = 100;
const int MAX_FILECOUNT = 50;
char wild[MAX+1];
int wlen;
char filename[MAX+1];
int flen;
char filename_list[MAX_FILECOUNT][MAX];
int filename_count;
vector<string> list;
//-1 은 아직 답이 계산되지 않았음을 의미한다.
//1은 해당 입력들이 서로 대응됨을 의미한다.
//0은 해당 입력들이 서로 대응되지 않음을 의미한다.
int cache[MAX+1][MAX+1];
//패턴과 문자열
string W, S;


//전역변수 초기화
void init(void) {
	wlen = 0;
	wild[0] = 0;

	flen = 0;
	filename[0] = 0;

	filename_count = 0;

	list.clear();

	for (int i = 0; i < MAX+1; ++i)
		for (int j = 0; j < MAX+1; ++j)
			cache[i][j] = -1;
}

int _strlen(const char *s) {
	int count = 0;

	while (1) {
		if (s[count++] == '\0')
			break;
	}
	return count - 1;
}

int wildcard(char *w, char *f) {
	//기저조건1.
	if (*w == '\0' && *f == '\0') {
		//cout << "*w = *f = '0'" << endl; 
		return 1;
	}
	else if (*w == '?')
		return wildcard(w+1, f+1);
	else if (*w == '*') {
		char *next = w+1;
		if (*next == '\0')
			return 1;
		else {
			char *fn = f;

			while (*fn != '\0' && *next != *fn) {
				fn++;
			}

			return wildcard(next, fn);
		}
	}
	else if (*w == '\0' || *f == '\0') {
		//cout << "*w = " << *w << ", *f = " << *f << endl;
		return 0;
	}
	else if (*w != *f)
		return 0;
	else {
		// *w == *f
		return wildcard(w+1, f+1);
	}
}

//new implement
int match(char *wildcard, char *str) {
	char *w = wildcard;
	char *s = str;

	cout << "match(" << w << ", " << s << ")" << endl;

	//기저 조건 or special case
	switch (*w) {
		case '\0':
			if (*s == '\0')
				return 1;
			else
				return 0;
		case '?':
			return match(w+1, s+1);
		case '*':
			//next character of wildcard

			while (*(++w) == '*')
				w++;

			cout << "after '*' = " << *w << endl;

			while (*s != '\0') {
				if (match(w, s))
					return 1;
				s++;
			}
	}

	if (*w != *s)
		return 0;

	// 다음 문자 같은지 비교
	return match(w+1, s+1);
}

bool match2(const string& w, const string& s) {
	//w[pos]와 s[pos]를 맞춰나간다.
	int pos = 0;
	while (pos < s.size() && pos < w.size() &&
			(w[pos] == '?' || w[pos] == s[pos]))
		++pos;

	//더이상 대응할 수 없으면 왜 while문이 끝났는지 확인한다.
	//2. 패턴 끝에 도달해서 끝난 경우: 문자열도 끝났어야 대응됨
	if (pos == w.size())
		return pos == s.size();

	//4. *를 만나서 끝난 경우: *에 몇글자를 대응해야 할지 재귀 호출하면서 확인한다.
	if (w[pos] == '*')
		for (int skip = 0; pos+skip <= s.size(); ++skip)
			if (match2(w.substr(pos+1), s.substr(pos+skip)))
				return true;

	//이 외의 경우에는 모두 대응되지 않는다
	return false;
}

//와일드 카드 패턴 W[w..]가 문자열 S[s..]에 대응되는지 여부를 반환한다.
bool matchMemoized(int w, int s) {
	cout << "matchMemoized(" << W.substr(w) << ", " << S.substr(s) << ")" << endl;

	//메모이제이션
	int& ret = cache[w][s];
	if (ret != -1) {
		cout << "after cache[" << w << "][" << s << "] = " << ret << endl;
		return ret;
	}
	
	//ret 가 reference이기 때문에 값을 업데이트 하면 cache[][] 업데이트 된다.

	//W[w], S[s]을 맞춰나간다.
	if (w < W.size() && s < S.size() &&
			(W[w] == '?' || W[w] == S[s]))
		return ret = matchMemoized(w+1, s+1);

	//왜 while문이 끝났는지 확인한다.
	if (w == W.size())
		return ret = (s == S.size());

	//*를 만나서 끝난 경우
	if (W[w] == '*') {
		if (matchMemoized(w+1, s) ||
			(s < S.size() && matchMemoized(w, s+1))) {
			return ret = 1;
		}
	}

	//이 외의 경우에는 모두 대응되지 않는다.
	return ret = 0;
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

		//read wild card
		in >> wild;
		wlen = _strlen(wild);

		//cout << "wildcard = " << wild << endl;
		
		//filename count
		int fcount = 0;
		in >> fcount;

		while (fcount-- > 0) {
			in >> filename;
			flen = _strlen(filename);

			//cout << "filename = " << filename << endl;

			//int ret = wildcard(wild, filename);
			//int ret = match(wild, filename);
			//int ret = match2(string(wild), string(filename));
			W = wild;
			S = filename;
			int ret = matchMemoized(0, 0);
			if (ret)
				list.push_back(filename);
		}

		//cout << "list size = " << list.size() << endl;
		sort(list.begin(), list.end());

		for (vector<string>::iterator iter = list.begin(); iter != list.end(); iter++)
			cout << *iter << endl;
	}

	return 0;
}

