#include<stdio.h>
#include<stdbool.h>
#define BUFSIZE 128

void openAndClose() {
	//r read ֻ��������д�����ļ����������ʧ��
	//w write ֻд�����ܶ������ļ���������ᴴ���ļ�������������������
	//a append ׷��ֻд�����ܶ�������ļ��������򴴽��ļ������������������ĩβ׷������
	
	FILE* fp = fopen("1.txt", "r");
	if (!fp) {
		perror("open failed");
		return;
	}

	fclose(fp);
}

//�ַ���
void charRead() {
	FILE* fp = fopen("charRead.txt", "r");
	if (!fp) {
		perror("open failed");
		return;
	}
	int ch = fgetc(fp);
	if (ch == EOF) {
		perror("read failed");
	}
	else {
		printf("%c", ch);
	}

	//��������ȫ��������
	//1��
	//while (true) {
	//	ch = fgetc(fp);
	//	if (ch == EOF) {
	//		break;
	//	}
	//	putchar(ch);
	//}

	//2.
	while ((ch = fgetc(fp)) != EOF) {
		putchar(ch);
	}

	fclose(fp);
}

//�ַ�д
void charWrite() {
	FILE* fp = fopen("charRead.txt", "w");
	if (!fp) {
		perror("open failed");
		return;
	}
	
	//дһ���ַ�
	fputc('#', fp);

	//д����ַ�
	for (int i = 0; i < 26; i++)
	{
		fputc('A' + i, fp);
	}

	fclose(fp);
}

//��Ҫд����Ҫ��(��ò�Ҫ����)
void charReadWrite() {
	FILE* fp = fopen("charRead.txt", "w+");
	if (!fp) {
		perror("open failed");
		return;
	}
	int ch;
	//д�㶫��
	fputc('A', fp);
	//�����ļ�λ��ָ�뵽�ļ��Ŀ�ͷ
	rewind(fp);
	//������
	if ((ch = fgetc(fp)) != EOF) {
		printf("succeed  %c", ch);
	}
	else {
		printf("read failed");
	}

	fclose(fp);
}

//�ַ�����
void strRead() {
	FILE* fp = fopen("strRead.txt", "r");
	if (!fp) {
		perror("open failed");
		return;
	}

	char buf[BUFSIZE] = { 0 };
	if (!fgets(buf, BUFSIZ, fp)) {
		printf("str read failed!\n");
	}
	else {
		puts(buf);
	}

	fclose(fp);

}

//�ַ���д
void strRead() {
	FILE* fp = fopen("strRead.txt", "w");
	if (!fp) {
		perror("open failed");
		return;
	}

	if (0 != fputs("hello World!", fp)) {
		perror("write error");
	}

	fclose(fp);

}

int main() {

	//openAndClose();
	//charRead();
	//charWrite();
	//charReadWrite();
	strRead();

	return 0;
}