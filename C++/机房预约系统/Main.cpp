#include<iostream>
#include<fstream>
#include<string>
#include"globalFile.h"


using namespace std;

//��¼����
void login(string fileName, int type);
//����Ա�˵�
void managerMenu(Identity* &manager);
//ѧ���˵�
void studentMenu(Identity*& student);
//��ʦ�˵�
void teacherMenu(Identity*& teacher);

int main() {
	//�û�ѡ��
	int select = 0;
	while (true)
	{
		system("cls");
		cout << "========================  ����ԤԼϵͳ  ====================="<< endl;
		cout << "\t\t ---------��ѡ���������--------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.ѧ    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.��    ʦ           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "��������ѡ��: ";
		cin >> select;
		switch (select)
		{
		case 0://�˳�
			cout << "��ӭ�´�ʹ�ã�" << endl;
			exit(0);
			break;
		case 1://ѧ��
			login(STUDENT_FILE, 1);
			break;
		case 2://��ʦ
			login(TEACHER_FILE, 2);
			break;
		case 3://����Ա
			login(ADMIN_FILE, 3);
			break;
		default:
			cout << "�޴�ѡ����������룡" << endl;
			system("pause");
			break;
		}
	}

	return 0;
}

void login(string fileName, int type)
{
	//����Ҫ���������
	int id = 0;//ѧ�� �� ְ����
	string name;//�û���
	string pwd;//����
	//������ļ��ж�ȡ��ѧ�ţ�����������
	int fId;
	string fName;
	string fPwd;
	//����һ���˻���ָ��
	Identity* person = NULL;

	//�򿪶�Ӧ�ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		system("pause");
		ifs.close();
		return;
	}

	//ͨ��type�ж�id������� ѧ�� ���� ְ���� ���� �����루����Ա��¼��
	if (1 == type)	//ѧ����¼
	{
		cout << "���������ѧ�ţ�";
		cin >> id;
	}
	else if (2 == type) //��ʦ��¼
	{
		cout << "���������ְ���ţ�";
		cin >> id;
	}
	//����˭��¼��Ҫ���� �û��� �� ����
	cout << "�������û�����";
	cin >> name;
	cout << "���������룺";
	cin >> pwd;

	//���������ж�Ӧ�ĵ�¼��֤
	if (type == 1)
	{
		//ѧ����¼��֤
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			//cout << fId << " " << fName << " " << fPwd << endl;
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "ѧ����֤��¼�ɹ�!" << endl;
				system("pause");
				//ѧ����½�����Ը�newһ��ѧ���࣬����¼�˵���Ϣ�Ž�ȥ
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2)
	{
		//��ʦ��¼��֤
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "��ʦ��֤��¼�ɹ�!" << endl;
				system("pause");
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա��¼��֤
		while (ifs >> fName && ifs >> fPwd) {
			if (name == fName && pwd == fPwd)
			{
				cout << "����Ա��֤��¼�ɹ�!" << endl;
				system("pause");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	//����˵����¼��֤ʧ����
	cout << "��֤��¼ʧ��!" << endl;
	system("pause");

	//�ǵùر��ļ�
	ifs.close();
	return;
}

void managerMenu(Identity*& manager)
{
	//��Ϊmanager��Identity�࣬Manager��Ĺ��ܺ���û�У�������Ҫת��Manager��
	Manager* mg = (Manager*)manager;
	//�û������ѡ��
	int select;
	//����ѭ����
	bool show = true;

	while (show)
	{
		//���ù�����Ĳ˵�
		mg->operMenu();
		//��ʼѡ��
		cin >> select;
		switch (select)
		{
		case 0:
			delete mg;
			cout << "ע���ɹ�" << endl;
			system("pause");
			show = false;
			break;
		case 1:
			mg->addPerson();//����˺�
			break;
		case 2:
			mg->showPerson();//�鿴�˺�
			break;
		case 3:
			mg->showComputer();//�鿴����
			break;
		case 4:
			mg->cleanFile();//���ԤԼ
			break;
		default:
			cout << "�޴�ѡ����������룡" << endl;
			system("pause");
			break;
		}

	}
}

void studentMenu(Identity*& student)
{
	Student* stu = (Student*)student;
	//�û������ѡ��
	int select;
	//����ѭ����
	bool show = true;

	while (show)
	{
		//���ù�����Ĳ˵�
		stu->operMenu();
		//��ʼѡ��
		cin >> select;
		switch (select)
		{
		case 0:
			delete stu;
			cout << "ע���ɹ�" << endl;
			system("pause");
			show = false;
			break;
		case 1:
			stu->applyOrder();//����ԤԼ
			break;
		case 2:
			stu->showMyOrder();//�鿴�ҵ�ԤԼ
			break;
		case 3:
			stu->showAllOrder();//�鿴����ԤԼ
			break;
		case 4:
			stu->cancelOrder();//ȡ��ԤԼ
			break;
		default:
			cout << "�޴�ѡ����������룡" << endl;
			system("pause");
			break;
		}
	}
}

//��ʦ�˵�
void teacherMenu(Identity*& teacher)
{
	Teacher* t = (Teacher*)teacher;
	while (true)
	{
		//��ʦ�˵�
		t->operMenu();

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//�鿴����ԤԼ
			t->showAllOrder();
		}
		else if (select == 2)
		{
			//���ԤԼ
			t->validOrder();
		}
		else
		{
			delete t;
			cout << "ע���ɹ�" << endl;
			system("pause");
			return;
		}

	}
}