#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

void printMainMenu() {
	cout << "---���ȭ---" << endl;
	cout << "--1.ʯͷ" << endl;
	cout << "--2.����" << endl;
	cout << "--3.��" << endl;
	cout << "------------" << endl;
}

void isWin() {
	int playerSel;
	cin >> playerSel;
	srand((unsigned int)time(NULL));
	int aiSel = rand() % 3 + 1;
	if (playerSel == aiSel) {
		cout << "ƽ��" << endl;
	}
	else if ((playerSel + 1 == aiSel) || (playerSel == 3 && aiSel == 1)) {
		cout << "��Ӯ�ˣ�" << endl;
	}
	else {
		cout << "������" << endl;
	}
}


int main() {
	while (true)
	{
		printMainMenu();
		isWin();
		system("pause");
		system("cls");
	}

	return 0;
}
