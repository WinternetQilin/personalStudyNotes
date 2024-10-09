#include "ExLine.h"

ExLine::ExLine(int size, COLORREF color)
{
	this->size = size;
	this->color = color;
	this->isDown = false;
}

void ExLine::draw(ExMessage msg)
{
	//�������
	if (msg.message == WM_LBUTTONDOWN) {
		this->isDown = true;
		//��¼���
		this->begin = ExPoint(msg.x, msg.y);
	}
	//�������
	if (msg.message == WM_LBUTTONUP) {
		this->isDown = false;
	}
	//���ߣ��������+�ƶ�
	if (this->isDown == true && msg.message == WM_MOUSEMOVE) {
		setlinestyle(PS_ENDCAP_ROUND,this->size);
		setlinecolor(this->color);
		line(this->begin.getX(), this->begin.getY(), msg.x, msg.y);
	}
	//��һ�λ��ߵĽ�β����һ�λ��ߵ����
	this->begin = ExPoint(msg.x, msg.y);
}

void ExLine::setSize(int& size)
{
	this->size = size;
}

void ExLine::setColor(COLORREF color)
{
	this->color = color;
}
