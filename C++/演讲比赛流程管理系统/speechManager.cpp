#include "speechManager.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include <fstream>

using namespace std;

speechManager::speechManager()
{
	//��ʼ������
	this->initSpeech();
	//����������ʼʱ��ѡ��
	this->createSpeaker();
	//��ȡ�����¼
	this->loadSorce();
}

void speechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

speechManager::~speechManager()
{
}

void speechManager::initSpeech()
{
	//�������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vDone.clear();
	this->m_speaker.clear();
	this->m_index = 1;
	this->m_Record.clear();
}

void speechManager::createSpeaker()
{
	//׼�������������
	string nameSeed = "ABCDEFGHIJKL";
	//ѭ������
	for (int i = 0; i < nameSeed.size(); i++) {
		//����ѡ��
		speaker s;
		//��������
		string name = "ѡ��";
		name += nameSeed[i];
		s.m_name = name ;
		//cout << nameSeed[i];
		//��ʼ�����ַ�����������������ѭ���ˣ�
		s.m_score[0] = 0;
		s.m_score[1] = 0;
		//���뱾��ѭ���ĳ�Ա���
		this->v1.push_back(10001 + i);
		//���� ѡ�ֱ�� �� ѡ�� ��map��
		m_speaker.insert(make_pair(10001 + i, s));



	}
}

void speechManager::startSpeech()
{

	//��һ�ֱ���
	//1����ǩ
	speechDraw();
	//2������
	speechContest();
	//3����ʾ�������
	showScore();
	//4���ִ�++
	m_index++;

	//�ڶ��ֱ���
	//1����ǩ
	speechDraw();
	//2������
	speechContest();
	//3����ʾ�������(���ս��)
	showScore();
	//4���������
	scoreRecord();

	//ÿ�α�����Ҫ���ñ���
	//��ʼ������
	this->initSpeech();
	//����ѡ��
	this->createSpeaker();
	//���»�ȡ�ļ��е���ʷ��������
	this->loadSorce();

	//����
	cout << "�������������" << endl;
	system("pause");
	system("cls");

}

void speechManager::speechDraw()
{
	cout << "�� << " << this->m_index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	//���ж��ǵ�һ�ֻ��ǵڶ���
	vector<int>& v=v1;
	if (this->m_index == 2) {
		v = v2;
	}
	//��ʼ����������ı��
	random_shuffle(v.begin(), v.end());
	//��������
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) { 
		cout << *iter << " "; 
	}
	cout << endl;
	cout << "---------------------" << endl;
	system("pause");
}

void speechManager::speechContest() {
	cout << "------------- ��" << this->m_index << "����ʽ������ʼ��------------- " << endl;

	//��ʱ�������棬keyΪ������valueΪ������Ա��ţ����ݷ�����������(��Ҫ��Ϊ������)
	//keyΪ��������Ϊ���и���key���ģ���multimap����map����Ϊ����key�����ظ�
	multimap<double, int, greater<double>> scoreTemp;

	//�ж��ǵ�һ�ֻ��ǵڶ���
	vector<int>& v = v1;
	if (this->m_index == 2) {
		v = v2;
	}
	
	//����һ��������������ͳ���ѱ���������
	int cntPerosn = 0;

	//ѭ������������Աv
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) {
		//��ÿλѡ�ִ�֣�10-1-1��ȡƽ����
		//�ȴ���һ��˫��������ڼ�¼����
		deque<double> scores;
		//ѭ��10��ȡ�����ģ����
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; // 600 ~ 1000
			//cout << score << " ";
			scores.push_back(score);
		}
		//����-1-1ȡƽ����
		sort(scores.begin(), scores.end(), greater<double>());
		scores.pop_back();
		scores.pop_front();
		double average = (accumulate(scores.begin(), scores.end(), 0.0f) / 8.0);
		//��ƽ��ֵ�洢����Ӧѡ�ֵĶ�Ӧ�ִ���
		this->m_speaker[*iter].m_score[m_index - 1] = average;
		//˳�㽫ƽ��ֵ�ͳ�Ա��ŷŵ���ʱ��������������
		scoreTemp.insert(make_pair(average, *iter));
		//һ����Ա�ķ���Ū���ˣ�������++
		cntPerosn++;

		//����һ�飬�ж��Ƿ���6��
		if (cntPerosn % 6 == 0) {
			//��6���˾����һ��6�˵ı������
			if (this->m_index == 1) {
				cout << "��" << cntPerosn / 6 << "С��������Σ�" << endl;
			}
			for (multimap<double, int, greater<int>>::iterator it = scoreTemp.begin(); it
				!= scoreTemp.end(); it++)
			{
				cout << "���: " << it->second 
					<< " ������ " << this->m_speaker[it -> second].m_name 
					<< " �ɼ��� " << this->m_speaker[it->second].m_score[this->m_index - 1] 
					<<endl;
			}

			//ѭ��������ʱ������������ǰ��������v2��vDone����
			int count = 0;
			for (multimap<double, int, greater<int>>::iterator it = scoreTemp.begin();
				it != scoreTemp.end() && count < 3; it++, count++) {
				//�жϵ�һ�ֻ��ǵڶ���
				if (this->m_index == 1) {
					//6��3��v2
					v2.push_back((*it).second);

				}
				if (this->m_index == 2) {
					//6��3��vDone
					vDone.push_back((*it).second);
				}
			}

			//����ʱ������գ�������һ��6���˵ķ�����¼
			scoreTemp.clear();
			cout << endl;
			
		}
	}
	cout << "------------- ��" << this->m_index << "�ֱ������ ------------- " << endl;
	system("pause");
}

