#include <stdio.h>

FILE* fp = NULL;

struct node {
	int left;
	int right;
};

struct node tree[1001] = { 0 };
int sum = 0;

int count(int t) {
	int l = 0;
	int r = 0;

	if (t == -1) return 0;

	l = count(tree[t].left);
	r = count(tree[t].right);

	if (tree[t].left != -1) {
		l++;
	}
	if (tree[t].right != -1) {
		r++;
	}
	if (l < r) {
		sum++;
	}
	return l + r;
}


int make_tree(void) {
	int node = 0;
	int i = 0;
	int num = 0;

	fscanf(fp, "%d\n", &node);

	for (i = 0; i < node; i++) {
		fscanf(fp, "%d ", &num);
		fscanf(fp, "%d ", &tree[num].left);	
		fscanf(fp, "%d\n", &tree[num].right);

	}

	count(1);
	return sum;
}


int main(void) {
	int num_d = 0;
	int test_case[1000] = { 0 };
	int i = 0;

	fp = fopen("input.txt", "rt");

	fscanf(fp, "%d\n", &num_d);

	for (i = 1; i <= num_d; i++) {
		struct node tree[1001] = { 0 };
		sum = 0;
		test_case[i] = make_tree();
	}

	for (i = 1; i <= num_d; i++) {
		printf("%d\n", test_case[i]);
	}

	fclose(fp);
	return 0;
}