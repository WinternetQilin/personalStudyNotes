#pragma once
#include<iostream>
#include<vector>
#include"Identity.h"
#include"Manager.h"
#include"Student.h"
#include"Teacher.h"
#include"ComputerRooom.h"

using namespace std;

class Manager:public Identity
{
public:
	//�޲ι���
	Manager();

	//�вι��죨����Ա���������룩
	Manager(string name, string pwd);

	//ѡ��˵�
	virtual void operMenu();

	//����˺�  
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	//��ʼ������������������������Ϊ��ʵ������˺�ʱ��ȥ�ز�����
	void initVector();

	//����ظ�(id��ѧ��=1����ʦ=����;����true �������ظ���false����û���ظ�)
	bool checkRepeat(int id, int type);

	//ѧ������
	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTea;

	//��������
	vector<ComputerRoom> vCom;

};

