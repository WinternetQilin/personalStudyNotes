#pragma once
#include<stdbool.h>
#define ROW 10
#define COL 10

//��·���
enum state{road,wall,};

//��̽����
enum dir{p_up,p_right,p_down,p_left};

//��̽�ڵ�����
struct pathNode {
	//��ǰ��ĵ�ǰ��̽����
	int dir;
	//�Ƿ��߹�
	bool isFind;
};

//������
typedef struct myPoint {
	int row, col;
}myPoint;
