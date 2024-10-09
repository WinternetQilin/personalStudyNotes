#include <stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>

/*
ѧ������ϵͳ��
����ѧ�ţ��������Ա�����,ѧ��
��Ҫ���ܣ�
����ѧ��
	β��
	����ָ��ѧ�ź���
	����ָ����������
	��Ҫ����ѧ����ѧ�ţ��������Ա����䣬ѧ��
		ѧ�ű������벢�Ҳ������ظ�
		�����Ĳ�����͸�Ĭ��ֵ
	ÿ�β�����һ��ѧ���ͽ���һ��ȫ����
ɾ��ѧ��
	βɾ
	����ѧ��ɾ��ѧ��
	��������ɾ��ѧ��
�޸�ѧ��
	����ѧ���޸�ѧ����Ϣ
	���������޸�ѧ����Ϣ
��ѯѧ��
	����ѧ�Ų�ѯѧ����Ϣ
	����������ѯѧ����Ϣ
		������ͬ������һ��չʾ����
�ļ��洢������ stuInfo.txt ��
*/

//����ѧ���ṹ
struct student
{
	long long int ID;		//ѧ��
	char name[11];			//����
	char gender[3];			//�Ա�
	int age;				//����
	double credit;			//ѧ��
};

//������ѧ����˳���
struct stuSqList {
	struct student* parr;
	int curSize;			//�����е�ǰ�Ѿ��洢��ѧ����Ϣ����
	int maxSize;			//������ܴ�С
};

//����ѧ��˳�����
struct stuSqList* createSqList();

//��ʼ��˳�����
void initSqList(struct stuSqList* l);

//����ѧ������
struct student createStu(long long int ID, char* name, char* gender, int age, double credit);

//ѧ����Ӳ˵�
void stuInsertMenu(struct stuSqList* list);

//ѧ��ɾ���˵�
void stuDelMenu(struct stuSqList* list);

//ѧ���޸Ĳ˵�
void stuModifyMenu(struct stuSqList* list);

//ѧ����ѯ�˵�
void stuSearchMenu(struct stuSqList* list);

//β��
void push(struct stuSqList* l, struct student s);

//����ѧ���м��
void midInsertByID(struct stuSqList* l, struct student s, long long int ID);

//���������м�壨���������Ĭ�ϲ��ڵ�һ���ĺ��棩
void midInsertByName(struct stuSqList* l, struct student s, char* name);

//����
void travel(struct stuSqList* list);

//����ѧ�ű���(�����±�)
int travelByID(struct stuSqList* l, long long int ID);

//�������������������±꣩
int travelByName(struct stuSqList* l,char* name);

//βɾ
void pop(struct stuSqList* l);

//����ѧ��ɾ��ѧ��
void delStuByID(struct stuSqList* l, long long int ID);

//��������ɾ��ѧ��
void delStuByName(struct stuSqList* l, char* name);

//����ѧ���޸�ѧ����Ϣ
void modifyByID(struct stuSqList* l, long long int ID);

//���������޸�ѧ����Ϣ
void modifyByName(struct stuSqList* l, char* name);

//����ѧ�ֽ�����������
void sort(struct stuSqList* l);

//�ļ�����
//�˳�ϵͳ��ʱ�򱣴浽�����ļ� stuInfo.txt ��
void saveToFile(struct stuSqList* l);

//�˳�ǰ����˳���
void destory(struct stuSqList* l);

