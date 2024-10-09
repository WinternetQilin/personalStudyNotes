#include <regex> //������ʽͷ�ļ�
#include <fstream> //�ļ�����ͷ�ļ�
#include <iostream>
#include <string>
#include <queue>//��������
#include <map>//�����ַ�ظ�����
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")//���ض�̬��   ��Դ����Ū����
#include <windows.h>

using namespace std;
//http://www.netbian.com/s/meinvmm/
 

//��ַ       ����
map<string, int> g_map;//�����ַ�ظ�����
//���������
char g_zhuji[256] = { 0 };
//����������·��
char g_path[256] = { 0 };
//������socket
SOCKET g_socket;
//���ͼƬ��ַ������
vector<string> photoAddr;
//�����ҳ��ַ������
vector<string> htmlAddr;

//��jpgͼƬ
void snapJpg(const char* addr);

//������ַ
void jiexiAddr(char* buff);
//���ӷ�����
void connectAddr();
//�õ�Դ����
void getHtml();
//����ͼƬ
void saveImage(string str);
//����ҳԴ�����л�ȡͼƬ����
void getImage(string& allHtml);
//����ҳԴ�����л�ȡ��ַ����
void getAddr(string& allHtml);

int main() {

	string begAddr;
	cout << "��������ʼ��ַ:";
	cin >> begAddr;

	//����һ���ļ���
	CreateDirectory(".\\images", NULL);

	snapJpg(begAddr.c_str());
	while (1);
	return 0;
}


//��jpgͼƬ
void snapJpg(const char* addr) {
	queue<string> q;//����ַ
	q.push(addr);//����ʼ��ַ�Ž�ȥ

	while (!q.empty()) {
		//��q���ó�һ�� 
		string currentAddr = q.front();
		//ɾ��
		q.pop();
		//�����ַ�ظ�����
		g_map[currentAddr]++;
		//������ַ �õ�����
		char buff[256] = { 0 };
		strcpy(buff, currentAddr.c_str());
		//������ַ
		jiexiAddr(buff);
		//���ӷ�����
		connectAddr();
		//�õ�Դ����
		getHtml();
#if 1
		//��Դ�����н�������ַ��ͼƬ��ַ �����Ӧ������
		//����ַ��ŵ�����q��
		vector<string>::iterator it;
		for (it = htmlAddr.begin(); it != htmlAddr.end(); it++) {
			if (0 == g_map[*it]) {//û�����ӹ�
				q.push(*it);//�ŵ�������
			}
		}
		htmlAddr.clear();//�������
		//����ͼƬ
		for (it = photoAddr.begin(); it != photoAddr.end(); it++) {
			saveImage(*it);
		}
		photoAddr.clear();//�������
#else
		while (1);
#endif
	}
}

