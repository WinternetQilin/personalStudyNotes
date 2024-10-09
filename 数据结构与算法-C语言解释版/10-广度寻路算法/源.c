#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>

#define ROW 10
#define COL 10

struct myPoint {
	int row, col;
};

struct treeNode
{
	struct myPoint p;					//��ǰ�ڵ�����
	struct treeNode* parentNode;		//ָ�򸸽ڵ�
	struct treeNode* children[4];		//�ĸ�����
	int curSize;				//�Ѵ溢�Ӹ���

};

//�ĸ�����û��˳��Ҫ��
enum dir
{
	p_up,
	p_down,
	p_left,
	p_right
};

//�����ڵ㺯��
struct treeNode* createNode(int row, int col) {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	if (NULL == pNew)return NULL;
	memset(pNew, 0, sizeof(struct treeNode));
	pNew->p.row = row;
	pNew->p.col = col;
	return pNew;
}

//�ж��Ƿ�����
bool canWalk(struct myPoint p, int map[ROW][COL], bool isGoneMap[ROW][COL]) {
	//Խ��
	if (p.row >= ROW || p.row < 0 ||
		p.col >= COL || p.col < 0) {
		return false;
	}
	//ǽ
	if (map[p.row][p.col])return false;
	//�߹�
	if (isGoneMap[p.row][p.col])return false;

	return true;
}

/*
���Ѱ·�㷨��
	�����̽��
		��̽�����и�˳��
			һ�� ��������
		ÿ���ڵ㶼��¼��ǰ��̽���� �� �Ƿ��߹�
	ѭ���ҵ���ǰ����Χ�ĸ��������̽�����ܲ�����
		�����ͽ�����ת����һ������
		���ߣ���÷�����һ��������ǰλ�������¼��ջ��������ǰλ�ñ��Ϊ�߹�
		�����ߣ�ǰ����������û����������
			���һ�������ߣ������ߵ�����ͬ�ˣ���ջ���õ�ǰλ�ñ�Ϊ�µ�ջ������
		�ҵ��յ㣺��ǰλ��Ϊ�յ�λ��
		�Ҳ����յ㣺ջ����

���Ѱ·�㷨��
	�ӵ�ǰ�㿪ʼ������һ�� �Ĳ�����ֻ���ĸ������ߣ��������ң�
	һ��һ��ȥ��չ��ֱ�������յ� ���� ��һ��
		��ǰ��һ�����飬��һ��һ�����飬�����л����ǲ���л�
			�ҵ��յ㣺����������յ�
			�Ҳ�����������һ���㶼û��
*/

int main() {
	//��ͼ
	int map[ROW][COL] = {
		{ 0, 1, 0, 0, 0, 1, 0, 0, 1, 1 },
		{ 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 0, 1, 0, 1, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 }
	};
	//���
	struct myPoint begP = { 0,0 };
	//�յ�
	struct myPoint endP = { 3,9 };
	//����Ƿ��߹��ĵ�ͼ
	bool isGoneMap[ROW][COL] = { 0 };
	//��������Ҫ�������߹�
	isGoneMap[begP.row][begP.col] = true;

	//������,������Ϊ���ĸ��ڵ�
	struct treeNode* treeRoot = createNode(begP.row, begP.col);

	//��ǰ��(����㿪ʼ)
	struct treeNode* curFloor[100] = {treeRoot};
	int curFSize = 1;
	//��һ��
	struct treeNode* nextFloor[100];
	int nextFSize = 0;

	struct treeNode* pTemp = NULL;
	struct treeNode* cur = NULL;

	//�յ���
	bool isFind = false;

	while (true)
	{
		//��ʼһ����ƽ�
		for (int i = 0; i < curFSize; i++)
		{
			cur = curFloor[i];
			//�ҳ���һ�����нڵ�
			for (int j = 0; j < 4; j++)
			{
				//��ǰ�ڵ���ĸ�����
				pTemp = createNode(cur->p.row, cur->p.col);
				//���ݷ����temp
				switch (j)
				{
				case p_up:
					pTemp->p.row--;
					break;
				case p_down:
					pTemp->p.row++;
					break;
				case p_left:
					pTemp->p.col--;
					break;
				case p_right:
					pTemp->p.col++;
					break;
				}
				//�ж��ܲ�����
				if (canWalk(pTemp->p,map,isGoneMap)) {
					//����
					//����
					pTemp->parentNode = cur;
					cur->children[cur->curSize++] = pTemp;
					//����һ������
					nextFloor[nextFSize++] = pTemp;
					//����߹�
					isGoneMap[pTemp->p.row][pTemp->p.col] = true;
					//�ж��Ƿ��ҵ��յ�
					if (endP.row == pTemp->p.row &&
						endP.col == pTemp->p.col) {
						isFind = true;
						break;
					}
				}
				else {
					//������
					free(pTemp);
					pTemp = NULL;
				}
				
			}
			if (isFind)break;
		}
		if (isFind)break;

		//�����һ������ʲô��û��,ֱ������ѭ������������
		if (nextFSize == 0)break;

		//�л�����һ��
		memcpy(curFloor, nextFloor,nextFSize * sizeof(struct treeNode));
		curFSize = nextFSize;
		//����һ����������
		memset(nextFloor, 0, nextFSize * sizeof(struct treeNode));
		nextFSize = 0;
	}

	if (isFind) {
		printf("�ҵ��յ��ˣ�\n");
		while (pTemp)
		{
			printf("(%d,%d)\n", pTemp->p.row, pTemp->p.col);
			pTemp = pTemp->parentNode;
		}
	}
	else {
		printf("�Ҳ����յ㣡\n");
	}

	while (true);

	return 0;
}
