#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>

/*
ѧ������ϵͳ��
	�����������
		ѧ��(long long int)
		����(char[11])
		�Ա�(char[3])
		����(int)
		ѧ�Ų����ظ����������ظ�
	�洢�ṹ��
		��ͷ��β��˫�������������
		ͷ�ڵ����� ѧ�� ��һ������ȥ��¼��Ч���ݽڵ�ĸ���
	��Ҫ���ܣ�
		1.����ѧ��
			1.1β��
				�ڱ����ĩβ����ѧ��
			1.2����ָ��ѧ�ź���
				���뵽ָ�����Ѵ��ڵ�ѧ�ź���һλ�������������û���������ѧ��
			1.3����ָ����������
				������������ѧ����������������û�ѡ����뵽˭�ĺ���
		2.ɾ��ѧ��
			2.1βɾ
				ɾ�������ĩβ��ѧ��
			2.2����ѧ��ɾ��ѧ��
				ɾ��ָ�����Ѵ��ڵ�ѧ���������������û���������ѧ��
			2.3��������ɾ��ѧ��
				������������ѧ����������������û�ѡ��ɾ��˭
		3.�޸�ѧ��
			3.1����ѧ���޸�ѧ����Ϣ
				�޸�ָ�����Ѵ��ڵ�ѧ���������������û���������ѧ��
			3.2���������޸�ѧ����Ϣ
				������������ѧ����������������û�ѡ���޸�˭
				����ѡ������������������޸�
		4.��ѯѧ��
			4.1����ѧ�Ų�ѯѧ����Ϣ
				�޸�ָ�����Ѵ��ڵ�ѧ���������������û���������ѧ��
			4.2����������ѯѧ����Ϣ
				������������ѧ�����������
		5.�ļ��洢
			��������ʱ�ڳ�ʼ���ж�ȡ�����ļ� stuInfo.txt �е����ݵ�����
			�˳�ʱ���������ݴ洢�������ļ� stuInfo.txt ��
*/

//ѧ���Ľṹ����
struct student
{
	long long int ID;		//ѧ��
	char name[11];			//����
	char gender[3];			//�Ա�
	int age;				//����
};

//��ѧ���Ľڵ�����
struct node {
	struct student stu;
	struct node* pNext;
	struct node* pParent;
};

//��ѧ������������
struct list {
	//ͷ�ڵ�
	struct node* pHead;
	//β�ڵ�
	struct node* tail;
};

//�����սڵ�
struct node* createNodeNULL();

//�����ڵ�
struct node* createNode(long long int ID, char* name, char* gender, int age);

//������������
struct list* createList();

//��ʼ�������ļ�������
void initList(struct list* l);

//ѧ���������˵�
void stuMainMenu(struct list* list);

//ѧ����Ӳ˵�
void stuInsertMenu(struct list* list);

//ѧ��ɾ���˵�
void stuDelMenu(struct list* list);

//ѧ���޸Ĳ˵�
void stuModifyMenu(struct list* list);

//ѧ����ѯ�˵�
void stuSearchMenu(struct list* list);

//β��
void push(struct list* l, struct node* n);

//����ѧ���м��
void midInsertByID(struct list* l, struct node* n, long long int ID);

//���������м�壨���������Ĭ�ϲ��ڵ�һ���ĺ��棩
void midInsertByName(struct list* l, struct node* n, char* name);

//����
void travel(struct list* l);

//����ѧ�ű���(�����±�)
struct node* travelByID(struct list* l, long long int _ID);

//�������������������±꣩
struct node* travelByName(struct list* l, char* _name);

//βɾ
void pop(struct list* l);

//����ѧ��ɾ��ѧ��
void delStuByID(struct list* l, long long int ID);

//��������ɾ��ѧ��
void delStuByName(struct list* l, char* name);

//����ѧ���޸�ѧ����Ϣ
void modifyByID(struct list* l, long long int ID);

//���������޸�ѧ����Ϣ
void modifyByName(struct list* l, char* name);

//�ļ�����
//�˳�ϵͳ��ʱ�򱣴浽�����ļ� stuInfo.txt ��
void saveToFile(struct list* l);

//�˳�ǰ����˳���
void destory(struct list* l);

int main() {
	//��������(˳����list->pHead->stu.ID�洢Ŀǰ���еĽڵ�������������ͷ�ڵ�)
	struct list* list = createList();
	//��ʼ������
	initList(list);
	//������
	while (true)
	{
		stuMainMenu(list);
	}
	return 0;
}

