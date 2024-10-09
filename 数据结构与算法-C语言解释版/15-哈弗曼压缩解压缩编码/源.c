#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include"res.h"

//day16-04

/*
������(huffman)��������Ϊ�������������������Ч�����
	����Ƶ�ʸߵģ�������ڵ��,��Ӧ�Ĺ����������
	����Ƶ�ʵ͵ģ�������ڵ�Զ����Ӧ�Ĺ��������볤
	���������ݷŵ�Ҷ�ӽڵ㣬�����֧ȥһ�μ�0�����ҷ�֧ȥһ�μ�1
	������ù���������ȥ�������ݣ������ù����������������������ѹ�������

	ѹ����
		1.������ѹ���ļ�->�õ��ֵ�
			1.0�ļ�����
			1.1Ҫ֪���ж������ֽ�
			1.2֪��ÿ���ֽڳ��ֶ��ٴ�
		2.�����ֵ����ɹ�����������ȡÿ���ֽڶ�Ӧ�Ĺ���������
			�����������������д洢����1���������ң�2��������Ҷ�ӽڵ�ʹ洢
		3.����ѹ���ļ����ֵ�д�룩����ȡ��ѹ���ļ���һ��һ���ֽڵĻ�ȡ��Ӧ�ı��루������λ��ƴ�ӳ��ֽڲ�д�뵽ѹ�����ļ���
		4.�������д���ˣ��ر��ļ�����

	��ѹ��
		1.��ѹ�����ļ��а��ֵ������
		2.�����ֵ����ɹ�������
		3.ѭ����ѹ�����ļ��ж�ȡ�ֽ�
			3.1һ��������λ������ȥ������������
			3.2�ҵ�һ��Ҷ�ӽڵ㣬�͵õ�һ���ֽڵĽ�ѹ������ݣ�˳��д���ѹ����ļ���
			3.3�����ȡ��ϣ�����û�к����˻�����������ң��ͽ���
*/

