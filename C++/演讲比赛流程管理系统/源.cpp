#include"speechManager.h"


int main(){
	
	speechManager sm;
	srand((unsigned int)time(NULL));

	//for (map<int, speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	//{
	//	cout << "ѡ�ֱ�ţ�" << it->first
	//		<< " ������ " << it->second.m_name
	//		<< "     �ɼ��� " << it->second.m_score[0] << endl;
	//}

	while (true)
	{
		sm.showMenu();
		int select;
		cout << "������ѡ��>";
		cin >> select;
		switch (select)
		{
		case 0:
			cout << "�����˳�����ӭ�´�ʹ��" << endl;
			exit(0);
			break;
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		default:
			cout << "��Чѡ�������ѡ��" << endl;
			break;
		}
		//system("pause");
		system("cls");
	}
	

	return 0;
}