int main() {
	//����˳���
	struct stuSqList* list = createSqList();
	//��ʼ��˳���
	initSqList(list);
	//�˵�ѡ��
	int select;
	while (true)
	{
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
			saveToFile(list);
			//������˳���
			destory(list);
			//����˳�
			exit(0);
			break;
		case 1:
			stuInsertMenu(list);
			break;
		case 2:
			stuDelMenu(list);
			break;
		case 3:
			stuModifyMenu(list);
			break;
		case 4:
			stuSearchMenu(list);
			break;
		case 5:
			travel(list);
			break;
		default:
			printf("����ѡ���������������룡");
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}

//����ѧ��˳�����
struct stuSqList* createSqList(){
	struct stuSqList* pNew = malloc(sizeof(struct stuSqList));
	while (NULL == pNew) {
		pNew = malloc(sizeof(struct stuSqList));
	}
	return pNew;
}

//��ʼ��˳�����
void initSqList(struct stuSqList* l) {
	l->parr = malloc(1 * sizeof(struct student));
	l->curSize = 0;
	l->maxSize = 1;
	//�ļ��������������ļ� stuInfo.txt ���ѧ����Ϣ����˳���
	FILE* fp = fopen("stuInfo.txt", "r+");
	while (NULL == fp)
	{
		printf("�ļ���ʧ�ܣ���������...\n");
		fp = fopen("stuInfo.txt", "r+");
	}
	struct student s;
	while (EOF != fscanf(fp, "%lld %s %s %d %lf", &s.ID, s.name, s.gender, &s.age, &s.credit))
	{
		push(l, s);
	}
	//�ر��ļ�
	fclose(fp);
}

//����ѧ������
struct student createStu(long long int ID, char* name, char* gender, int age, double credit)
{
	struct student s;
	s.ID = ID;
	strcpy(s.name, name);
	strcpy(s.gender, gender);
	s.age = age;
	s.credit = credit;
	//���س�ȥ
	return s;
}

//ѧ������˵�
void stuInsertMenu(struct stuSqList* list)
{
	//Ҫ��ӵ�ѧ����Ϣ
	long long int _ID;
	int _age;
	char _name[11];
	char _gender[3];
	double _credit;
	//�ж�ѧ���Ƿ����
	int isExit;
	//ĳѧ��
	long long int selectID;
	//ĳ����
	char selectName[11];
	//Ҫ��ӵ�ѧ��
	struct student s;
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
			getchar();
			//�ж�Ҫ�����ѧ����û���ظ�
			isExit = travelByID(list, _ID);
			while (-1 != isExit) {
				//���ظ�����������
				printf("�����ѧ���Ѵ��ڣ����������룺");
				scanf("%lld", &_ID);
				getchar();
				isExit = travelByID(list, _ID);
			}
			printf("���������ѧ����������");
			scanf("%s", _name);
			getchar();
			printf("���������ѧ�����Ա�");
			scanf("%s", _gender);
			printf("���������ѧ�������䣺");
			scanf("%d", &_age);
			printf("���������ѧ����ѧ�֣�");
			scanf("%lf", &_credit);
			//printf("\t\t -------------------------------\n");
			//system("pause");
			//printf("%lld %s %s %d\n", _ID, _name, _gender, _age);
			//system("pause");
			s = createStu(_ID, _name, _gender, _age,_credit);
			push(list, s);
			printf("��ӳɹ�!\n");
			system("pause");
			break;
		case 2:
			printf("���������ѧ����ѧ�ţ�");
			scanf("%lld", &_ID);
			getchar();
			//�ж�Ҫ�����ѧ����û���ظ�
			isExit = travelByID(list, _ID);
			while (-1 != isExit) {
				//���ظ�����������
				printf("�����ѧ���Ѵ��ڣ����������룺");
				scanf("%lld", &_ID);
				getchar();
				isExit = travelByID(list, _ID);
			}
			printf("���������ѧ����������");
			scanf("%s", _name);
			getchar();
			printf("���������ѧ�����Ա�");
			scanf("%s", _gender);
			printf("���������ѧ�������䣺");
			scanf("%d", &_age);
			printf("������ĳѧ�ţ�");
			scanf("%lld", &selectID);
			printf("���������ѧ����ѧ�֣�");
			scanf("%lf", &_credit);

			//printf("\t\t -------------------------------\n");
			//system("pause");
			//printf("%lld %s %s %d\n", _ID, _name, _gender, _age);
			//system("pause");
			s = createStu(_ID, _name, _gender, _age,_credit);
			midInsertByID(list, s, selectID);
			break;
		case 3:
			printf("���������ѧ����ѧ�ţ�");
			scanf("%lld", &_ID);
			getchar();
			//�ж�Ҫ�����ѧ����û���ظ�
			isExit = travelByID(list, _ID);
			while (-1 != isExit) {
				//���ظ�����������
				printf("�����ѧ���Ѵ��ڣ����������룺");
				scanf("%lld", &_ID);
				getchar();
				isExit = travelByID(list, _ID);
			}
			printf("���������ѧ����������");
			scanf("%s", _name);
			getchar();
			printf("���������ѧ�����Ա�");
			scanf("%s", _gender);
			printf("���������ѧ�������䣺");
			scanf("%d", &_age);
			printf("������ĳѧ����������");
			scanf("%s", selectName);
			printf("���������ѧ����ѧ�֣�");
			scanf("%lf", &_credit);
			s = createStu(_ID, _name, _gender, _age,_credit);
			midInsertByName(list, s, selectName);
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
void stuDelMenu(struct stuSqList* list)
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
			pop(list);
			break;
		case 2:
			printf("������Ҫɾ����ѧ��ѧ�ţ�");
			scanf("%lld", &selectID);
			delStuByID(list, selectID);
			break;
		case 3:
			printf("������Ҫɾ����ѧ��������");
			scanf("%s", selectName);
			delStuByName(list, selectName);
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
void stuModifyMenu(struct stuSqList* list)
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
			modifyByID(list, selectID);
			break;
		case 2:
			printf("������Ҫ�޸���Ϣ��ѧ��������");
			scanf("%s", selectName);
			modifyByName(list, selectName);
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
void stuSearchMenu(struct stuSqList* list)
{
	//Ҫ��ѯ��ѧ��
	long long int selectID;
	//Ҫ��ѯ������
	char selectName[11];
	//��ѯѧ���������������ظ�,�������¼�±�
	int nameIdx[100] = { 0 };

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
			printf("������Ҫ��ѯ��Ϣ��ѧ��ѧ�ţ�");
			scanf("%lld", &selectID);
			int idx = travelByID(list, selectID);
			while (-1 == idx) {
				printf("�����ѧ�Ų����ڣ����������루����-2��������");
				scanf("%lld", &selectID);
				if (-2 == selectID) {
					break;
				}
				idx = travelByID(list, selectID);
			}
			if (idx >= 0) {
				printf("������ѧ��ѧ��Ϊ��%s����ѧ����\n", selectID);
				printf("%lld %s %s %d\n",list->parr[idx].ID, list->parr[idx].name, list->parr[idx].gender, list->parr[idx].age);
			}
			system("pause");

			break;
		case 2:
			printf("������Ҫ��ѯ��Ϣ��ѧ��������");
			scanf("%s", selectName);
			//��Ҫ������ͬ���Ķ�Ҫ��ʾ��������������д
			//�жϱ��Ƿ����
			if (NULL == list) {
				printf("�����ڣ�");
				system("pause");
				return;
			}
			//�������������е��±��ƶ�
			int index = 0;
			//��ʼ����
			for (int i = 0; i < list->curSize; i++)
			{
				if (0 == (strcmp(list->parr[i].name, selectName))) {
					nameIdx[index++] = i;
				}
			}
			//������ɣ���ʼ���
			printf("������ѧ������Ϊ��%s����ѧ����\n", selectName);
			for (int i = 0; i < index; i++) {
				printf("%lld %s %s %d\n", list->parr[i].ID, list->parr[i].name, list->parr[i].gender, list->parr[i].age);
			}
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
void push(struct stuSqList* l, struct student s)
{
	//printf("%lld %s %s %d\n", s.ID, s.name,s.gender, s.age);
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�жϱ��Ƿ������
	if (l->curSize >= l->maxSize) {
		//�����˾����¿����ڴ�
		int maxSizeTemp = (l->maxSize / 2 > 1 ? l->maxSize / 2 : 1) + l->maxSize;
		//�������ڴ�
		struct student* pNew = malloc(maxSizeTemp * sizeof(struct student));
		while (NULL == pNew) {
			pNew = malloc(maxSizeTemp * sizeof(struct student));
		}
		//�����ڴ����ݴ浽���ڴ�
		memcpy(pNew, l->parr, l->curSize * sizeof(struct student));
		//�ͷ����ڴ�
		free(l->parr);
		//ָ�����ڴ�
		l->parr = pNew;
		//�����������
		l->maxSize = maxSizeTemp;
	}
	//û��ֱ�Ӵ�
	l->parr[l->curSize].ID = s.ID;
	strcpy(l->parr[l->curSize].name, s.name);
	strcpy(l->parr[l->curSize].gender, s.gender);
	l->parr[l->curSize].age = s.age;
	l->parr[l->curSize].credit = s.credit;
	l->curSize++;
	sort(l);//����
}

//����ѧ���м��
void midInsertByID(struct stuSqList* l, struct student s, long long int ID)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�����ҵ�Ŀ��ѧ�ŵ��±�
	int distIdx = travelByID(l, ID);
	if (-1 == distIdx) {
		printf("δ�ҵ�Ŀ��ѧ�ţ�����ʧ�ܣ�\n");
		system("pause");
		return;
	}
	//�жϱ��Ƿ������
	if (l->curSize >= l->maxSize) {
		//�����˾����¿����ڴ�
		int maxSizeTemp = (l->maxSize / 2 > 1 ? l->maxSize / 2 : 1) + l->maxSize;
		//�������ڴ�
		struct student* pNew = malloc(maxSizeTemp * sizeof(struct student));
		while (NULL == pNew) {
			pNew = malloc(maxSizeTemp * sizeof(struct student));
		}
		//�����ڴ����ݴ浽���ڴ�
		memcpy(pNew, l->parr, l->curSize * sizeof(struct student));
		//�ͷ����ڴ�
		free(l->parr);
		//ָ�����ڴ�
		l->parr = pNew;
		//�����������
		l->maxSize = maxSizeTemp;
	}
	//����պ��ǲ��뵽������һ����ֱ��д��
	if (distIdx == l->curSize-1) {
		l->parr[l->curSize].ID = s.ID;
		strcpy(l->parr[l->curSize].name, s.name);
		strcpy(l->parr[l->curSize].gender, s.gender);
		l->parr[l->curSize].age = s.age;
		l->curSize++;
		printf("��ӳɹ�!\n");
		system("pause");
		return;
	}
	//��������Ĳ���
	for (int i = l->curSize - 1; i > distIdx; i--)
	{
		l->parr[i + 1] = l->parr[i];
	}
	l->parr[distIdx + 1].ID = s.ID;
	strcpy(l->parr[distIdx + 1].name, s.name);
	strcpy(l->parr[distIdx + 1].gender, s.gender);
	l->parr[distIdx + 1].age = s.age;
	l->curSize++;
	printf("��ӳɹ�!\n");
	system("pause");
	return;
}

//���������м��
void midInsertByName(struct stuSqList* l, struct student s, char* name)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�����ҵ�Ŀ���������±�
	int distIdx = travelByName(l, name);
	if (-1 == distIdx) {
		printf("δ�ҵ�Ŀ������������ʧ�ܣ�\n");
		system("pause");
		return;
	}
	//�жϱ��Ƿ������
	if (l->curSize >= l->maxSize) {
		//�����˾����¿����ڴ�
		int maxSizeTemp = (l->maxSize / 2 > 1 ? l->maxSize / 2 : 1) + l->maxSize;
		//�������ڴ�
		struct student* pNew = malloc(maxSizeTemp * sizeof(struct student));
		while (NULL == pNew) {
			pNew = malloc(maxSizeTemp * sizeof(struct student));
		}
		//�����ڴ����ݴ浽���ڴ�
		memcpy(pNew, l->parr, l->curSize * sizeof(struct student));
		//�ͷ����ڴ�
		free(l->parr);
		//ָ�����ڴ�
		l->parr = pNew;
		//�����������
		l->maxSize = maxSizeTemp;
	}
	//����պ��ǲ��뵽������һ����ֱ��д��
	if (distIdx == l->curSize - 1) {
		l->parr[l->curSize].ID = s.ID;
		strcpy(l->parr[l->curSize].name, s.name);
		strcpy(l->parr[l->curSize].gender, s.gender);
		l->parr[l->curSize].age = s.age;
		l->curSize++;
		printf("��ӳɹ�!\n");
		system("pause");
		return;
	}
	//��������Ĳ���
	for (int i = l->curSize - 1; i > distIdx; i--)
	{
		l->parr[i + 1] = l->parr[i];
	}
	l->parr[distIdx + 1].ID = s.ID;
	strcpy(l->parr[distIdx + 1].name, s.name);
	strcpy(l->parr[distIdx + 1].gender, s.gender);
	l->parr[distIdx + 1].age = s.age;
	l->curSize++;
	printf("��ӳɹ�!\n");
	system("pause");
	return;
}

//����
void travel(struct stuSqList* list)
{
	system("cls");
	printf("\t\t ---------------ȫ��ѧ����Ϣ-----------------\n");
	printf("\t\t| ѧ      ��    ��    ��   �Ա�   ����  ѧ�� |\n");
	for (int i = 0; i < list->curSize; i++)
	{
		printf("\t\t| %10lld  %10s   %4s   %4d  %.1lf  |\n", list->parr[i].ID, list->parr[i].name, list->parr[i].gender, list->parr[i].age, list->parr[i].credit);
	}
	printf("\t\t -------------------����--------------------\n");
	system("pause");
}

//����ѧ�ű���(�����±�)
int travelByID(struct stuSqList* l, long long int ID)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//��ʼ����
	for (int i = 0; i < l->curSize; i++)
	{
		if (ID == l->parr[i].ID)return i;
	}
	//������֮��û�еĻ��ͷ���-1
	return -1;
}

