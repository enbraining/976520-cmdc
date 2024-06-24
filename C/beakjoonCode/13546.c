#include <stdio.h>

#define MAX (100000 + 100)
#define SQRT (316)
#define SIZE (MAX / SQRT + 1)

int N, K, M;
int A[MAX];

int maxLength[MAX + 1000];
int maxLengthBucket[SIZE];
int answer[MAX];

typedef struct st1 {
	int index;
	int left;
	int right;
} QUERY;

QUERY query[MAX];
#pragma region merge sort
QUERY b[MAX];

int isMin(QUERY a, QUERY b) {
	if (a.left / SQRT < b.left / SQRT) return 1;
	else if (a.left / SQRT == b.left / SQRT && a.right < b.right) return 1;

	return 0;
}

void merge(QUERY* a, int start, int end) {
	int mid, i, j, k;

	mid = (start + end) >> 1;
	i = start;
	j = mid + 1;
	k = 0;

	while (i <= mid && j <= end) {
		if (isMin(a[i], a[j])) b[k++] = a[i++];
		else b[k++] = a[j++];
	}

	while (i <= mid) b[k++] = a[i++];
	while (j <= end) b[k++] = a[j++];

	for (i = start; i <= end; i++)
		a[i] = b[i - start];
}

void sort(QUERY* a, int start, int end) {
	int mid;
	if (start >= end) return;

	mid = (start + end) >> 1;
	sort(a, start, mid);
	sort(a, mid + 1, end);
	merge(a, start, end);
}
#pragma endregion

#pragma region deque
typedef struct st2 {
	int value;
	struct st2* next;
	struct st2* prev;
}DEQUE;

DEQUE deque[MAX];
DEQUE* front[MAX];
DEQUE* back[MAX];
DEQUE POOL[MAX * 10];
int pcnt;

int dequeSize[MAX];

void push_front(int head, int value) {
	dequeSize[head]++;

	DEQUE* node;
	if (front[head]->prev == NULL) node = &POOL[pcnt++];
	else node = front[head]->prev;

	node->value = value;

	node->next = front[head];
	front[head]->prev = node;

	front[head] = node;
}

void push_back(int head, int value) {
	dequeSize[head]++;

	DEQUE* node;
	if (back[head]->next == NULL) node = &POOL[pcnt++];
	else node = back[head]->next;

	back[head]->value = value;

	node->prev = back[head];
	back[head]->next = node;

	back[head] = node;
}

int pop_front(int head) {
	dequeSize[head]--;

	int ret = front[head]->value;

	front[head] = front[head]->next;

	return ret;
}

int pop_back(int head) {
	//if (dequeSize[head] == 0) return -1;

	dequeSize[head]--;

	int ret = back[head]->prev->value;

	back[head] = back[head]->prev;

	return ret;
}

#pragma endregion

void leftPop(int left) {
	int length;
	int head = A[left];

	length = back[head]->prev->value - front[head]->value;
	maxLength[length]--;
	maxLengthBucket[length / SQRT]--;

	pop_front(head);

	if (dequeSize[head] != 0) {
		length = back[head]->prev->value - front[head]->value;
		maxLength[length]++;
		maxLengthBucket[length / SQRT]++;
	}
}

void leftPush(int left) {
	int length;
	int head = A[left];

	if (dequeSize[head] != 0) {
		length = back[head]->prev->value - front[head]->value;
		maxLength[length]--;
		maxLengthBucket[length / SQRT]--;
	}

	push_front(head, left);

	length = back[head]->prev->value - front[head]->value;
	maxLength[length]++;
	maxLengthBucket[length / SQRT]++;
}

void rightPush(int right) {
	int length;
	int head = A[right];

	if (dequeSize[head] != 0) {
		length = back[head]->prev->value - front[head]->value;
		maxLength[length]--;
		maxLengthBucket[length / SQRT]--;
	}

	push_back(head, right);

	length = back[head]->prev->value - front[head]->value;
	maxLength[length]++;
	maxLengthBucket[length / SQRT]++;
}

void rightPop(int right) {
	int length;
	int head = A[right];

	length = back[head]->prev->value - front[head]->value;
	maxLength[length]--;
	maxLengthBucket[length / SQRT]--;

	pop_back(head);

	if (dequeSize[head] != 0) {
		length = back[head]->prev->value - front[head]->value;
		maxLength[length]++;
		maxLengthBucket[length / SQRT]++;
	}
}

int findMaxLength() {
	for (int i = SIZE - 1; i >= 0; i--) {
		if (maxLengthBucket[i] == 0) {
			continue;
		}

		for (int k = SQRT - 1; k >= 0; k--) {

			if (maxLength[i * SQRT + k] > 0) {
				return i * SQRT + k;
			}
		}
	}

	return 0;
}

int main() {
	for (int i = 0; i < MAX; i++) {
		front[i] = back[i] = &deque[i];
	}

	scanf("%d %d", &N, &K);

	for (int i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
	}

	scanf("%d", &M);

	for (int i = 0; i < M; i++) {
		int left, right;

		scanf("%d %d", &left, &right);

		query[i].index = i;
		query[i].left = left;
		query[i].right = right;
	}

	sort(query, 0, M - 1);

	int left, right;

	left = right = query[0].left;
	leftPush(left);

	for (int i = 0; i < M; i++) {
		while (right < query[i].right) rightPush(++right);
		while (left > query[i].left) leftPush(--left);

		while (right > query[i].right) rightPop(right--);
		while (left < query[i].left) leftPop(left++);

		answer[query[i].index] = findMaxLength();
	}

	for (int i = 0; i < M; i++) printf("%d\n", answer[i]);

	return 0;
}
