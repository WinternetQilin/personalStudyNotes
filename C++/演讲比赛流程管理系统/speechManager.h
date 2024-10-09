#pragma once
#include"speaker.h"
#include<vector>
#include<map>
#include<iostream>

using namespace std;

class speechManager
{
public:
	//����
	speechManager();
	//�˵�չʾ
	void showMenu();
	//����
	~speechManager();

	//��Ա����
	//�����һ�ֱ���ѡ�ֱ������
	vector<int> v1;
	//�ڶ��ֱ���ѡ�ֱ������
	vector<int> v2;
	//��������ǰ��������
	vector<int> vDone;
	//��ű�� �Լ���Ӧ�� ����ѡ�� ����
	map<int, speaker> m_speaker;
	//��¼�ִεļ�����
	int m_index;

	//�ļ�Ϊ�յı�־
	bool fileIsEmpty;
	//�����¼
	map<int, vector<string>> m_Record;
	
	//��ʼ������
	void initSpeech();
	//�����ʼ����һ�֣���12��������Ա
	void createSpeaker();
	//��ʼ��������
	void startSpeech();
	//���Ҳ�����Ա����ǩ����չʾ
	void speechDraw();
	//��ʼ��������
	void speechContest();
	//��ʾÿ�ֵĽ���ѡ��
	void showScore();
	//����ǰ�����ķ����������ļ�
	void scoreRecord();

	//��ȡ�ļ��еķ�����¼
	void loadSorce();
	//��ʾ����÷�
	void showRecord();
	////��ռ�¼
	void clearRecord();
};

