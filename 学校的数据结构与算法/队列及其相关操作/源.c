#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct myQueue {
	int* parr;
	int headIdx;
	int tailIdx;
	int capacity;
};

//��ʼ��
void initQueue(struct myQueue* q) {
	q->capacity = 10;
	q->parr = malloc(q->capacity * sizeof(int));
	q->headIdx = q->tailIdx = 0;
}

//�����Ƿ�Ϊ��
bool isEmpty(struct myQueue* q) {
	if (NULL == q)return;
	if (q->headIdx == q->tailIdx) {
		return true;
	}
	else {
		return false;
	}
}

//�����е�Ԫ�ظ���
int sizeQueue(struct myQueue* q) {
	if (NULL == q)return;
	return (q->tailIdx - q->headIdx);
}

//���
void push(struct myQueue* q,int data) {
	if (NULL == q)return;
	if (q->tailIdx >= q->capacity) {
		printf("�������޷����룡\n");
		return;
	}
	q->parr[q->tailIdx++] = data;
	printf("����ɹ�\n");
}

//����
void pop(struct myQueue* q) {
	if (NULL == q)return;
	if (isEmpty(q)) {
		printf("�ӿգ��޷�ɾ����\n");
		return;
	}
	q->headIdx++;
}

//����
void travel(struct myQueue* q) {
	if (NULL == q)return;
	if (isEmpty(q)) {
		printf("�ӿգ�\n");
		return;
	}
	for (int i = q->headIdx; i < q->tailIdx; i++)
	{
		printf("%d ", q->parr[i]);
	}
	printf("\n");
}

//����
void destory(struct myQueue* q) {
	if (NULL == q)return;
	free(q->parr);
	free(q);
}

int main() {
	struct myQueue* q = malloc(sizeof(struct myQueue));
	initQueue(q);
	travel(q);
	push(q, 1);
	push(q, 1);
	push(q, 4);
	push(q, 5);
	push(q, 1);
	push(q, 4);
	push(q, 1);
	push(q, 3);
	push(q, 1);
	push(q, 4);
	push(q, 5);
	push(q, 2);
	push(q, 1);
	printf("��ǰջԪ�ظ�����%d\n", sizeQueue(q));
	travel(q);
	for (int i = q->headIdx; i < q->tailIdx; i++)
	{
		pop(q);
		printf("��ǰջԪ�ظ�����%d\n", sizeQueue(q));
		travel(q);
	}
	destory(q);
	return 0;
}