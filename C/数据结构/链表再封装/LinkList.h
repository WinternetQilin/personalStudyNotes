#pragma once
#include<stdint.h>

//������������
typedef int Data;

//�ڵ�
typedef struct Node {
	Data data;
	struct Node* next;
}Node;

//����ṹ
typedef struct LinkList
{
	//ͷ�ڵ�
	Node* front;
	//β�ڵ�
	Node* tail;
	//�ڵ����
	size_t size;

}LinkList;

/**
 * ��������
 * 
 * @return ���ش����ɹ��������ָ��.
 */

//��������
LinkList* CreatLinkList();

//��������
void destoryLinkList(LinkList* list);

//��ͷ����������
void linkList_push_front(LinkList* list, Data val);

//��β����������
void linkList_push_back(LinkList* list, Data val);

//��ָ��Ԫ�غ����������
void linkList_push(LinkList* list, Data after,Data val);

//ͷɾ
void linkList_pop_front(LinkList* list);

//βɾ
void linkList_pop_back(LinkList* list);

//ָ��ɾ
void linkList_pop(LinkList* list,Data val);