//�������������������±꣩
int travelByName(struct stuSqList* l,char* name)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//��ʼ����
	for (int i = 0; i < l->curSize; i++)
	{
		if (0 == (strcmp(l->parr[i].name,name)))return i;
	}
	//������֮��û�еĻ��ͷ���-1
	return -1;
}

//βɾ
void pop(struct stuSqList* l)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	if (0 == l->curSize) {
		printf("�����������ݣ��޷�����ɾ����\n");
		system("pause");
		return;
	}
	l->curSize--;
	printf("ɾ���ɹ�!\n");
	system("pause");
}

//����ѧ��ɾ��ѧ��
void delStuByID(struct stuSqList* l,long long int ID)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�ҵ�Ҫɾ����ѧ�ŵ��±�
	int delIdx = travelByID(l, ID);
	if (-1 == delIdx) {
		printf("δ�ҵ�ѧ��Ϊ��%lld����ѧ����\n", ID);
		system("pause");
		return;
	}
	//ɾ��
	for (int i = delIdx; i < l->curSize-1; i++)
	{
		l->parr[i] = l->parr[i + 1];
	}
	l->curSize--;
	printf("ɾ���ɹ�!\n");
	system("pause");
}

//��������ɾ��ѧ��
void delStuByName(struct stuSqList* l, char* name)
{
	int nameArr[100] = { 0 };
	int select;
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�ҵ�Ҫɾ�����������±�
	int delIdx = travelByName(l, name);
	if (-1 == delIdx) {
		printf("δ�ҵ�����Ϊ��%s����ѧ����\n", name);
		system("pause");
		return;
	}
	int idx = 0;
	//��ʼ��������
	for (int i = 0; i < l->curSize; i++)
	{
		if (0 == (strcmp(l->parr[i].name, name))) {
			nameArr[idx++] = i;
		}
	}
	//��ʼ�������
	printf("����������%s���ҵ�����ѧ����\n", name);
	for (int i = 0; i < idx; i++)
	{
		printf("%d. %lld %s %s %d\n", i+1,l->parr[nameArr[i]].ID, l->parr[nameArr[i]].name, l->parr[nameArr[i]].gender, l->parr[nameArr[i]].age);
	}
	printf("��ѡ����Ҫɾ����ѧ��������-1ȡ��ɾ������");
	scanf("%d", &select);
	if (-1 == select)return;
	select--;
	while (select<0 || select>idx - 1) {
		printf("ѡ����ڣ����������룡\n");
		printf("��ѡ����Ҫɾ����ѧ����");
		scanf("%d", &select);
	}
	//ɾ��
	for (int i = nameArr[select]; i < l->curSize - 1; i++)
	{
		l->parr[i] = l->parr[i + 1];
	}
	l->curSize--;
	printf("ɾ���ɹ�!\n");
	system("pause");
}

