#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>

struct myStack {
	int* parr;
	int headIdx;
	int tailIdx;
	int capacity;
};

//��ʼ��
void myStackInit(struct myStack* s) {
	s->capacity = 10;
	s->parr = calloc(s->capacity, sizeof(int));
	s->headIdx = s->tailIdx = 0;
}

//�Ƿ�ջ��
bool isEmpty(struct myStack* s) {
	if (NULL == s) {
		return true;
	}
	if (s->headIdx == s->tailIdx) {
		return true;
	}
	else {
		return false;
	}
}

//ջ��Ԫ�ظ���
int myStackSize(struct myStack* s) {
	return s->tailIdx;
}

//��ջ
void push(struct myStack* s, int data) {
	if (NULL == s)return;
	if (s->tailIdx >= s->capacity) {
		printf("ջ�����޷����룡\n");
		return;
	}
	s->parr[s->tailIdx++] = data;
	printf("����ɹ�\n");
}

//��ջ
void pop(struct myStack* s) {
	if (NULL == s)return;
	if (isEmpty(s)) {
		printf("ջ�գ��޷�ɾ����\n");
		return;
	}
	s->tailIdx--;
}

//����ջ
void travel(struct myStack* s) {
	if (NULL == s)return;
	if (isEmpty(s)) {
		printf("ջ�գ�\n");
		return;
	}
	for (int i = 0; i < s->tailIdx; i++)
	{
		printf("%d ", s->parr[i]);
	}
	printf("\n");
}

//����ջ��Ԫ������
int myStackTop(struct myStack* s) {
	if (NULL == s)return;
	if (isEmpty(s)) {
		printf("ջ�գ�\n");
		return;
	}
	return s->parr[s->tailIdx - 1];
}

//����ջ
void myStackDestory(struct myStack* s) {
	free(s->parr);
	free(s);
}

int main() {
	struct myStack* ms = malloc(sizeof(struct myStack));
	myStackInit(ms);
	travel(ms);
	push(ms, 1);
	push(ms, 1);
	push(ms, 4);
	push(ms, 5);
	push(ms, 1);
	push(ms, 4);
	push(ms, 1);
	push(ms, 3);
	push(ms, 1);
	push(ms, 4);
	push(ms, 5);
	push(ms, 2);
	push(ms, 1);
	printf("��ǰջԪ�ظ�����%d\n", myStackSize(ms));
	printf("��ǰջ��Ԫ�����ݣ�%d\n", myStackTop(ms));
	travel(ms);
	for (int i = 0; i < 12; i++)
	{
		pop(ms);
		printf("��ǰջԪ�ظ�����%d\n", myStackSize(ms));
	}
	myStackDestory(ms);
	return 0;
}