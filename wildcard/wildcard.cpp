#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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


//전역변수 초기화
void init(void) {
	wlen = 0;
	wild[0] = 0;

	flen = 0;
	filename[0] = 0;

	filename_count = 0;

	list.clear();
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

			bool ret = wildcard(wild, filename);
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