//����ѧ���޸�ѧ����Ϣ
void modifyByID(struct stuSqList* l, long long int ID)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�ҵ�Ҫ�޸ĵ�ѧ�ŵ��±�
	int modIdx = travelByID(l, ID);
	if (-1 == modIdx) {
		printf("δ�ҵ�ѧ��Ϊ��%lld����ѧ����", ID);
		return;
	}
	long long int _ID = -1;
	char _name[11] = "-1";
	char _gender[3] = "-1";
	int _age = -1;
	printf("��ǰѧ�ţ�%lld\n", l->parr[modIdx].ID);
	printf("�������޸ĺ��ѧ�ţ�����-1ȡ���޸ģ���");
	scanf("%lld", &_ID);
	if (-1 == _ID) {
		printf("��ȡ���޸�ѧ�ţ�\n");
	}
	else {
		l->parr[modIdx].ID = _ID;
	}
	printf("��ǰ������%s\n", l->parr[modIdx].name);
	printf("�������޸ĺ������������-1ȡ���޸ģ���");
	scanf("%s", &_name);
	if (0==(strcmp(_name,"-1"))) {
		printf("��ȡ���޸�������\n");
	}
	else {
		strcpy(l->parr[modIdx].name, _name);
	}
	printf("��ǰ�Ա�%s\n", l->parr[modIdx].gender);
	printf("�������޸ĺ������������-1ȡ���޸ģ���");
	scanf("%s", &_gender);
	if (0 == (strcmp(_gender, "-1"))) {
		printf("��ȡ���޸��Ա�\n");
	}
	else {
		strcpy(l->parr[modIdx].gender, _gender);
	}
	printf("��ǰ���䣺%d\n", l->parr[modIdx].age);
	printf("�������޸ĺ�����䣨����-1ȡ���޸ģ���");
	scanf("%d", &_age);
	if (-1 == _age) {
		printf("��ȡ���޸����䣡\n");
	}
	else {
		l->parr[modIdx].age = _age;
	}
	printf("�޸����!\n");
	system("pause");
}

