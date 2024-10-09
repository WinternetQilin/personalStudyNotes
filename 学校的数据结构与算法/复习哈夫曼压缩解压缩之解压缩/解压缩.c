#include "Res.h"

//�������ڵ�
struct Node* createNode(struct Zifu* pzf);

//�����ֵ䴴����������
struct Node* createHFMTree(struct Zidian* pzd);

//�ж��Ƿ���Ҷ�ӽڵ�
bool isLeaf(struct Node* pRoot);

int main()
{
	struct Zidian zd = { 0 };
	//�򿪴���ѹ�ļ�
	FILE* fpSrc = fopen("2.txt", "rb");//����ѹ�ļ�
	FILE* fpDst = fopen("3.txt", "wb");//��ѹ���ļ�
	//���ֵ������
	fread(&zd, 1, sizeof(struct Zidian), fpSrc);
	//�����ֵ����ɹ�������
	struct Node* pRoot = createHFMTree(&zd);

	int num_zf = pRoot->zf.cnt;
	char read_c;
	int idx_read_c;
	struct Node* pTemp = pRoot;
	while (1 == fread(&read_c, 1, 1, fpSrc) && num_zf > 0)
	{
		idx_read_c = 0;
		while (idx_read_c < 8)
		{
			//0x80 = 1000 0000
			if (read_c & (0x80>>idx_read_c))
			{
				pTemp = pTemp->pLeft;
			}
			else
			{
				pTemp = pTemp->pRight;
			}
			idx_read_c++;

			if (isLeaf(pTemp))
			{
				fwrite(&(pTemp->zf.zf), 1, 1, fpDst);
				pTemp = pRoot;//�Ӹ����¿�ʼ
				num_zf--;
				if (num_zf <= 0)break;
			}
		}//end of while (idx_read_c < 8)
	}//end of while (1 == fread(&read_c, 1, 1, fpSrc) && num_zf > 0)

	fclose(fpSrc);
	fclose(fpDst);
	while (1);

	return 0;
}

struct Node* createNode(struct Zifu* pzf)
{
	struct Node* pNew = calloc(1, sizeof(struct Node));
	if (NULL == pNew)return NULL;

	memcpy(&(pNew->zf), pzf, sizeof(struct Zifu));

	return pNew;
}

struct Node* createHFMTree(struct Zidian* pzd)
{
	//0 ׼�������飬��� ���ֵ����ַ�������ÿ���ӽڵ�ָ��
	struct Node** ppArr = calloc(pzd->zf_num, sizeof(struct Node*));
	if (!ppArr)return NULL;
	for (int i = 0; i < pzd->zf_num; i++)
	{
		ppArr[i] = createNode(&(pzd->zf_arr[i]));
		ppArr[i]->zf.idx = i;
	}
	// 
	// 1 ѭ������С��
	//		�ҵڶ�С��
	//		��������
	int minIdx, secMinIdx;
	struct Node* pTemp = NULL;
	for (int i = 0; i < pzd->zf_num - 1; i++)
	{
		//����С
		int j = 0;//�����һ����С
		while (ppArr[j] == NULL)j++;//�����սڵ�ĵ�һ��
		minIdx = j++;
		for (j; j < pzd->zf_num; j++)
		{
			if (ppArr[j] && ppArr[j]->zf.cnt < ppArr[minIdx]->zf.cnt)
			{
				minIdx = j;
			}
		}
		//�ҵڶ�С
		j = 0;
		while (ppArr[j] == NULL || j == minIdx)j++;
		secMinIdx = j++;
		for (j; j < pzd->zf_num; j++)
		{
			if (ppArr[j] && ppArr[j]->zf.cnt < ppArr[secMinIdx]->zf.cnt && j != minIdx)
			{
				secMinIdx = j;
			}
		}

		// 2 �����
		struct Zifu tempZf = { 0 };
		tempZf.cnt = ppArr[minIdx]->zf.cnt + ppArr[secMinIdx]->zf.cnt;
		tempZf.idx = -1;
		pTemp = createNode(&tempZf);
		pTemp->pLeft = ppArr[minIdx];
		pTemp->pRight = ppArr[secMinIdx];
		ppArr[minIdx]->pParent = pTemp;
		ppArr[secMinIdx]->pParent = pTemp;

		// 3 ��������ɾ���Ѿ�������������ڵ㣬������Ŀո��ڵ��������
		ppArr[minIdx] = pTemp;
		ppArr[secMinIdx] = NULL;

		// һֱ��ѭ������
	}

	// 4 ���ظ��ڵ㣬�����������ĸ��ڵ�
	return pTemp;
}

bool isLeaf(struct Node* pRoot)
{
	if (NULL != pRoot && NULL == pRoot->pLeft && NULL == pRoot->pRight)
	{
		return true;
	}
	return false;
}