#include<iostream>
#include<math.h>

using namespace std;

bool weishu(long long int n) {
	if ((1000 <= n && n <= 9999) || (100000 <= n && n <= 999999) || (10000000 <= n && n <= 99999999) || (100000000 == n))return false;
	return true;
}

bool huiwen(long long int n) {
	long long int un = 0;
	long long int temp = n;
	//���жϸ�λ�ǲ���0.Ҫ��0�Ļ�ֱ�Ӿͷ���false����Ϊֻ��0��������Ļ���
	if (0 == n % 10) {
		return false;
	}
	while (temp) {
		un = un * 10 + (temp % 10);
		temp /= 10;
	}
	if (n == un) {
		return true;
	}
	else {
		return false;
	}
}

bool zhishu(long long int n) {
	for (long long int i = 2; i <= sqrt(n); i++) {
		if (0 == n % i) {
			return false;
		}
	}

	return true;
}

int main() {
	long long int a, b;
	cin >> a >> b;
	//��������ѭ������Ϊż���϶���������
	if (0 == a % 2) {
		a++;
	}
	for (long long int i = a; i <= b; i += 2)
	{
		if (weishu(i)) {
			if (huiwen(i)) {
				if (zhishu(i)) {
					cout << i << endl;
				}
			}
		}
	}
	return 0;
}