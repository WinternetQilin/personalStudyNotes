#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<string.h>

#define ROW 10
#define COL 10

#define StraightLineCost 10
#define DiagonalCost 14

//����ö��
enum dir
{
	up,
	down,
	left,
	right,
	l_up,
	l_down,
	r_up,
	r_down
};

//������
struct Point
{
	int row, col, f, g, h;
};

//���ڵ�����
struct treeNode {
	struct Point p;
	struct treeNode* parent;
	struct treeNode* children[8];
	int curSize;
};

//�������ڵ�ĺ���
struct treeNode* createTN(struct Point p) {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	if (NULL == pNew)return NULL;
	memset(pNew, 0, sizeof(struct treeNode));
	pNew->p.row = p.row;
	pNew->p.col = p.col;
	//ע��gҪ�ۼ�
	pNew->p.g = p.g;

	return pNew;
}

//�жϵ��ܲ�����
bool canWalk(struct Point p, int map[ROW][COL], bool isGone[ROW][COL]) {
	if (p.row < 0 || p.row >= ROW ||
		p.col < 0 || p.col >= COL) return false;

	if (isGone[p.row][p.col])return false;

	if (1 == map[p.row][p.col])return false;

	return true;
}

//����h
int getH(struct Point now, struct Point dist) {
	int x = dist.row - now.row;
	if (x < 0) {
		x = -x;
	}
	int y = dist.col - now.col;
	if (y < 0) {
		y = -y;
	}

	return (x + y) * StraightLineCost;
}

/*
A��Ѱ·�㷨��
	��·��������������������������ʾѰ·������
	���ۣ����Ķ࣬���۸ߣ������٣����۵�
	A��Ѱ·������ֱ�ߣ�������б��
	ÿһ���Ĵ��۶���Ҫ�������ã�
		ֱ��10��б��14
		һ������ñ���  ֱ�ߣ�б��=1������2 ��Դ�Թ��ɶ���
		��������ֵ��f��= ��㵽��ǰ�㣨��̽�㣩�Ѿ������Ĵ��ۣ�g�� + ��̽�㵽�յ��Ԥ�����ۣ�h��
		��Ԥ��ʱҪ�����ϰ������ֻ��ֱ�߾���
		�߹��ĵ�����Ҫ��Ϊ�߹�
	ÿһ������Ϊ����а˸�������ߣ�����ÿ��������Ϊ�˲����ṹ�洢
		ͬ��Ҫ��ָ��Ԫ�ص�ָ�룬�����ҵ��յ��������·��
		��������������п��ܵĽڵ㣬ÿ�α�����������������ֵ��С�ĵ��ߣ��߲�ͨ�ĵ�ǵô�������ȥ����

*/

int main() {

	//��ͼ
	int map[ROW][COL] = {
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }
	};
	//����߹���ͼ
	bool isGone[ROW][COL] = { 0 };
	//����Ƿ��ҵ��յ�
	bool isFind = false;

	//���
	struct Point begP = { 1,1 };
	//�����Ϊ�߹�
	isGone[begP.row][begP.col] = true;
	//�յ�
	struct Point endP = { 6,7 };

	//��
	struct treeNode* treeRoot = NULL;
	//�������
	treeRoot = createTN(begP);

	//�ȴ�С������
	struct treeNode* arr[100];
	//��Ч����
	int cur = 0;

	//��ǰ��
	struct treeNode* curN = treeRoot;
	//��ʱ��
	struct treeNode* pTemp = NULL;
	//��Сֵ�±��¼
	int minIdx;

	//��ʼѰ·
	while (true)
	{
		//������ǰ����Χ�ĵ�
		for (int i = 0; i < 8; i++)
		{
			pTemp = createTN(curN->p);
			switch (i) {
			case up:
				pTemp->p.row--;
				pTemp->p.g += StraightLineCost;
				break;
			case down:
				pTemp->p.row++;
				pTemp->p.g += StraightLineCost;
				break;
			case left:
				pTemp->p.col--;
				pTemp->p.g += StraightLineCost;
				break;
			case right:
				pTemp->p.col++;
				pTemp->p.g += StraightLineCost;
				break;
			case l_up:
				pTemp->p.col--;
				pTemp->p.row--;
				pTemp->p.g += DiagonalCost;
				break;
			case r_up:
				pTemp->p.col++;
				pTemp->p.row--;
				pTemp->p.g += DiagonalCost;
				break;
			case l_down:
				pTemp->p.col--;
				pTemp->p.row++;
				pTemp->p.g += DiagonalCost;
				break;
			case r_down:
				pTemp->p.col++;
				pTemp->p.row++;
				pTemp->p.g += DiagonalCost;
				break;
			}//switch end

			//�ж��ܲ�����
			if (canWalk(pTemp->p,map,isGone)) {
				//���߾�Ҫ
				//����h
				pTemp->p.h = getH(pTemp->p, endP);
				//����f
				pTemp->p.f = pTemp->p.h + pTemp->p.g;
				//����
				pTemp->parent = curN;
				curN->children[curN->curSize++] = pTemp;
				//������
				arr[cur++] = pTemp;
				//�����Ȳ�Ҫ��
			}
			else {
				//������
				free(pTemp);
				pTemp = NULL;
			}

		}//for (int i = 0; i < 8; i++) end
		
		//����
		//for (int i = 0; i < cur; i++) {
		//	printf("%d:(%d,%d)g:%d h:%d f:%d\n", i, arr[i]->p.row, arr[i]->p.col,arr[i]->p.g,arr[i]->p.h,arr[i]->p.f);
		//}
		
		//���������ҵ� f ��С�ĵ���
		minIdx = 0;//�ȼ����һ��Ϊ��Сֵ
		for (int j = 0; j < cur; j++)
		{
			if (arr[j]->p.f < arr[minIdx]->p.f) {
				minIdx = j;
			}
		}
		curN = arr[minIdx];
		//��Ҫ�ڵ�ͼ�б���߹�
		isGone[curN->p.row][curN->p.col] = true;

		//������Ҫ���߹��ĵ�ɾ��
		for (int k = minIdx; k < cur-1; k++)
		{
			arr[k] = arr[k + 1];
		}
		cur--;

		//����
		//printf("ɾ֮��\n");
		//for (int i = 0; i < cur; i++) {
		//	printf("%d:(%d,%d)g:%d h:%d f:%d\n", i, arr[i]->p.row, arr[i]->p.col, arr[i]->p.g, arr[i]->p.h, arr[i]->p.f);
		//}

		//�ж��Ƿ��ҵ��յ�
		if (curN->p.row == endP.row&&
			curN->p.col == endP.col) {
			isFind = true;
			break;
		}
		//�ж������Ƿ�Ϊ��
		if (0 == cur) {
			break;
		}

	}//while(true) end

	if (isFind) {
		printf("�ҵ��յ��ˣ�\n");
		//��ӡ·��
		while (curN)
		{
			printf("(%d,%d)\n", curN->p.row, curN->p.col);
			curN = curN->parent;
		}
	}
	else {
		printf("�Ҳ����յ㣡\n");
	}

	return 0;
}