void speechManager::showScore()
{
	if (this->m_index == 1) {
		cout << "---------��" << this->m_index << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
	}
	else {
		cout << "---------�����������-----------" << endl;
	}
	vector<int>& v = v2;
	if (this->m_index == 2) {
		v = vDone;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << m_speaker[*it].m_name 
			<< " �÷֣� " <<m_speaker[*it].m_score[this->m_index - 1] 
			<< endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}

void speechManager::loadSorce()
{
	//���ķ�ʽ�򿪼�¼�ļ�
	ifstream ifs("speech.csv", ios::in); 
	//�ж��ļ��Ƿ�������
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	//��ȡһ���ַ��󣬿����ǲ��ǿ��ļ�����ֹ�ļ���ֻ�пո���߻��з����������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��!" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//��ȥ��������������ļ���Ϊ��
	this->fileIsEmpty = false;
	//�ٽ��ղŶ�ȡ�ĵ����ַ��Ż�ȥ
	ifs.putback(ch); 

	//���ڽ��մ��ļ��ж�ȡ���ַ���
	string scoreData;
	//����ͳ�ƽ���
	int index = 0;
	//ÿ�ζ�ȡһ������
	while (ifs >> scoreData) {
		//��ʼ�����ݽ��зָ�
		//���ڴ洢�ָ����ÿС��string��������
		vector<string> v;
		//��¼��ȡ����ʼλ��
		int start = 0;
		//��¼�ָ��λ��
		int pos = -1;

		//��ʼ��
		while (true)
		{
			//��start��ʼ���� ',' ����λ�ü�¼��pos��
			pos = scoreData.find(",", start); 
			//�Ҳ���break����
			if (pos == -1)
			{
				break; 
			}
			//�ҵ��Ļ�����ʼ�и�(����1 ��ʼλ�ã�����2 ��ȡ����)
			string temp = scoreData.substr(start, pos - start);
			//���и�Ƭ�η�������
			v.push_back(temp);
			//������ʼλ�õ��и����һλ����������Ѱ��
			start = pos + 1;
		}
		//��һ�ֵ�����󣬽�����v�����ݴ浽ȫ��������
		this->m_Record.insert(make_pair(index, v));
		//��������
		index++;
	}
	//������֮�󣬹ر��ļ�
	ifs.close();
}

void speechManager::showRecord()
{
	if (this->m_Record.empty()) {
		cout << "�������������" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "��" << i + 1 << "�� " <<
			"�ھ���ţ�" << this->m_Record[i][0] << "  �÷֣�" << this->m_Record[i][1] << endl;
		cout << "\t�Ǿ���ţ�" << this->m_Record[i][2] << "  �÷֣�" << this->m_Record[i][3] << endl;
		cout<<"\t  ������ţ�" << this->m_Record[i][4] << "  �÷֣�" << this->m_Record[i][5] << endl;
		cout << "--------------------" << endl;
	}
	system("pause");
	system("cls");
}

void speechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//��ʼ������
		this->initSpeech();
		//����ѡ��
		this->createSpeaker();
		//��ȡ�����¼
		this->loadSorce();
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

void speechManager::scoreRecord()
{
	fstream file;
	//��д��׷��д�ķ�ʽ���ļ�
	file.open("speech.csv", ios::out | ios::app);
	//��ǰ�����ķ���д���ļ�
	for (vector<int>::iterator it = vDone.begin(); it != vDone.end(); it++)
	{
		file << *it << ","<< m_speaker[*it].m_score[1] << ",";
	}
	file << endl;
	cout << "��¼�Ѿ�����" << endl;
	file.close();
}

