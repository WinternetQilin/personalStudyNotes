#pragma once
#include"res.h"
typedef struct myStack
{
	struct myPoint* pBuff;
	int len;
	int maxlen;
}myStack;

//��ʼ��ջ
void init(struct myStack* s);

//��ջ
void push(struct myStack* s, struct myPoint* p);

//��ջ
void pop(struct myStack* s);

//��ȡջ��
struct myPoint* getTop(struct myStack* s);

//�ж�ջ�Ƿ�Ϊ��
bool isEmpty(struct myStack* s);

