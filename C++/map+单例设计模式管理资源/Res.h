#pragma once
#include"graphics.h"
#include<iostream>
#include"string"
#include<map>

using namespace std;

class Res{
public:
	~Res();
	//ʵ�ֵ���ģʽ�Ĺؼ���
	static Res* GetRes();
	//��Դ����
	//����ͼƬ
	static map<string, IMAGE*> layout; 
	//����ͼƬ
	static map<string, pair<int,IMAGE*>> action;
	static void ShowLayout(int x,int y,string name);
	static void ShowAction(int x,int y,string name,int frame);
private:
	Res();
};