//������ַ
void jiexiAddr(char* buff) {
	char temp[256] = { 0 };
	strcpy(temp, buff);

	//�Թ�ǰ���߸� http://
	char* p = strstr(buff, "http://");//buff�����Ӵ� "http://" �ҵ������Ӵ��׵�ַ
	if (NULL == p) return;
	else
		p += 7;//����Ų�߸�

	sscanf(p, "%[^/]%s", g_zhuji, g_path);
	printf("������%s\n", g_zhuji);
	printf("·����%s\n", g_path);
}
//���ӷ�����
void connectAddr() {
	//1 ��ȡЭ��汾��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2) {
		printf("����汾��ʧ�ܣ�\n");
		return;
	}
	printf("����汾�ųɹ���\n");
	//2 ����socket
	g_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == g_socket) {
		printf("����socketʧ��!\n");
		return;
	}
	printf("����socket�ɹ�!\n");
	//3 ����Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET; //�����socket������һ������һ��
	//4 ��
	int r = bind(g_socket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("��ʧ��!\n");
		return;
	}
	printf("�󶨳ɹ���\n");
	//5 �õ�����ip��ַ
	struct hostent* p = gethostbyname(g_zhuji);//192.168.0.44    ipv4
	if (NULL == p) {
		printf("��ȡ������ַʧ��!\n");
		return;
	}
	printf("��ȡ������ַ�ɹ�!\n");

	memcpy(&addr.sin_addr, p->h_addr, 4);	//��������ַ����Э���ַ����
	addr.sin_port = htons(80);				//���������˿ں�   ������˿ں�һ��Ϊ80

	//6 ���ӷ�����
	r = connect(g_socket, (sockaddr*)&addr, sizeof addr);
	if (-1 == r) {
		printf("���ӷ�����ʧ��!\n");
		return;
	}
	printf("���ӷ������ɹ���\n");
	//7 ͨ�ţ����ͻ�ȡԴ��������

	//������Ϣ
	string reqInfo = "GET " + (string)g_path + " HTTP/1.1\r\nHost:" +
		(string)g_zhuji + "\r\nConnection:Close\r\n\r\n";
	//����������Ϣ��������
	r = send(g_socket, reqInfo.c_str(), reqInfo.size(), NULL);
	if (r > 0) {
		printf("����������Ϣ�ɹ�!\n");
	}
	else {
		printf("����������Ϣʧ�ܣ�ʧ��ԭ��%d\n", WSAGetLastError());
	}

}
//�õ�Դ����
void getHtml() {
	string allHtml;

	char buff[1024];
	int r;
	while (1) {
		r = recv(g_socket, buff, 1023, NULL);
		if (r > 0) {
			buff[r] = 0;
			allHtml += buff;
		}
		else {
			break;
		}
	}

	cout << allHtml << endl;

	//����ҳԴ�����л�ȡͼƬ����
	getImage(allHtml);
	//����ҳԴ�����л�ȡ��ַ����
	getAddr(allHtml);
}
//����ͼƬ
void saveImage(string str) {
	//1 ����ͼƬ��ַ
	char buff[256];
	memset(buff, 0, 256);
	strcpy(buff, str.c_str());

	jiexiAddr(buff);
	//2 ���ӷ�����
	//3 ��������ͼƬ����
	connectAddr();
	//4 ���ش���ͼƬ�ļ�
	//4.1 �õ�ͼƬ�ļ���
	string photoName;
	photoName.resize(str.size());

	char ch;
	int j = 0;
	for (int i = 0; i < str.length(); i++) {
		ch = str[i];
		// '\0'  '\n' '\t' '\r' '\\' '\"'
		if (ch != '\\' && ch != '/' && ch != ':' && ch != '*' && ch != '?' &&
			ch != '"' && ch != '<' && ch != '>' && ch != '|') {
			photoName[j++] = ch;
		}
	}

	photoName = "./images/" + photoName.substr(0, j);

	//4.2 ����ͼƬ�ļ�
	fstream file;
	file.open(photoName, ios::out | ios::binary);//������д

	//5 ���շ��͹�����ͼƬ��Ϣ��д��ͼƬ�ļ���
	int r;
	char tempBuff[1024] = { 0 };

	//�ų����ļ�ͷ��"\r\n\r\n"
	r = recv(g_socket, tempBuff, 1023, NULL);
	char* p = strstr(tempBuff, "\r\n\r\n");
	file.write(p + strlen("\r\n\r\n"), r - (p - tempBuff) - strlen("\r\n\r\n"));

	while (1) {
		r = recv(g_socket, tempBuff, 1023, NULL);
		if (r > 0) {
			file.write(tempBuff, r);
		}
		else {
			break;
		}

	}
	//6 ����ر�
	file.close();

}

//����ҳԴ�����л�ȡͼƬ����
void getImage(string& allHtml) {
	smatch mat;//����ƥ��Ķ���
	regex pattren("src=\"(.*?\\.jpg)\"");
	string::const_iterator start = allHtml.begin();//��ʼλ��
	string::const_iterator end = allHtml.end();//����λ��

	while (regex_search(start, end, mat, pattren)) {
		string msg(mat[1].first, mat[1].second);
		photoAddr.push_back(msg);
		cout << "�ҵ�ͼƬ��" << msg << endl;
		start = mat[0].second;//�ı���ʼλ��
	}
}
//����ҳԴ�����л�ȡ��ַ����
void getAddr(string& allHtml) {
	smatch mat;//����ƥ��Ķ���
	regex pattren("href=\"(http://[^\\s,\"]+)\"");
	string::const_iterator start = allHtml.begin();//��ʼλ��
	string::const_iterator end = allHtml.end();//����λ��

	while (regex_search(start, end, mat, pattren)) {
		string msg(mat[1].first, mat[1].second);
		htmlAddr.push_back(msg);
		cout << "�ҵ���ַ��" << msg << endl;
		start = mat[0].second;//�ı���ʼλ��
	}
}