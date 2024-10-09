#include<stdio.h>
#include<stdbool.h>
#include<windows.h>
#include"res.h"
#include"myStack.h"

//�Ӹ�����
void printMap(int map[ROW][COL],myPoint* curPos) {
	system("cls");
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++) {
			if (curPos->row == i && curPos->col == j) {
				printf("��");
			}
			else {
				if (map[i][j]) {
					printf("ǽ");
				}
				else {
					printf("  ");
				}
			}
		}
		printf("\n");
	}
}
void printPathMap(int map[ROW][COL], myStack stack, myPoint* curPos) {
	printf("\n");
	int step = 0;
	myPoint* p = (stack.pBuff) + step;

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++) {

			if (p->row < i && p->col == j) {
				i = p->row;
			}
			if (p->row == i && p->col == j) {
				map[i][j] = 2;
				step++;
				p = (stack.pBuff) + step;
			}

		}
	}

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++) {
			if (curPos->row == i && curPos->col == j) {
				printf("��");
			}
			else {
				if (1==map[i][j]) {
					printf("ǽ");
				}
				if (2 == map[i][j]) {
					printf("��");
					continue;
				}
				if (0 == map[i][j]) {
					printf("  ");
				}
			}
		}
		printf("\n");
	}
}

/*
���Ѱ·�㷨��
	Ѱ·�㷨��ͨ���㷨���滮һ������㵽�յ��·��
	���Ѱ·�����ƣ�ֻ����ֱ�ߣ�������б��
	���Ѱ·˼�룺
		1.��̽����ǰ������������ĸ�����ֱ���̽
			��̽����˳���ϣ��ң��£���һ������£�Ҫô˳ʱ�룬Ҫô��ʱ�룩
			���Ը������������б�ǣ��߹���·����߹������ϰ���һ�����Ϊ������
		2.��������ͬ
			ÿ��һ������ջ����������ͬ�ͳ�ջ�������µ�ջ��
		3.����
			�����յ����
			ջ���˽���

*/

int main() {
	int map[ROW][COL]={
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 0, 0, 1, 0, 1, 1 },
		{ 1, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	//������ͼ������Ƿ��߹�����̽����
	struct pathNode pathMap[ROW][COL] = { 0 };

	//׼��һ��ջ
	myStack stack;
	//myPoint test[] = {
	//	{1,1},
	//	{2,1},
	//	{3,1},
	//	{4,1},
	//	{5,1}
	//};
	init(&stack);
	myPoint begPos = { 1,1 };
	myPoint endPos = { 8,8 };
	//�������߹�������ջ
	pathMap[begPos.row][begPos.col].isFind = true;
	push(&stack, &begPos);

	//����һ����ǰ��
	myPoint curPos = begPos;
	//����һ����̽��
	myPoint searchPos;
	//����Ƿ��ҵ��յ�
	bool isFindEnd = false;

	while (true)
	{
		//��ʼѰ·
		searchPos = curPos;
		//�жϵ�ǰ�����̽����
		switch (pathMap[curPos.row][curPos.col].dir)
		{
		case p_up:
			searchPos.row--;
			//��ǰ����̽����ı�
			pathMap[curPos.row][curPos.col].dir=p_right;
			//�ж���̽�����ܲ�����
			if (wall != map[searchPos.row][searchPos.col] &&//�����ϰ���
				true != pathMap[searchPos.row][searchPos.col].isFind) {//û���߹�
				//���ߣ�
				// λ����ջ
				push(&stack, &searchPos);
				// ����߹�
				pathMap[searchPos.row][searchPos.col].isFind = true;
				// ��(��ǰ��仯)
				curPos = searchPos;
			}
			break;
		case p_right:
			searchPos.col++;
			//��ǰ����̽����ı�
			pathMap[curPos.row][curPos.col].dir=p_down;
			//�ж���̽�����ܲ�����
			if (wall != map[searchPos.row][searchPos.col] &&//�����ϰ���
				true != pathMap[searchPos.row][searchPos.col].isFind) {//û���߹�
				//���ߣ�
				// λ����ջ
				push(&stack, &searchPos);
				// ����߹�
				pathMap[searchPos.row][searchPos.col].isFind = true;
				// ��(��ǰ��仯)
				curPos = searchPos;
			}
			break;
		case p_down:
			searchPos.row++;
			//��ǰ����̽����ı�
			pathMap[curPos.row][curPos.col].dir=p_left;
			//�ж���̽�����ܲ�����
			if (wall != map[searchPos.row][searchPos.col] &&//�����ϰ���
				true != pathMap[searchPos.row][searchPos.col].isFind) {//û���߹�
				//���ߣ�
				// λ����ջ
				push(&stack, &searchPos);
				// ����߹�
				pathMap[searchPos.row][searchPos.col].isFind = true;
				// ��(��ǰ��仯)
				curPos = searchPos;
			}
			break;
		case p_left:
			searchPos.col--;
			//��ǰ����̽����ı�
			pathMap[curPos.row][curPos.col].dir=p_right;
			//�ж���̽�����ܲ�����
			if (wall != map[searchPos.row][searchPos.col] &&//�����ϰ���
				true != pathMap[searchPos.row][searchPos.col].isFind) {//û���߹�
				//���ߣ�
				// λ����ջ
				push(&stack, &searchPos);
				// ����߹�
				pathMap[searchPos.row][searchPos.col].isFind = true;
				// ��(��ǰ��仯)
				curPos = searchPos;
			}
			else {
				//������
				//��ջ
				pop(&stack);
				//����ջ��
				myPoint* temp = getTop(&stack);
				curPos.row = temp->row;
				curPos.col = temp->col;
			}
			
			break;
		}
		Sleep(200);
		printMap(map, &curPos);

		//�ж��Ƿ��ҵ��յ�
		if (endPos.col == curPos.col&&endPos.row == curPos.row) {
			isFindEnd = true;
			break;
		}

		//�ж�ջ�Ƿ�Ϊ��
		if (isEmpty(&stack))break;
	}
	//�ҵ��յ㣬��ӡջ��λ��
	if (isFindEnd) {
		printf("�ҵ��յ��ˣ�\n");
		system("pause");
		printPathMap(map, stack, &curPos);
		system("pause");
		printf("path��\n");
		while (!isEmpty(&stack))
		{
			printf("(%d , %d)\n", getTop(&stack)->row, getTop(&stack)->col);
			pop(&stack);
		}
	}
	else {
		printf("�Ҳ����յ��ˣ�\n");
	}
	//����
	//for (int i = 0; i < 5; i++)
	//{
	//	push(&stack, &test[i]);
	//}
	//while (!isEmpty(&stack))
	//{
	//	printf("(%d , %d)\n", getTop(&stack)->row, getTop(&stack)->col);
	//	pop(&stack);
	//}

	return 0;
}