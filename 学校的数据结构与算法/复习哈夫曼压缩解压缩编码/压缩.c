#include"Res.h"

//������ѹ���ļ��������ֵ�
void analysisFile(char* secFile, struct Zidian* pzd);
//�����ַ��������������ڵ�
struct Node* createNode(struct Zifu* pzf);
//�����ֵ乹����������
struct Node* createHFMTree(struct Zidian* pzd);
//���ݹ���������ù��������� �� д���ֵ���
void createHFMCode(struct Node* pRoot, struct Zidian* pzd);
//������ѹ���ļ��������ֵ佫��Ӧ�ַ���HFM����д��ѹ�����ļ�
void writeCompressFile(const char* srcFile, const char* dstFile, struct Zidian* pzd);

int main()
{
	//��ѹ���ļ���Ϊ 1.txt
	//1.������ѹ���ļ����õ��ֵ�
	struct Zidian zd = { 0 };
	analysisFile("1.txt", &zd);
	//2.�����ֵ乹����������
	struct Node* pRoot = createHFMTree(&zd);
	//3.���ݹ���������ù��������벢д���ֵ�
	createHFMCode(pRoot, &zd);
	//4.���ݹ�������������ѹ������ļ�
	writeCompressFile("1.txt", "2.txt", &zd);

	while (1);

	return 0;
}