//�����սڵ�
struct node* createNodeNULL()
{
	struct node* pNew = malloc(sizeof(struct node));
	while (NULL == pNew) {
		pNew = malloc(sizeof(struct node));
	}
	//ȫ����ֵ
	memset(pNew, 0, sizeof(struct node));
	return pNew;
}

//�����ڵ�
struct node* createNode(long long int _ID, char* _name, char* _gender, int _age)
{
	struct node* pNew = malloc(sizeof(struct node));
	while (NULL == pNew) {
		pNew = malloc(sizeof(struct node));
	}
	//��ֵ
	pNew->stu.ID = _ID;
	strcpy(pNew->stu.name, _name);
	strcpy(pNew->stu.gender, _gender);
	pNew->stu.age = _age;
	//ָ��ָ��շ�ָֹ����ֵĵط�
	pNew->pNext = NULL;
	pNew->pParent = NULL;
	//���س�ȥ
	return pNew;
}

//������������
struct list* createList()
{
	struct list* pNew = malloc(sizeof(struct list));
	pNew->pHead = createNodeNULL();
	//β�ڵ�ָ����ĩβ�Ľڵ�
	pNew->tail = pNew->pHead;
	return pNew;
}

//��ʼ�������ļ�������
void initList(struct list* l)
{
	//�������ļ� stuInfo.txt ���ѧ����Ϣ����˳���
	FILE* fp = fopen("stuInfo.txt", "r+");
	while (NULL == fp)
	{
		printf("�ļ���ʧ�ܣ���������...\n");
		fp = fopen("stuInfo.txt", "w+");
	}
	struct node* n = createNodeNULL();
	while (EOF != fscanf(fp, "%lld %s %s %d", &n->stu.ID, n->stu.name, n->stu.gender, &n->stu.age)) {
		push(l, n);
		n = createNodeNULL();
	}
	//�ر��ļ�
	fclose(fp);
}

//ѧ���������˵�
void stuMainMenu(struct list* l)
{
	//�˵�ѡ��
	int select;
	system("cls");
	printf("========================  ѧ������ϵͳ  ========================\n");
	printf("\t\t -------------------------------\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          1.ѧ�����           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          2.ѧ��ɾ��           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          3.ѧ���޸�           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          4.ѧ����ѯ           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          5.ȫ��ѧ��           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t|          0.�����˳�           |\n");
	printf("\t\t|                               |\n");
	printf("\t\t -------------------------------\n");
	printf("\n\t\t���������ѡ��");
	scanf("%d", &select);
	switch (select)
	{
	case 0:
		//�Ƚ�����ı��浽�ļ�
		saveToFile(l);
		//������˳���
		destory(l);
		//����˳�
		exit(0);
		break;
	case 1:
		stuInsertMenu(l);
		break;
	case 2:
		stuDelMenu(l);
		break;
	case 3:
		stuModifyMenu(l);
		break;
	case 4:
		stuSearchMenu(l);
		break;
	case 5:
		travel(l);
		break;
	default:
		printf("����ѡ���������������룡");
		system("pause");
		system("cls");
		break;
	}
}