//���������޸�ѧ����Ϣ
void modifyByName(struct stuSqList* l, char* name)
{
	//�жϱ��Ƿ����
	if (NULL == l) {
		printf("�����ڣ�");
		system("pause");
		return;
	}
	//�ҵ�Ҫ�޸ĵ�ѧ�ŵ��±�
	int modIdx = travelByName(l, name);
	if (-1 == modIdx) {
		printf("δ�ҵ�����Ϊ��%s����ѧ����", name);
		return;
	}
	long long int _ID = -1;
	char _name[11] = "-1";
	char _gender[3] = "-1";
	int _age = -1;
	printf("��ǰѧ�ţ�%lld\n", l->parr[modIdx].ID);
	printf("�������޸ĺ��ѧ�ţ�����-1ȡ���޸ģ���");
	scanf("%lld", &_ID);
	if (-1 == _ID) {
		printf("��ȡ���޸�ѧ�ţ�\n");
	}
	else {
		l->parr[modIdx].ID = _ID;
	}
	printf("��ǰ������%s\n", l->parr[modIdx].name);
	printf("�������޸ĺ������������-1ȡ���޸ģ���");
	scanf("%s", &_name);
	if (0 == (strcmp(_name, "-1"))) {
		printf("��ȡ���޸�������\n");
	}
	else {
		strcpy(l->parr[modIdx].name, _name);
	}
	printf("��ǰ�Ա�%s\n", l->parr[modIdx].gender);
	printf("�������޸ĺ������������-1ȡ���޸ģ���");
	scanf("%s", &_gender);
	if (0 == (strcmp(_gender, "-1"))) {
		printf("��ȡ���޸��Ա�\n");
	}
	else {
		strcpy(l->parr[modIdx].gender, _gender);
	}
	printf("��ǰ���䣺%d\n", l->parr[modIdx].age);
	printf("�������޸ĺ�����䣨����-1ȡ���޸ģ���");
	scanf("%d", &_age);
	if (-1 == _age) {
		printf("��ȡ���޸����䣡\n");
	}
	else {
		l->parr[modIdx].age = _age;
	}
	printf("�޸����!\n");
	system("pause");
}