void analysisFile(char* secFile, struct Zidian* pzd)
{
	if (secFile == NULL || pzd == NULL)return;//����

	FILE* fp = fopen(secFile, "rb");//�Զ�����ֻ���ķ�ʽ���ļ�
	if (NULL == fp)
	{
		perror("analysisFile open file failed!\n");
		return;
	}

	unsigned char read_c;//���ڴ洢��ȡ�����ַ�
	while (fread(&read_c, 1, 1, fp)==1)//�������һ���ַ�
	{
		bool exist = false;//�Ƿ��Ѿ����ֵ��д���
		for (int i = 0; i < pzd->zf_num; i++)
		{
			if (read_c == pzd->zf_arr[i].zf)
			{
				exist = true;
				pzd->zf_arr[i].cnt++;//������ڣ����ַ��ĳ��ִ���+1
			}
		}
		if (!exist)//��������ڣ����ֵ��д�����ַ����ҳ��ִ���+1
		{
			pzd->zf_arr[pzd->zf_num].zf = read_c;
			pzd->zf_arr[pzd->zf_num++].cnt++;
		}
	}//end of (fread(&read_c, 1, 1, fp)==1
	fclose(fp);
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
	//0 ׼�������飬��� �����ֵ䴴���� ÿ���ַ��� �ڵ�ָ��
	struct Node** ppArr = calloc(pzd->zf_num, sizeof(struct Node*));
	if (!ppArr)return NULL;
	//�����ֵ䴴�� ÿ���ַ��� �ڵ�ָ�� ������ղŴ�����ָ������
	for (int i = 0; i < pzd->zf_num; i++)
	{
		ppArr[i] = createNode(&(pzd->zf_arr[i]));
		ppArr[i]->zf.idx = i;//������ָ����������Ӧ�������±�
	}
	// 1 �� ָ�������� ѭ�� ����С�ĺ͵ڶ�С����ϳ�������ָ������
	int minIdx, secMinIdx;
	struct Node* pTemp = NULL;
	for (int i = 0; i < pzd->zf_num - 1; i++)
	{
		//����С
		int j = 0;//�����һ����С
		while (ppArr[j] == NULL)j++;//�����սڵ�
		minIdx = j++;
		for (j; j < pzd->zf_num; j++)
		{
			//����ýڵ���� �� j���ִ��� С�� minIdx��
			if (ppArr[j] && ppArr[j]->zf.cnt < ppArr[minIdx]->zf.cnt)
			{
				minIdx = j;
			}
		}
		//�ҵڶ�С
		j = 0;
		while (ppArr[j] == NULL || j == minIdx)j++;//�����պ���С�ڵ�
		secMinIdx = j++;
		for (j; j < pzd->zf_num; j++)
		{
			if (ppArr[j] && ppArr[j]->zf.cnt < ppArr[secMinIdx]->zf.cnt 
				&& j != minIdx)
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
	}//end of (int i = 0; i < pzd->zf_num - 1; i++)
	// 4 �������ĸ��ڵ㣬�����������ĸ��ڵ�
	return pTemp;
}

//�ж��Ƿ���Ҷ�ӽڵ�
bool isLeaf(struct Node* pRoot)
{
	if (NULL != pRoot && NULL == pRoot->pLeft && NULL == pRoot->pRight)
	{
		return true;
	}
	return false;
}

//����HFM����
void setHFMCode(struct Node* pRoot, char* pCodeArr)
{
	char tempCodeArr[HFM_CODE_LEN] = { 0 };
	int tempIdx = 0;
	while (pRoot->pParent)//��Ҷ�ӽڵ������Ҹ��ڵ�
	{
		//��1��2
		if (pRoot == pRoot->pParent->pLeft)
		{
			tempCodeArr[tempIdx++] = 1;
		}
		else
		{
			tempCodeArr[tempIdx++] = 2;
		}
		pRoot = pRoot->pParent;
	}
	for (int i = 0; i < tempIdx; i++)
	{
		//����������Ѱ�ҵģ�������Ҫ���ַ�������һ��
		pCodeArr[i] = tempCodeArr[tempIdx - 1 - i];
	}
}

void createHFMCode(struct Node* pRoot, struct Zidian* pzd)
{
	if (pRoot == NULL || pzd == NULL)return;
	if (isLeaf(pRoot))
	{
		int idx = pRoot->zf.idx;
		setHFMCode(pRoot, pzd->zf_arr[idx].code);
	}
	else
	{
		createHFMCode(pRoot->pLeft, pzd);
		createHFMCode(pRoot->pRight, pzd);
	}

}

//���ֵ��еõ���Ӧ�ַ��Ĺ���������
void getHFMCode(char read_c, char* tempHFMCode, struct Zidian* pzd)
{
	for (int i = 0; i < pzd->zf_num; i++)
	{
		if (read_c == pzd->zf_arr[i].zf)
		{
			strcpy(tempHFMCode, pzd->zf_arr[i].code);

			//�������
			//printf("%c---", read_c);
			//for (int j = 0; j < HFM_CODE_LEN; j++)
			//{
			//	if (tempHFMCode[j] != 0)
			//	{
			//		printf("%d", tempHFMCode[j]);
			//	}
			//}
			//printf("\n");

			return;
		}
	}
}

void writeCompressFile(const char* srcFile, const char* dstFile, struct Zidian* pzd)
{
	if (NULL == srcFile || NULL == dstFile || NULL == pzd)return;
	FILE* fpDst = fopen(dstFile, "wb");
	FILE* fpSrc = fopen(srcFile, "rb");

	fwrite(pzd, 1, sizeof(struct Zidian), fpDst);

	char read_c;//�洢�������ֽ�
	int retRead;
	char write_c;//�洢Ҫд����ֽ�
	int idx_write_c;//ͳ�ƶ����˼���bitλ��write_c��

	char tempHFMCode[HFM_CODE_LEN] = { 0 };//��ʱ�洢����������
	int idxTempHFMCode = 0;

	bool isEnd = false;
	while (!isEnd)
	{
		//�����ʱ���������������ǿյľ�ȥ�¶�һ��
		if (0 == tempHFMCode[idxTempHFMCode])
		{
			retRead = fread(&read_c, 1, 1, fpSrc);
			if (retRead < 1)break;
			//���ֵ��л�ȡread_c�ַ���HFM����д�뵽tempHFMCode��
			getHFMCode(read_c, tempHFMCode, pzd);
			idxTempHFMCode = 0;
		}

		//ƴ�ɶ������ֽ�
		write_c = 0;
		idx_write_c = 0;
		while (idx_write_c < 8)
		{
			if (2 == tempHFMCode[idxTempHFMCode])//���ö�ӦbitλΪ0
			{
				//~��ʾ��λȡ��
				//1&����������
				//0&����������0
				write_c = write_c & ~(1 << (7 - idx_write_c));
				idx_write_c++;
				idxTempHFMCode++;
			}
			else if (1 == tempHFMCode[idxTempHFMCode])//���ö�ӦbitλΪ1
			{
				//1|����������1
				//0|����������
				write_c = write_c | (1 << (7 - idx_write_c));
				idx_write_c++;
				idxTempHFMCode++;
			}
			else
			{
				//�����˵����ǰ�ֽڵ�HFM�����Ѿ�������
				//��Ҫ�¶�һ��
				retRead = fread(&read_c, 1, 1, fpSrc);
				if (retRead < 1)
				{
					//������˵����ѹ���ļ��Ѿ���ȡ����ˣ����Խ�����
					isEnd = true;
					break;
				}
				getHFMCode(read_c, tempHFMCode, pzd);
				idxTempHFMCode = 0;
			}
		}//end of while (idx_write_c < 8)
		//���˸�bitλ��дһ��
		fwrite(&write_c, 1, 1, fpDst);

		//��������
		//for (int i = 0; i < 8; i++)
		//{
		//	if (write_c & 0x80)
		//	{
		//		printf("1");
		//	}
		//	else
		//	{
		//		printf("0");
		//	}
		//	write_c <<= 1;
		//}
		//printf("\n");

	}//end of while (!isEnd)

	//д����
	fclose(fpDst);
	fclose(fpSrc);
}
