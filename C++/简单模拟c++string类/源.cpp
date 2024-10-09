#include<string>
#include<cstring>
#include<iostream>

using namespace std;

class my_string {
public:
	//ʵ����ͨ����
	my_string() {
		pstr = nullptr;
		curSize = 0;
	}
	my_string(const char* str) {
		curSize = strlen(str);
		pstr = new char[curSize+1];
		strcpy_s(pstr, curSize+1, str);
	}
	//ʵ�ֿ�������
	my_string(const my_string& object) :my_string(object.pstr) {

	}
	char* c_str() {
		return pstr;
	}
	char* data() {
		return pstr;
	}
	bool empty() const {
		return curSize == 0;
	}
	int size()const {
		return curSize;
	}
	~my_string() {
		cout << "�ɹ��ͷ�" << endl;
		delete[] pstr;
	}
	//���������
	void operator=(const my_string& obj) {
		curSize = obj.curSize;
		pstr = new char[curSize + 1];
		strcpy_s(pstr, curSize + 1, obj.pstr);
	}
	friend ostream& operator<<(ostream& out,const my_string&obj) {
		out << obj.pstr;
		return out;
	}
	friend istream& operator>>(istream& in,my_string& obj) {
		char temp[1024];
		in >> temp;
		obj = my_string(temp);
		return in;
	}
	char operator[](int index) {
		return pstr[index];
	}
public:
	char* begin() {
		return pstr;
	}
	char* end() {
		return pstr + curSize;
	}
	class iterator
	{
	public:
		iterator(char* pmove) :pmove(pmove) {

		}
		bool operator!=(char* pmove) {
			return this->pmove != pmove;
		}
		iterator operator++() {
			return iterator(++pmove);
		}
		char operator*() {
			return pmove[0];
		}
	protected:
		char* pmove;
	};
public:
	//�Ƚ�
	bool operator==(const my_string&obj ) const{
		return strcmp(this->pstr, obj.pstr) == 0;
	}
	bool operator>(const my_string& obj) const {
		return strcmp(this->pstr, obj.pstr) > 0;
	}
	bool operator<(const my_string& obj) const {
		return strcmp(this->pstr, obj.pstr) < 0;
	}
	//����
	my_string operator+(const my_string& obj) {
		int length = obj.curSize + this->curSize + 1;
		char* pstr = new char[length];
		memset(pstr, 0, length);
		if (this->pstr != NULL) {
			strcat_s(pstr, length, this->pstr);
		}
		if (this->pstr != NULL) {
			strcat_s(pstr, length, obj.pstr);
		}
		return move(my_string(pstr));
	}
protected:
	char* pstr;
	int curSize;
};

int main() {
	//��ͨ����
	my_string str = "this is my string";
	my_string str1("this is my str1");
	//��������
	my_string str2 = str;
	my_string str3(str1);
	//��Ա����
	cout <<str.c_str()<<" " << str.data() << " " << str.size() << " " << str.empty() << endl;
	cout << str3.c_str() << " " << str3.size() << " " << str3.empty() << endl;
	//���������
	my_string str4;
	str4 = str3;
	str4 = "this is str4";
	cout << str4.c_str() << " " << str4.data() << " " << str4.size() << " " << str4.empty() << endl;
	cout << str4 << endl;
	my_string str5;
	cin >> str5 ;
	cout << str5 << endl;
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i];
	}cout << endl;
	//���������
	for (my_string::iterator pstr = str.begin(); pstr != str.end(); ++pstr) {
		cout << *pstr;
	}
	cout << endl;
	//�Ƚ�����
	cout << (str5 == str4) << endl;
	//��������
	my_string first = "I Love You";
	my_string sec = "XiaoBai";
	my_string result = first + sec;
	cout << result << endl;
	return 0;
}
