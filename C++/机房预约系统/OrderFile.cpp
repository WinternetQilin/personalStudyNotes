#include "OrderFile.h"
#include<fstream>

OrderFile::OrderFile()
{
	//��ԤԼ�ļ�
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string week;		//�ܼ�
	string day;			//ʱ��
	string stuId;		//������ѧ��
	string stuName;		//����������
	string roomId;		//��������
	string status;		//ԤԼ״̬
	this->m_Size = 0;	//ͳ��ԤԼ��¼����

	while (ifs >> week && ifs >> day && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//Ƭ���и�ʱ��ʱ��ŵı���
		string key;
		string value;
		map<string, string> m;
		//�и�
		int pos = week.find(":");
		if (pos != -1)
		{
			key = week.substr(0, pos);
			value = week.substr(pos + 1, week.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = day.find(":");
		if (pos != -1)
		{
			key = day.substr(0, pos);
			value = day.substr(pos + 1, day.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;//����һ��ԤԼ���ݾ���ͳ�������ı���++
	}// end of while (ifs >> week && ifs >> day && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	//���ǵùر��ļ�
	ifs.close();
}

void OrderFile::updateOrder()
{
	//���µ��ļ�
	//����ڴ���û�оͲ��ô���
	if (this->m_Size == 0)return;

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < m_Size; i++)
	{
		ofs << "����:" << this->m_orderData[i]["����"] << " ";
		ofs << "ʱ��:" << this->m_orderData[i]["ʱ��"] << " ";
		ofs << "������ѧ��:" << this->m_orderData[i]["������ѧ��"] << " ";
		ofs << "����������:" << this->m_orderData[i]["����������"] << " ";
		ofs << "�����:" << this->m_orderData[i]["�����"] << " ";
		ofs << "ԤԼ״̬:" << this->m_orderData[i]["ԤԼ״̬"] << endl;
	}
	ofs.close();
}
