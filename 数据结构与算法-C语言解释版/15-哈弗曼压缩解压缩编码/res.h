#pragma once
//���������볤������
#define HFM_CODE_LEN 10

//�ַ�����
struct ZiFu {
	//�洢�ַ�����
	unsigned char		zf;
	//���ַ��ĳ��ִ���
	unsigned int		cnt;
	//����������
	char				code[HFM_CODE_LEN];
	//�����±�
	int					idx;
};

//�ֵ�����
struct AllZiFu {
	//�ܹ����ַ�����
	int num;
	//ÿ���ַ�����Ϣ���ַ�����,�ַ��������256�֣�
	struct ZiFu arr[256];
};

//���Ľڵ�����
struct node
{
	struct ZiFu data;
	struct node* pParent;
	struct node* pL;
	struct node* pR;
};
