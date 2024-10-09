#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include"res.h"

//�������ڵ�
struct node* createNode(struct ZiFu* pZf) {
	struct node* pNew = malloc(sizeof(struct node));
	if (NULL == pNew) {
		return NULL;
	}
	memset(pNew, 0, sizeof(struct node));
	memcpy(&(pNew->data), pZf, sizeof(struct ZiFu));
	return pNew;
}

//�����ֵ乹����������
struct node* createHaffmanTree(struct AllZiFu* pZd) {
	//׼��������
	struct node** pArray = (struct node**)malloc(pZd->num * (sizeof(struct node*)));
	if (NULL == pArray)return NULL;

	for (int i = 0; i < pZd->num; i++)
	{
		pArray[i] = createNode(&(pZd->arr[i]));
		pArray[i]->data.idx = i;//�����±�
	}

	int minIdx, secMinIdx;
	int j;
	struct node* pTemp = NULL;
	//ѭ����
	for (int i = 0; i < pZd->num - 1; i++)
	{
		//1.�ҵ�����Ƶ����͵�
		//�����һ����С
		j = 0;
		while (pArray[j] == NULL)j++;//�ҵ���һ��
		minIdx = j;

		for (j = 0; j < pZd->num; j++)//������������
		{
			if (pArray[j] &&
				pArray[j]->data.cnt < pArray[minIdx]->data.cnt) {
				minIdx = j;
			}
		}

		//2.�ҵ�����Ƶ�ʵڶ��͵�
		j = 0;
		while (pArray[j] == NULL || j == minIdx)j++;//�ҵ��ڶ���
		secMinIdx = j;

		for (j = 0; j < pZd->num; j++)//������������
		{
			if (pArray[j] &&
				j != minIdx &&
				pArray[j]->data.cnt < pArray[secMinIdx]->data.cnt) {
				secMinIdx = j;
			}
		}

		//3.�����

		//���ɸ��ڵ�
		struct ZiFu tempZf = { 0,pArray[secMinIdx]->data.cnt + pArray[minIdx]->data.cnt };
		tempZf.idx = -1;
		pTemp = createNode(&tempZf);
		//����
		pTemp->pL = pArray[minIdx];
		pTemp->pR = pArray[secMinIdx];
		pArray[minIdx]->pParent = pTemp;
		pArray[secMinIdx]->pParent = pTemp;

		//4.������ɾ������Ƶ����͵ĺͳ���Ƶ�ʵڶ��͵ģ�����µĸ��ڵ�
		pArray[minIdx] = pTemp;//��ɾ������СƵ�ʽڵ�������˸��ڵ�
		pArray[secMinIdx] = NULL;
	}


	//5.���ظ��ڵ�
	return pTemp;
}

//�ж��Ƿ�ΪҶ�ӽڵ�
bool isLeaf(struct node* root) {
	if (root && NULL == root->pL && NULL == root->pR) return true;
	return false;
}

int main() {
	//�����ֵ�ṹ��
	struct AllZiFu zd = { 0 };

	FILE* fpsrc = fopen("2.txt", "rb");
	FILE* fpdist = fopen("3.txt", "wb");//��ѹ���ļ�

	//�ֵ������
	fread(&zd, 1, sizeof(struct AllZiFu), fpsrc);

	//�����ֵ����ɹ�������
	struct node* pRoot = createHaffmanTree(&zd);

	//ͳ���ֽ���
	int allCnt = pRoot->data.cnt;
	int myCount = 0;

	char temp;//�������ֽ�
	struct node* pTemp = pRoot;

	int idx;//����λ������
	bool isOK = false;
	while (1==fread(&temp,1,1,fpsrc))
	{
		idx = 0;
		while (idx < 8) {
			if ( temp&(0x80>>idx) ) {//��ǰλΪ1
				pTemp = pTemp->pL;
			}
			else {//��ǰλΪ0
				pTemp = pTemp->pR;
			}

			if (isLeaf(pTemp)) {//�����Ҷ�ӽڵ�
				fwrite(&(pTemp->data.zf),1,1,fpdist);
				myCount++;
				if (myCount >= allCnt) {
					isOK = true;
					break;
				}
				pTemp = pRoot;//�ص����ڵ�
			}
			idx++;//idx�仯
		}//end of while (idx < 8)
		if (isOK) {
			break;
		}
	}//end of (1==fread(&temp,1,1,fpsrc))

	fclose(fpsrc);
	fclose(fpdist);
	return 0;
}
