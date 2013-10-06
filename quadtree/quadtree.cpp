#include <iostream>
#include <fstream>

using namespace std;

#define NODE_CHILDS	4

struct node {
	char value;
	struct node *child[NODE_CHILDS];
};

const char *input = "input.txt";

//전역변수들
#define BUF_MAX	1000
char buf[BUF_MAX];
int buf_index;

//전역변수 초기화
void init(void) {
	buf[0] = 0;
	buf_index = 0;
}

static void make_child(struct node *p) {
	for (int i = 0 ; i < NODE_CHILDS; ++i) {
		struct node *n = new struct node;

		n->value = buf[buf_index++];
		if (n->value == 'x')
			make_child(n);

		p->child[i] = n;
	}
}

// root node을 반환한다.
struct node *make_tree() {
	struct node *root = new struct node;

	root->value = buf[buf_index++];
	if (root->value == 'x') {
		make_child(root);
	}

	return root;
}

void swap(struct node **l, struct node **r) {
	struct node *temp;

	temp = *l;
	*l = *r;
	*r = temp;
}


// quadtree을 상하 반전 시킨다.
void reverse_topbottom(struct node *quadtree) {
	//기저 조건: child 가지지 안으면 return
	if (quadtree->value != 'x')
		return;

	//손으로 해보면 상하 반전은
	// 1 <-> 3, 2<->4 swap 이다.
	swap (&quadtree->child[0], &quadtree->child[2]);
	swap (&quadtree->child[1], &quadtree->child[3]);

	for (int i = 0; i < NODE_CHILDS; ++i) 
		reverse_topbottom(quadtree->child[i]);
}

void print(struct node *quadtree) {
	cout << quadtree->value;

	if (quadtree->value != 'x')
		return;

	for (int i = 0; i < NODE_CHILDS; ++i)
		print(quadtree->child[i]);
}

//책 코드
#include <string>

string _reverse(string::iterator &it) {
	char head = *it;
	it++;

	if (head != 'x') 
		return string(1, head);

	string ll = _reverse(it);
	string lr = _reverse(it);
	string rl = _reverse(it);
	string rr = _reverse(it);

	return string("x") + rl + rr + ll + lr;
}

int main(void) {
	ifstream in(input);
	if (!in) {
		cout << "failt to open" << endl;
		return -1;
	}

	int tcase;
	in >> tcase;

	while (tcase-- > 0) {
		string input;

		in >> input;;

		string::iterator it = input.begin();
		string ret = _reverse(it);
		cout << ret << endl;
	}

	return 0;
}

#if 0
int main(void) {
	ifstream in(input);
	if (!in) {
		cout << "failt to open" << endl;
		return -1;
	}

	int tcase;
	in >> tcase;

	while (tcase-- > 0) {
		init();

		in >> buf;

		struct node *root = make_tree();
		reverse_topbottom(root);

		print(root);
		cout << endl;
	}

	return 0;
}
#endif
