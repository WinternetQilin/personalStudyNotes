#pragma once
#include <iostream>
#include<algorithm>
#include<vector>
#include"Identity.h"
#include"ComputerRooom.h"

using namespace std;

class Student:public Identity
{
public:
	//Ĭ�Ϲ���
	Student();

	//�вι��죨ѧ�ţ��û��������룩
	Student(int id, string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴�ҵ�ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	//ѧ��ѧ��
	int m_Id;

	//��������
	vector<ComputerRoom> vCom;
};

