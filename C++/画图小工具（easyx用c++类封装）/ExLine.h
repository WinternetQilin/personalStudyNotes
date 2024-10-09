#pragma once
#include"ExCommon.h"
#include"ExPoint.h"
class ExLine
{
public:
	ExLine(int size = 5, COLORREF color = BLACK);
	void draw(ExMessage msg);
	void setSize(int& size);
	void setColor(COLORREF color);
private:
	//�ߵĴ�ϸ
	int size;
	//�ߵ���ɫ
	COLORREF color;
	//��갴���Ƿ���
	bool isDown;
	//�ߵ����
	ExPoint begin;
};