//������������
void sort(struct stuSqList* l)
{
	struct student temp = { 0 };
	for (int i = 0; i < l->curSize-1; i++)
	{
		for (int j = 0; j < l->curSize - i - 1; j++)
		{
			double one = l->parr[j].credit;
			double two = l->parr[j + 1].credit;
			if (one > two)
			{
				memcpy(&temp, &(l->parr[j + 1]), sizeof(struct student));
				memcpy(&(l->parr[j + 1]), &(l->parr[j]), sizeof(struct student));
				memcpy(&(l->parr[j]), &temp, sizeof(struct student));
			}
		}
	}
}

//�ļ�����
//�˳�ϵͳ��ʱ�򱣴浽�����ļ� stuInfo.txt ��
void saveToFile(struct stuSqList* l)
{
	//��д��ģʽ��stuInfo.txt�ļ�
	FILE* fp = fopen("stuInfo.txt", "w+");
	while (NULL == fp)
	{
		printf("�ļ���ʧ�ܣ���������...\n");
		fp = fopen("stuInfo.txt", "w+");
	}
	//�����е�����д���ļ�
	for (int i = 0; i < l->curSize; i++)
	{
		fprintf(fp, "%lld %s %s %d %lf\n", l->parr[i].ID, l->parr[i].name, l->parr[i].gender, l->parr[i].age, l->parr[i].credit);
	}
	//���ǵùر��ļ�
	fclose(fp);
}

//�˳�ǰ����˳���
void destory(struct stuSqList* l)
{
	//û�б��˾Ͳ���������
	if (NULL == l)return;
	if (NULL == l->parr)return;
	free(l->parr);
	free(l);
}
