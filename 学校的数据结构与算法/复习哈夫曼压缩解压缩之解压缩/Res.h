#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define HFM_CODE_LEN 10//���ù��������볤��

//�ַ�����
struct Zifu
{
	unsigned char zf;//�ַ�
	unsigned int cnt;//���ִ���
	char code[HFM_CODE_LEN];//��Ӧ�Ĺ���������
	int idx;//�ַ����飨�ֵ䣩�ж�Ӧ�±�
};
//�ֵ�����
struct Zidian
{
	int zf_num;//�ַ�����
	struct Zifu zf_arr[256];//�洢ÿ���ַ�����Ϣ�����256�֣�
};
//���������ڵ�����
struct Node
{
	struct Zifu zf;
	struct Node* pLeft;
	struct Node* pRight;
	struct Node* pParent;
};