//������ѹ���ļ����õ��ֵ�
void analysisFile(char* srcFile, struct AllZiFu* pZd) {
	//����
	if (NULL == srcFile || NULL == pZd)return ;

	//1.���ļ�
	FILE* fp = fopen(srcFile, "rb");
	if (NULL == fp) {
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	//2.ѭ����ȡ
	//���������ֽڴ�������
	unsigned char c;
	int r;
	//���ֵ����Ƿ���ڵı�ǣ�Ĭ�ϲ�����
	bool exist = false;
	int i;
	while (true)
	{
		r = fread(&c, 1, 1, fp);
		if (r < 1)break;
		//3.���ֵ����Ƿ��������ַ�
		
		for (i = 0; i < pZd->num; i++)
		{
			if (c == pZd->arr[i].zf) {
				exist = true;
				break;
			}
		}
		//����	���ִ���+1
		if (exist) {
			pZd->arr[i].cnt++;
			exist = false;
		}
		else {//������	��ӵ��ֵ���
			pZd->arr[pZd->num].zf = c;
			pZd->arr[pZd->num].cnt++;
			pZd->num++;
		}

		
	}
	
	//4.�ر��ļ�
	fclose(fp);
}

//�������ڵ�
struct node* createNode(struct ZiFu* pZf) {
	struct node* pNew = malloc(sizeof(struct node));
	if (NULL == pNew) {
		return NULL;
	}
	memset(pNew, 0, sizeof(struct node));
	memcpy(&(pNew->data), pZf, sizeof(struct ZiFu));
	return pNew;
}

//�����ֵ乹����������
struct node* createHaffmanTree(struct AllZiFu* pZd) {
	//׼��������
	struct node** pArray = (struct node**)malloc(pZd->num * (sizeof(struct node*)));
	if (NULL == pArray)return NULL;

	for (int i = 0; i < pZd->num; i++)
	{
		pArray[i] = createNode(&(pZd->arr[i]));
		pArray[i]->data.idx = i;//�����±�
	}

	int minIdx, secMinIdx;
	int j;
	struct node* pTemp = NULL;
	//ѭ����
	for (int i = 0; i < pZd->num-1; i++)
	{
		//1.�ҵ�����Ƶ����͵�
		//�����һ����С
		j = 0;
		while (pArray[j] == NULL)j++;//�ҵ���һ��
		minIdx = j;

		for ( j = 0; j < pZd->num; j++)//������������
		{
			if (pArray[j] &&
				pArray[j]->data.cnt < pArray[minIdx]->data.cnt) {
				minIdx = j;
			}
		}

		//2.�ҵ�����Ƶ�ʵڶ��͵�
		j = 0;
		while (pArray[j] == NULL||j==minIdx)j++;//�ҵ��ڶ���
		secMinIdx = j;

		for (j = 0; j < pZd->num; j++)//������������
		{
			if (pArray[j] &&
				j!=minIdx&&
				pArray[j]->data.cnt < pArray[secMinIdx]->data.cnt) {
				secMinIdx = j;
			}
		}

		//3.�����

		//���ɸ��ڵ�
		struct ZiFu tempZf = { 0,pArray[secMinIdx]->data.cnt + pArray[minIdx]->data.cnt };
		tempZf.idx = -1;
		pTemp = createNode(&tempZf);
		//����
		pTemp->pL = pArray[minIdx];
		pTemp->pR = pArray[secMinIdx];
		pArray[minIdx]->pParent = pTemp;
		pArray[secMinIdx]->pParent = pTemp;

		//4.������ɾ������Ƶ����͵ĺͳ���Ƶ�ʵڶ��͵ģ�����µĸ��ڵ�
		pArray[minIdx] = pTemp;//��ɾ������СƵ�ʽڵ�������˸��ڵ�
		pArray[secMinIdx] = NULL;
	}
	

	//5.���ظ��ڵ�
	return pTemp;
}

//�ж��Ƿ�ΪҶ�ӽڵ�
bool isLeaf(struct node* root) {
	if (root && NULL == root->pL && NULL == root->pR) return true;
	return false;
}

//����haffman����
void setHaffmanCode(struct node* root, char* haffmanCode) {
	char buff[HFM_CODE_LEN] = { 0 };
	int idx = 0;
	//root ѭ���Ҹ�
	while (root->pParent)
	{
		//�������ж����丸�����ӻ����Һ��ӣ��浽������
		if (root == root->pParent->pL) {//������
			buff[idx++] = 1;
		}
		else {//���Һ���
			buff[idx++] = 2;
		}


		root = root->pParent;
	}
	

	//��ת��д��haffmanCode������
	for (int i = 0; i < idx; i++)
	{
		haffmanCode[i] = buff[idx - i - 1];
	}
}

//���ݹ��������õ����������벢д���ֵ���
void createHaffmanCode(struct node* root, struct AllZiFu* pZd) {
	int idx;
	if (root) {
		if (isLeaf(root)) {//˵����Ҷ�ӽڵ�
			idx = root->data.idx;
			setHaffmanCode(root, pZd->arr[idx].code);
		}
		else {//����Ҷ�ӽڵ�
			createHaffmanCode(root->pL, pZd);
			createHaffmanCode(root->pR, pZd);
		}
	}
}

//���ֵ��У��õ�һ���ַ���Ӧ�Ĺ���������
void getHaffmanCode(char c, char* haffmanCode, struct AllZiFu* pzd) {
	for (int i = 0; i < pzd->num ; i++)
	{
		if (c == pzd->arr[i].zf) {
			strcpy(haffmanCode, pzd->arr[i].code);
			return;
		}
	}
}

//������ѹ���ļ������Ѵ�ѹ���ļ����ַ���Ӧ�Ĺ���������д��ѹ������ļ���
void writeCompressFile(const char* srcFile, const char* dstFile, struct ALLZiFu* pzd) {
	//1.�򿪴�ѹ���ļ� ����ѹ�����ļ�
	FILE* fpSrc = fopen(srcFile, "rb");
	FILE* fpDist = fopen(dstFile, "wb");
	if (NULL == fpDist || NULL == fpSrc)return;

	//2.д���ֵ�
	fwrite(pzd, 1, sizeof(struct AllZiFu), fpDist);

	//3.ѭ������ѹ���ļ� ����ѭ������
	char c;//�洢�������ֽ�
	int r;

	char charForWrite;//����д����ֽڣ�һ��������λƴ������
	char idxForWrite;//charForWrite���������±꣩

	char haffmanCode[HFM_CODE_LEN] = {0};//��ʱ�洢hfm����
	int idxForHaffmanCode = 0;

	bool isEnd = false;//����Ƿ����

	while (1) {
		if (0 == haffmanCode[idxForHaffmanCode]) {//��Ҫ����ʱ���ٶ�
			r = fread(&c, 1, 1, fpSrc);
			if (r < 1) {
				break;
			}

			getHaffmanCode(c, haffmanCode, pzd);//���ֵ��л�ȡC�ַ���Ӧ��haffman���룬��д�뵽 haffmanCode ������
			idxForHaffmanCode = 0;

		}
		
		//4.�õ��ַ���Ӧ�ı��룬ƴ�ɶ������ֽڣ����˸�����λд��һ��
		charForWrite = 0;
		idxForHaffmanCode = 0;
		idxForWrite = 0;
		while (idxForHaffmanCode<8)
		{
			if (2 == haffmanCode[idxForHaffmanCode]) {//���ö�Ӧ����λΪ0
				charForWrite &= ~(1 << (7 - idxForWrite));

				idxForHaffmanCode++;
				idxForWrite++;
			}
			else if (1 == haffmanCode[idxForHaffmanCode]) {//���ö�Ӧ����λΪ1
				charForWrite |= (1 << (7 - idxForWrite));

				idxForHaffmanCode++;
				idxForWrite++;
			}
			else {//��ǰ�ֽڶ�Ӧ��haffman�����Ѿ�������
				r = fread(&c, 1, 1, fpSrc);
				if (r < 1) {
					isEnd = true;
					break;
				}
				getHaffmanCode(c, haffmanCode, pzd);//���ֵ��л�ȡC�ַ���Ӧ��haffman���룬��д�뵽 haffmanCode ������
				idxForHaffmanCode = 0;
			}
		}//end of while (idxForHaffmanCode<8)
		//��8������λ��дһ��
		fwrite(&charForWrite, 1, 1, fpDist);

		for (int i = 0; i < 8; i++)
		{
			if (charForWrite & 0x80) {
				printf("1");
			}
			else {
				printf("0");
			}
			charForWrite <<= 1;
		}

		if (isEnd)break;
	}//end of while (1)


	//5.�رձ���
	fclose(fpDist);
	fclose(fpSrc);
}

int main() {
	//��ѹ���ļ���  1.txt  aaaaaabbbbbbbbbbbcccdedefghabchhh

	//�����ֵ�ṹ��
	struct AllZiFu zd = { 0 };

	analysisFile("1.txt", &zd);

	struct node* tree = createHaffmanTree(&zd);

	createHaffmanCode(tree, &zd);

	writeCompressFile("1.txt", "2.txt", &zd);

	while (1);
	return 0;
}