//ѧ������˵�
void stuInsertMenu(struct list* l)
{
	//Ҫ��ӵ�ѧ����Ϣ
	long long int _ID;
	int _age;
	char _name[11];
	char _gender[3];
	//�ж�ѧ���Ƿ����
	struct node* isExit;
	//ĳѧ��
	long long int selectID;
	//ĳ����
	char selectName[11];
	//Ҫ��ӵ�ѧ���ڵ�
	struct node* n = createNodeNULL();
	//����Ĳ˵�ѡ��
	int select;
	//��ʱ���������������
	int c;
	//���Ʋ˵�ѭ��
	bool isShow = true;
	while (isShow)
	{
		system("cls");
		printf("========================  ѧ������ϵͳ  ========================\n");
		printf("\t\t -------------------------------\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          1.ֱ�����           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          2.��ӵ�ĳѧ�ź���   |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          3.��ӵ�ĳ��������   |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          0.�����ϼ�           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t -------------------------------\n");
		printf("\n\t\t���������ѡ��");
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			isShow = false;
			break;
		case 1:
			printf("���������ѧ����ѧ�ţ����������Ҳ����ظ�����");
			scanf("%lld", &_ID);
			while ((c = getchar()) != '\n' && c != EOF);
			//�ж�Ҫ�����ѧ����û���ظ�
			isExit = travelByID(l, _ID);
			while (NULL != isExit) {
				//���ظ�����������
				printf("�����ѧ���Ѵ��ڣ����������룺");
				scanf("%lld", &_ID);
				while ((c = getchar()) != '\n' && c != EOF);
				isExit = travelByID(l, _ID);
			}
			printf("���������ѧ����������");
			scanf("%s", _name);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("���������ѧ�����Ա�");
			scanf("%2s", _gender);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("���������ѧ�������䣺");
			scanf("%d", &_age);
			//system("pause");
			//printf("%lld %s %s %d\n", _ID, _name, _gender, _age);
			//system("pause");
			n = createNode(_ID, _name, _gender, _age);
			push(l, n);
			printf("��ӳɹ�!\n");
			system("pause");
			break;
		case 2:
			printf("���������ѧ����ѧ�ţ�");
			scanf("%lld", &_ID);
			while ((c = getchar()) != '\n' && c != EOF);
			//�ж�Ҫ�����ѧ����û���ظ�
			isExit = travelByID(l, _ID);
			while (NULL != isExit) {
				//���ظ�����������
				printf("�����ѧ���Ѵ��ڣ����������룺");
				scanf("%lld", &_ID);
				while ((c = getchar()) != '\n' && c != EOF);
				isExit = travelByID(l, _ID);
			}
			printf("���������ѧ����������");
			scanf("%s", _name);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("���������ѧ�����Ա�");
			scanf("%2s", _gender);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("���������ѧ�������䣺");
			scanf("%d", &_age);
			printf("������ĳѧ�ţ�");
			scanf("%lld", &selectID);
			//system("pause");
			//printf("%lld %s %s %d\n", _ID, _name, _gender, _age);
			//system("pause");
			n = createNode(_ID, _name, _gender, _age);
			midInsertByID(l, n, selectID);
			break;
		case 3:
			printf("���������ѧ����ѧ�ţ�");
			scanf("%lld", &_ID);
			while ((c = getchar()) != '\n' && c != EOF);
			//�ж�Ҫ�����ѧ����û���ظ�
			isExit = travelByID(l, _ID);
			while (NULL != isExit) {
				//���ظ�����������
				printf("�����ѧ���Ѵ��ڣ����������룺");
				scanf("%lld", &_ID);
				while ((c = getchar()) != '\n' && c != EOF);
				isExit = travelByID(l, _ID);
			}
			printf("���������ѧ����������");
			scanf("%s", _name);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("���������ѧ�����Ա�");
			scanf("%2s", _gender);
			while ((c = getchar()) != '\n' && c != EOF);
			printf("���������ѧ�������䣺");
			scanf("%d", &_age);
			printf("������ĳѧ����������");
			scanf("%s", selectName);
			n = createNode(_ID, _name, _gender, _age);
			midInsertByName(l, n, selectName);
			break;
		default:
			printf("����ѡ���������������룡\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

//ѧ��ɾ���˵�
void stuDelMenu(struct list* l)
{
	//Ҫɾ��ѧ��
	long long int selectID;
	//Ҫɾ������
	char selectName[11];
	//����Ĳ˵�ѡ��
	int select;
	//���Ʋ˵�ѭ��
	bool isShow = true;
	while (isShow)
	{
		system("cls");
		printf("========================  ѧ������ϵͳ  ========================\n");
		printf("\t\t -------------------------------\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          1.β��ɾ��           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          2.����ѧ��ɾ��       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          3.��������ɾ��       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          0.�����ϼ�           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t -------------------------------\n");
		printf("\n\t\t���������ѡ��");
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			isShow = false;
			break;
		case 1:
			pop(l);
			break;
		case 2:
			printf("������Ҫɾ����ѧ��ѧ�ţ�");
			scanf("%lld", &selectID);
			delStuByID(l, selectID);
			break;
		case 3:
			printf("������Ҫɾ����ѧ��������");
			scanf("%s", selectName);
			delStuByName(l, selectName);
			break;
		default:
			printf("����ѡ���������������룡\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

//ѧ���޸Ĳ˵�
void stuModifyMenu(struct list* l)
{
	//����ѧ���޸�
	long long int selectID;
	//���������޸�
	char selectName[11];
	//����Ĳ˵�ѡ��
	int select;
	//���Ʋ˵�ѭ��
	bool isShow = true;
	while (isShow)
	{
		system("cls");
		printf("========================  ѧ������ϵͳ  ========================\n");
		printf("\t\t -------------------------------\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          1.����ѧ���޸�       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          2.���������޸�       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          0.�����ϼ�           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t -------------------------------\n");
		printf("\n\t\t���������ѡ��");
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			isShow = false;
			break;
		case 1:
			printf("������Ҫ�޸���Ϣ��ѧ��ѧ�ţ�");
			scanf("%lld", &selectID);
			modifyByID(l, selectID);
			break;
		case 2:
			printf("������Ҫ�޸���Ϣ��ѧ��������");
			scanf("%s", selectName);
			modifyByName(l, selectName);
			break;
		default:
			printf("����ѡ���������������룡\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

//ѧ����ѯ�˵�
void stuSearchMenu(struct list* l)
{
	//Ҫ��ѯ��ѧ��
	long long int selectID = 0;
	//Ҫ��ѯ������
	char selectName[11] = { 0 };
	//��ѯѧ���������������ظ�,�������¼
	struct node* sameName[50] = { 0 };
	//����Ĳ˵�ѡ��
	int select;
	//���Ʋ˵�ѭ��
	bool isShow = true;
	while (isShow)
	{
		system("cls");
		printf("========================  ѧ������ϵͳ  ========================\n");
		printf("\t\t -------------------------------\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          1.����ѧ�Ų�ѯ       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          2.����������ѯ       |\n");
		printf("\t\t|                               |\n");
		printf("\t\t|          0.�����ϼ�           |\n");
		printf("\t\t|                               |\n");
		printf("\t\t -------------------------------\n");
		printf("\n\t\t���������ѡ��");
		scanf("%d", &select);
		switch (select)
		{
		case 0:
			isShow = false;
			break;
		case 1:
			printf("\t\t������Ҫ��ѯ��ѧ�ţ�");
			scanf("%lld", &selectID);
			struct node* searched = travelByID(l, selectID);
			while (NULL == searched) {
				printf("\t\t�����ѧ�Ų����ڣ����������루����-2��������");
				scanf("%lld", &selectID);
				if (-2 == selectID) {
					break;
				}
				searched = travelByID(l, selectID);
				printf("\t\t��ѯ��ѧ��Ϊ��%lld����ѧ����Ϣ��\n", searched->stu.ID);
				printf("\t\tѧ      ��    ��    ��   �Ա�   ����  \n");
				printf("\t\t%10lld  %10s   %4s   %4d  \n", searched->stu.ID, searched->stu.name, searched->stu.gender, searched->stu.age);
				system("pause");
			}
			break;
		case 2:
			printf("������Ҫ��ѯ��Ϣ��ѧ��������");
			scanf("%s", selectName);
			//��Ҫ������ͬ���Ķ�Ҫ��ʾ��������������д
			//�жϱ��Ƿ����
			if (NULL == l) {
				printf("�����ڣ�");
				system("pause");
				return;
			}
			//��ʼ����
			int idx = 0;//��¼�ж��ٸ�������
			struct node* pTemp = l->pHead->pNext;
			while (pTemp) {
				if (0 == strcmp(pTemp->stu.name, selectName)) {
					sameName[idx++] = pTemp;
				}
				pTemp = pTemp->pNext;
			}
			//������ɣ���ʼ���
			printf("������ѧ������Ϊ��%s����ѧ����\n", selectName);
			printf("\t\tѧ      ��    ��    ��   �Ա�   ����  \n");
			for (int i = 0; i < idx; i++)
			{
				printf("\t\t%10lld  %10s   %4s   %4d  \n", sameName[i]->stu.ID, sameName[i]->stu.name, sameName[i]->stu.gender, sameName[i]->stu.age);
			}
			printf("\n");
			system("pause");
			break;
		default:
			printf("����ѡ���������������룡\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

//β��
void push(struct list* l, struct node* n)
{ 
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//����β�ڵ��nextָ���½ڵ�
	l->tail->pNext = n;
	//�������µĽڵ��pParentָ��β�ڵ�
	n->pParent = l->tail;
	//����β�ڵ�
	l->tail = n;
	//ͷ�ڵ����+1
	l->pHead->stu.ID++;
}

//����ѧ���м��
void midInsertByID(struct list* l, struct node* n, long long int _ID)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�����ҵ�Ŀ��ѧ��
	struct node* pTemp = travelByID(l, _ID);
	if (NULL == pTemp) {//û�ҵ�
		printf("δ�ҵ�Ŀ��ѧ�ţ�����ʧ�ܣ�\n");
		system("pause");
		return;
	}
	else {//�ҵ���Ŀ��ڵ㣬��ʼ���������
		//���ж��ǲ������һ��
		if (pTemp == l->tail) {
			//����ǣ���ȥβ��
			push(l, n);
		}
		else {//������ǣ�����������
			//�½ڵ�Խ�Ŀ��ڵ����һ��
			n->pNext = pTemp->pNext;
			//Ŀ��ڵ����һ������Ϊ�½ڵ�
			pTemp->pNext = n;
			//�½ڵ�ĸ��ڵ����ΪĿ��ڵ�
			n->pParent = pTemp;
			//�½ڵ����һ���ڵ�ĸ��ڵ����Ϊ�½ڵ㣨�ɵ���ָ��Ŀ��ڵ�ģ�
			n->pNext->pParent = n;
			//����ͷ�ڵ������++
			l->pHead->stu.ID++;
		}
	}
	printf("��ӳɹ�!\n");
	system("pause");
	return;
}

//���������м��
void midInsertByName(struct list* l, struct node* n, char* _name)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//��������Ƿ���ڸ�����
	if (NULL == travelByName(l, _name)) {
		printf("δ�ҵ�Ŀ������������ʧ�ܣ�\n");
		system("pause");
		return;
	}
	else {//Ŀ��ѧ�Ŵ��ڣ�ѭ��������ͬ���Ķ���������
		//׼��һ����ͬ��ѧ��������
		struct node* sameArr[50] = { 0 };
		//�ۼƹ��ж��ٸ�ͬ����
		int idx = 0;
		//��ʼ������¼
		struct node* pTemp = l->pHead->pNext;
		while (pTemp) {
			if (0 == strcmp(pTemp->stu.name, _name)) {
				sameArr[idx++] = pTemp;
			}
			pTemp = pTemp->pNext;
		}
		//����������飬���û�ѡ��
		int select = 0;
		printf("��������Ϊ��%s����ѧ����\n", _name);
		printf("\t\t    ѧ     ��    ��    ��   �Ա�   ����  \n");
		for (int i = 0; i < idx; i++)
		{
			printf("\t\t %d.%10lld  %10s   %4s   %4d  \n", i+1, sameArr[i]->stu.ID, sameArr[i]->stu.name, sameArr[i]->stu.gender, sameArr[i]->stu.age);
		}
		printf("\n");
		printf("��ѡ��Ŀ��ѧ����Ϣ��ţ�");
		scanf("%d", &select);
		select--;
		while (select < 0 || select >= idx) {
			printf("����ķ�Χ�������������룺");
			scanf("%d", &select);
		}
		pTemp = sameArr[select];
		//��ʼ���в�������
		//���ж��ǲ������һ��
		if (pTemp == l->tail) {
			//����ǣ���ȥβ��
			push(l, n);
		}
		else {//������ǣ�����������
			//�½ڵ�Խ�Ŀ��ڵ����һ��
			n->pNext = pTemp->pNext;
			//Ŀ��ڵ����һ������Ϊ�½ڵ�
			pTemp->pNext = n;
			//�½ڵ�ĸ��ڵ����ΪĿ��ڵ�
			n->pParent = pTemp;
			//�½ڵ����һ���ڵ�ĸ��ڵ����Ϊ�½ڵ㣨�ɵ���ָ��Ŀ��ڵ�ģ�
			n->pNext->pParent = n;
			//����ͷ�ڵ������++
			l->pHead->stu.ID++;
		}
	}	
	printf("��ӳɹ�!\n");
	system("pause");
	return;
}

//����
void travel(struct list* l)
{
	system("cls");
	printf("\t\t -------------ȫ��ѧ����Ϣ--------------\n");
	printf("\t\t| ѧ      ��    ��    ��   �Ա�   ���� |\n");
	struct node* pTemp = l->pHead->pNext;
	while (pTemp) {
		printf("\t\t| %10lld  %10s   %4s   %4d |\n", pTemp->stu.ID, pTemp->stu.name, pTemp->stu.gender, pTemp->stu.age);
		pTemp = pTemp->pNext;
	}
	printf("\t\t -----------------����-----------------\n");
	system("pause");
}

//����ѧ�ű���(�ҵ�����Ŀ��ָ�룬�Ҳ�������NULL)
struct node* travelByID(struct list* l, long long int _ID)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//��ʼ����
	struct node* pTemp = l->pHead->pNext;
	while (pTemp) {
		if (_ID == pTemp->stu.ID)return pTemp;
		pTemp = pTemp->pNext;
	}
	//������֮��û�еĻ��ͷ���-1
	return NULL;
}

//������������(�ҵ�����Ŀ��ָ�룬�Ҳ�������NULL)
struct node* travelByName(struct list* l, char* _name)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//��ʼ����
	struct node* pTemp = l->pHead->pNext;
	while (pTemp) {
		if (0 == (strcmp(pTemp->stu.name, _name)))return pTemp;
		pTemp = pTemp->pNext;
	}
	//������֮��û�еĻ��ͷ���-1
	return NULL;
}

//βɾ
void pop(struct list* l)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	if (0 == l->pHead->stu.ID) {
		printf("�����������ݣ��޷�����ɾ����\n");
		system("pause");
		return;
	}
	//��β��Ҫɾ���Ľڵ��¼����
	struct node* delNode = l->tail;
	//����β�ڵ㣬ָ��ǰһ���ڵ�
	l->tail = l->tail->pParent;
	//�µ�β�ڵ�nextָ���ÿ�
	l->tail->pNext = NULL;
	//�ͷ�Ҫɾ���Ľڵ�
	free(delNode);
	//ͷ�ڵ�ļ�����--
	l->pHead->stu.ID--;
	printf("ɾ���ɹ�!\n");
	system("pause");
}

//����ѧ��ɾ��ѧ��
void delStuByID(struct list* l, long long int _ID)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�ҵ�Ҫɾ����ѧ�ŵ��±�
	struct node* pTemp = travelByID(l, _ID);
	if (NULL == pTemp) {//û�ҵ�
		printf("δ�ҵ�ѧ��Ϊ��%lld����ѧ����\n", _ID);
		system("pause");
		return;
	}
	else {//�ҵ���
		//���ж��ǲ������һ��
		if (pTemp == l->tail) {
			//����ǣ���ȥβɾ
			pop(l);
			//Ȼ��ֱ�ӽ���
			return;
		}
		else {//������ǣ�������ɾ��
			//��ɾ�ڵ�ĸ��ڵ��nextָ���ɾ�ڵ��next��������ɾ�ڵ㣩
			pTemp->pParent->pNext = pTemp->pNext;
			//��ɾ�ڵ��next�ڵ�ĸ��ڵ�ָ���ɾ�ڵ�ĸ��ڵ㣨������ɾ�ڵ㣩
			pTemp->pNext->pParent = pTemp->pParent;
			//�ͷ�
			free(pTemp);
			//����ͷ�ڵ������--
			l->pHead->stu.ID--;
		}
	}
	printf("ɾ���ɹ�!\n");
	system("pause");
}

//��������ɾ��ѧ��
void delStuByName(struct list* l, char* _name)
{
	int select = 0;
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�жϴ�ɾѧ���Ƿ����
	if (NULL == travelByName(l, _name)) {//������
		printf("δ�ҵ�����Ϊ��%s����ѧ����\n", _name);
		system("pause");
		return;
	}
	else {//����
		//׼��һ����ͬ��ѧ��������
		struct node* sameArr[50] = { 0 };
		//�ۼƹ��ж��ٸ�ͬ����
		int idx = 0;
		//��ʼ������¼
		struct node* pTemp = l->pHead->pNext;
		while (pTemp) {
			if (0 == strcmp(pTemp->stu.name, _name)) {
				sameArr[idx++] = pTemp;
			}
			pTemp = pTemp->pNext;
		}
		//����������飬���û�ѡ��
		int select = 0;
		printf("��������Ϊ��%s����ѧ����\n", _name);
		printf("\t\t    ѧ     ��    ��    ��   �Ա�   ����  \n");
		for (int i = 0; i < idx; i++)
		{
			printf("\t\t %d.%10lld  %10s   %4s   %4d  \n", i + 1, sameArr[i]->stu.ID, sameArr[i]->stu.name, sameArr[i]->stu.gender, sameArr[i]->stu.age);
		}
		printf("\n");
		printf("��ѡ��Ŀ��ѧ����Ϣ��ţ�");
		scanf("%d", &select);
		select--;
		while (select < 0 || select >= idx) {
			printf("����ķ�Χ�������������룺");
			scanf("%d", &select);
		}
		pTemp = sameArr[select];
		//�ҵ���Ŀ��ڵ�
		//���ж��ǲ������һ��
		if (pTemp == l->tail) {
			//����ǣ���ȥβɾ
			pop(l);
			//Ȼ��ֱ�ӽ���
			return;
		}
		else {//������ǣ�������ɾ��
			//��ɾ�ڵ�ĸ��ڵ��nextָ���ɾ�ڵ��next��������ɾ�ڵ㣩
			pTemp->pParent->pNext = pTemp->pNext;
			//��ɾ�ڵ��next�ڵ�ĸ��ڵ�ָ���ɾ�ڵ�ĸ��ڵ㣨������ɾ�ڵ㣩
			pTemp->pNext->pParent = pTemp->pParent;
			//�ͷ�
			free(pTemp);
			//����ͷ�ڵ������--
			l->pHead->stu.ID--;
		}
	}
	printf("ɾ���ɹ�!\n");
	system("pause");
}

//����ѧ���޸�ѧ����Ϣ
void modifyByID(struct list* l, long long int ID)
{
	//�޸ĺ����Ϣ��ʱ�洢
	long long int _ID = -1;
	char _name[11] = "-1";
	char _gender[3] = "-1";
	int _age = -1;
	//������ջ�����
	int c;
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�ҵ�Ҫ�޸ĵ�ѧ�ŵ��±�
	struct node* modNode = travelByID(l, ID);
	if (NULL == modNode) {
		printf("δ�ҵ�ѧ��Ϊ��%lld����ѧ����", ID);
		return;
	}
	else {
		printf("��ǰѧ�ţ�%lld\n", modNode->stu.ID);
		printf("�������޸ĺ��ѧ�ţ�����-1ȡ���޸ģ���");
		scanf("%lld", &_ID);
		if (-1 == _ID) {
			printf("��ȡ���޸�ѧ�ţ�\n");
		}
		else {
			modNode->stu.ID = _ID;
		}
		printf("��ǰ������%s\n", modNode->stu.name);
		printf("�������޸ĺ������������-1ȡ���޸ģ���");
		scanf("%s", &_name);
		if (0 == (strcmp(_name, "-1"))) {
			printf("��ȡ���޸�������\n");
		}
		else {
			strcpy(modNode->stu.name, _name);
		}
		printf("��ǰ�Ա�%s\n", modNode->stu.gender);
		printf("�������޸ĺ������������-1ȡ���޸ģ���");
		scanf("%2s", &_gender);
		while ((c = getchar()) != '\n' && c != EOF);
		if (0 == (strcmp(_gender, "-1"))) {
			printf("��ȡ���޸��Ա�\n");
		}
		else {
			strcpy(modNode->stu.gender, _gender);
		}
		printf("��ǰ���䣺%d\n", modNode->stu.age);
		printf("�������޸ĺ�����䣨����-1ȡ���޸ģ���");
		scanf("%d", &_age);
		if (-1 == _age) {
			printf("��ȡ���޸����䣡\n");
		}
		else {
			modNode->stu.age = _age;
		}
	}
	printf("�޸����!\n");
	system("pause");
}

//���������޸�ѧ����Ϣ
void modifyByName(struct list* l, char* name)
{
	//�޸ĺ����Ϣ��ʱ�洢
	long long int _ID = -1;
	char _name[11] = "-1";
	char _gender[3] = "-1";
	int _age = -1;
	//������ջ�����
	int c;
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�ж��Ƿ����
	if (NULL == travelByName(l, name)) {//������
		printf("δ�ҵ�����Ϊ��%s����ѧ����", name);
		return;
	}
	else {//����
		//׼��һ����ͬ��ѧ��������
		struct node* sameArr[50] = { 0 };
		//�ۼƹ��ж��ٸ�ͬ����
		int idx = 0;
		//��ʼ������¼
		struct node* modNode = l->pHead->pNext;
		while (modNode) {
			if (0 == strcmp(modNode->stu.name, _name)) {
				sameArr[idx++] = modNode;
			}
			modNode = modNode->pNext;
		}
		//����������飬���û�ѡ��
		int select = 0;
		printf("��������Ϊ��%s����ѧ����\n", _name);
		printf("\t\t    ѧ     ��    ��    ��   �Ա�   ����  \n");
		for (int i = 0; i < idx; i++)
		{
			printf("\t\t %d.%10lld  %10s   %4s   %4d  \n", i + 1, sameArr[i]->stu.ID, sameArr[i]->stu.name, sameArr[i]->stu.gender, sameArr[i]->stu.age);
		}
		printf("\n");
		printf("��ѡ��Ŀ��ѧ����Ϣ��ţ�");
		scanf("%d", &select);
		select--;
		while (select < 0 || select >= idx) {
			printf("����ķ�Χ�������������룺");
			scanf("%d", &select);
		}
		modNode = sameArr[select];
		printf("��ʼ�޸ģ�\n");
		printf("��ǰѧ�ţ�%lld\n", modNode->stu.ID);
		printf("�������޸ĺ��ѧ�ţ�����-1ȡ���޸ģ���");
		scanf("%lld", &_ID);
		if (-1 == _ID) {
			printf("��ȡ���޸�ѧ�ţ�\n");
		}
		else {
			modNode->stu.ID = _ID;
		}
		printf("��ǰ������%s\n", modNode->stu.name);
		printf("�������޸ĺ������������-1ȡ���޸ģ���");
		scanf("%s", &_name);
		if (0 == (strcmp(_name, "-1"))) {
			printf("��ȡ���޸�������\n");
		}
		else {
			strcpy(modNode->stu.name, _name);
		}
		printf("��ǰ�Ա�%s\n", modNode->stu.gender);
		printf("�������޸ĺ������������-1ȡ���޸ģ���");
		scanf("%2s", &_gender);
		while ((c = getchar()) != '\n' && c != EOF);
		if (0 == (strcmp(_gender, "-1"))) {
			printf("��ȡ���޸��Ա�\n");
		}
		else {
			strcpy(modNode->stu.gender, _gender);
		}
		printf("��ǰ���䣺%d\n", modNode->stu.age);
		printf("�������޸ĺ�����䣨����-1ȡ���޸ģ���");
		scanf("%d", &_age);
		if (-1 == _age) {
			printf("��ȡ���޸����䣡\n");
		}
		else {
			modNode->stu.age = _age;
		}
	}
	printf("�޸����!\n");
	system("pause");
}

//�ļ�����
//�˳�ϵͳ��ʱ�򱣴浽�����ļ� stuInfo.txt ��
void saveToFile(struct list* l)
{
	//��д��ģʽ��stuInfo.txt�ļ�
	FILE* fp = fopen("stuInfo.txt", "w+");//�ȴ���Ϊ��������ļ���ľ�����
	//�ж���������û�����ݣ�û�оͲ��ô����ļ���
	if (0 == l->pHead->stu.ID) {
		fclose(fp);
		return;
	}
	while (NULL == fp)
	{
		printf("�ļ���ʧ�ܣ���������...\n");
		fp = fopen("stuInfo.txt", "w+");
	}
	//�����е�����д���ļ�
	struct node* pTemp = l->pHead->pNext;
	while (pTemp) {
		fprintf(fp, "%lld %s %s %d\n", pTemp->stu.ID, pTemp->stu.name, pTemp->stu.gender, pTemp->stu.age);
		pTemp = pTemp->pNext;
	}
	//���ǵùر��ļ�
	fclose(fp);
}

//�˳�ǰ��������
void destory(struct list* l)
{
	if (NULL == l)return;
	if (0 == l->pHead->stu.ID) {
		//û����Ч���ݣ���ͷ�ڵ��������ڴ��ͷž�����
		free(l->pHead);
		free(l);
		return;
	}
	//ѭ�������ͷŽڵ�
	struct node* pTemp = l->tail;
	struct node* delNode;//Ҫɾ���Ľڵ�
	while (pTemp) {
		delNode = pTemp;
		pTemp = pTemp->pParent;//��β��ǰ��
		free(delNode);
		delNode = NULL;//��ָֹ����ֵĵط�
	}
	//�ͷ�����
	free(l);
}
//code by zmq