#pragma once
typedef struct Node
{
	int data;
	struct Node* next;
}Node,List;

//�����ʼ��
void flist_init(List* list);

//��������
void flist_clean(List* list);

//β��
void flist_push(List* list,int val);

//ͷ��
void flist_pop(List* list,int val);

//���м����
void flist_insert(List* list, int after, int val);

//�������ݴ�ӡ
void flist_print(List* list);

//βɾ
void flist_tailDel(List* list);

//ͷɾ
void flist_popDel(List* list);

//ɾ��ָ��Ԫ��
void flist_distDel(List* list,int val);

//��ȡ�����С
int flist_size(List* list);

//�������
int* flist_find(List* list, int val);

//����
void flist_sort(List* list);

//����ת
void flist_reverse(List* list);

