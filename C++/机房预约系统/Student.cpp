#include "Student.h"
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>
#include"globalFile.h"
#include"ComputerRooom.h"
#include"OrderFile.h"

using namespace std;

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
	//��ʼ������
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	//��ȡ������Ϣ
	ifstream ifs;
	ComputerRoom c;

	ifs.open(COMPUTER_FILE, ios::in);
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}

	ifs.close();
}

void Student::operMenu()
{
	system("cls");
	cout << "~~��ӭѧ����" << this->m_Name << " ��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.����ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.ȡ��ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ�����" << endl;
}

void Student::applyOrder()
{
	//�����õ�������
	int week, day, room;

	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
	while (true)
	{
		cin >> week;
		if (week >= 1 && week <= 5)break;
		cout << "������������������" << endl;
	}

	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	while (true)
	{
		cin >> day;
		if (day >= 1 && day <= 2)break;
		cout << "������������������" << endl;
	}

	cout << "��ѡ�������" << endl;
	int i = 1;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++,i++) {
		cout << "[" << i << "]" << " " << "�������ƣ�" << (*it).m_ComId << " " << "������" << (*it).m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= vCom.size())break;
		cout << "������������������" << endl;
	}

	cout << "ԤԼ�ɹ��������" << endl;

	//��ʼд���ļ�
	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "����:" << week << " ";
	ofs << "ʱ��:" << day << " ";
	ofs << "������ѧ��:" << this->m_Id << " ";
	ofs << "����������:" << this->m_Name << " ";
	ofs << "�����:" << vCom[room-1].m_ComId << " ";
	ofs << "ԤԼ״̬:" << 1 << endl;
	ofs.close();

	system("pause");
}

void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		return;
	}
	//��ʼ�������
	for (int i = 0; i < of.m_Size; i++)
	{
		//atoi()���������ָ�ʽ���ַ���ת��Ϊ�������͡����磬���ַ�����12345��ת��������12345
		//c_str()������C++�� string ���еĺ�������ͷ�ļ�Ϊ��#include <string>
		//���ǽ�C++�� string ת��ΪC���ַ������飬�� string �� const char* ֮���ת��
		if (atoi(of.m_orderData[i]["������ѧ��"].c_str()) == this->m_Id)
		{
			cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["����"];
			cout << " ʱ�Σ�" << (of.m_orderData[i]["ʱ��"] == "1" ? "����" : "����");
			cout << " ������" << of.m_orderData[i]["�����"];
			string status = " ״̬��"; 
			// 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
			if (of.m_orderData[i]["ԤԼ״̬"] == "1")
			{
				status += "�����";
			}
			else if (of.m_orderData[i]["ԤԼ״̬"] == "2")
			{
				status += "�ɹ�";
			}
			else if (of.m_orderData[i]["ԤԼ״̬"] == "-1")
			{
				status += "ʧ�ܣ����δͨ��";
			}
			else
			{
				status += "��ȡ��";
			}
			cout << status << endl;
		}
	}//end of for (int i = 0; i < of.m_Size; i++)
	system("pause");
}

void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "�� ";

		cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["����"];
		cout << " ʱ�Σ�" << (of.m_orderData[i]["ʱ��"] == "1" ? "����" : "����");
		cout << " ѧ�ţ�" << of.m_orderData[i]["������ѧ��"];
		cout << " ������" << of.m_orderData[i]["����������"];
		cout << " ������" << of.m_orderData[i]["�����"];
		string status = " ״̬��";
		// 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ -1 ԤԼʧ��
		if (of.m_orderData[i]["ԤԼ״̬"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["ԤԼ״̬"] == "2")
		{
			status += "�ɹ�";
		}
		else if (of.m_orderData[i]["ԤԼ״̬"] == "-1")
		{
			status += "ʧ�ܣ����δͨ��";
		}
		else
		{
			status += "��ȡ��";
		}
		cout << status << endl;
	}
	system("pause");
}

void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		return;
	}
	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
	//���ڴ洢����кͳɹ��������±�
	vector<int> idx;
	//�����������Ļ�Ŀ�ȡ������������
	int index = 0;
	for (int i = 0; i < of.m_Size; i++) {
		if (atoi(of.m_orderData[i]["������ѧ��"].c_str()) == this->m_Id) {
			if (of.m_orderData[i]["ԤԼ״̬"] == "1" || of.m_orderData[i]["ԤԼ״̬"] == "2") {
				//���������Ҫ������ݵ��±����idx����
				idx.push_back(i);
				cout << ++index << "�� ";
				cout << "ԤԼ���ڣ� ��" << of.m_orderData[i]["����"];
				cout << " ʱ�Σ�" << (of.m_orderData[i]["ʱ��"] == "1" ? "����" : "����");
				cout << " ������" << of.m_orderData[i]["�����"];
				string status = " ״̬�� "; 
				// 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ  -1 ԤԼʧ��
				if (of.m_orderData[i]["ԤԼ״̬"] == "1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["ԤԼ״̬"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}
	cout << "������ȡ���ļ�¼,0������" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= idx.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				//	cout << "��¼����λ�ã� " << v[select - 1] << endl;
				of.m_orderData[idx[select - 1]]["ԤԼ״̬"] = "0";
				of.updateOrder();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}

		}
		cout << "������������������" << endl;
	}
	system("pause");
}
