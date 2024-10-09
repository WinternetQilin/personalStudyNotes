#include<fstream>
#include<algorithm>
#include "Manager.h"
#include"globalFile.h"

Manager::Manager()
{
}

Manager::Manager(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;
	//��ʼ������
	this->initVector();
}

void Manager::operMenu()
{
	system("cls");
	cout << "��ӭ����Ա��" << this->m_Name << " ��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ�����";
}

void Manager::addPerson()
{
	//׼�������ļ�����
	ofstream ofs;
	//����ѡ��������Ҫ����ѧ���ļ�������ʦ�ļ�
	string fileName;
	//�洢Ҫ���������
	int id;
	string name;
	string pwd;
	//�˵�ѡ��
	int select;
	//�����Ƿ�ѭ��չʾ�˵�
	bool show = true;

	while (show) {
		system("cls");
		cout << "\t\t ---------------------------------\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          1.���ѧ��            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          2.�����ʦ            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          0.��    ��            |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t ---------------------------------\n";
		cout << "\t\t��ѡ�����Ĳ�����";
		cin >> select;
		if (1 == select) {
			fileName = STUDENT_FILE;
			cout << "������ѧ�ţ�";
			cin >> id;
			if (this->checkRepeat(id, 1)) {//���ظ�
				cout << "�����ѧ���Ѵ��ڣ����ʧ�ܣ�"<<endl;
				system("pause");
			}
			else {
				show = false;
			}
		}
		else if (2 == select) {
			fileName = TEACHER_FILE;
			cout << "������ְ���ţ�";
			cin >> id;
			if (this->checkRepeat(id, 2)) {//���ظ�
				cout << "�����ְ�����Ѵ��ڣ����ʧ�ܣ�" << endl;
				system("pause");
			}
			else {
				show = false;
			}
		}
		else if (0 == select) {
			return;
		}
		else {
			cout << "�޴�ѡ����������룡" << endl;
		}
	}
	//֪��Ҫ���ĸ��ļ��ˣ��Ϳ��Դ��ˣ�ģʽ��ֻд|׷��д��
	ofs.open(fileName, ios::out | ios::app);
	//���ŰѶ�Ҫ������û���������������
	cout << "������������";
	cin >> name;
	cout << "���������룺";
	cin >> pwd;
	//��ʼ���ļ���д
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;
	//��������
	this->initVector();
	system("pause");
	//���ǵùر��ļ�
	ofs.close();
}

//�������ڱ�cpp��ʹ�õĺ���
void _printStudent(Student& s)
{
	cout << "ѧ�ţ� " << s.m_Id << " ������ " << s.m_Name << " ���룺" << s.m_Pwd << endl;
}
void _printTeacher(Teacher& t)
{
	cout << "ְ���ţ� " << t.m_EmpId << " ������ " << t.m_Name << " ���룺" << t.m_Pwd << endl;
}

void Manager::showPerson()
{
	int select;
	bool show = true;

	
	while (show) {
		system("cls");
		cout << "\t\t ----------��ѡ��鿴����---------\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          1.�鿴����ѧ��        |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          2.�鿴������ʦ        |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|          0.��        ��        |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t ---------------------------------\n";
		cout << "\t\t��ѡ�����Ĳ�����";
		cin >> select;
		if (1 == select) {
			system("cls");
			cout << "����ѧ����Ϣ���£�" << endl;
			for_each(vStu.begin(), vStu.end(), _printStudent);
			show = false;
		}
		else if (2 == select) {
			system("cls");
			cout << "������ʦ��Ϣ���£�" << endl;
			for_each(vTea.begin(), vTea.end(), _printTeacher);
			show = false;
		}
		else if (0 == select) {
			return;
		}
		else {
			cout << "����ѡ������" << endl;
			system("pause");
		}
	}//end of while (show)
	system("pause");
}

void Manager::showComputer()
{
	cout << "������Ϣ���£� " << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "������ţ� " << it->m_ComId << " ������������� " << it->m_MaxNum << endl;
	}
	system("pause");
}

void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
}

void Manager::initVector()
{
	//����ձ���ֹ�ϴε�������Ⱦ��
	this->vStu.clear();
	this->vTea.clear();
	//��ʱ������ļ��ж�ȡ����������
	Student s;
	Teacher t;
	ComputerRoom c;
	//��ѧ���ͽ�ʦ�ļ������˺���Ϣ�ֱ�����Ӧ��vector��
	//��ѧ��
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "��ǰѧ������Ϊ�� " << vStu.size() << endl;
	system("pause");
	ifs.close();

	//����ʦ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	cout << "��ǰ��ʦ����Ϊ�� " << vTea.size() << endl;
	system("pause");
	ifs.close();

	//������
	ifs.open(COMPUTER_FILE, ios::in);
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	cout << "��ǰ��������Ϊ�� " << vCom.size() << endl;
	system("pause");
	ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}
