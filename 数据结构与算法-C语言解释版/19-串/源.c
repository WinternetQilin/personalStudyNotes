#include<stdio.h>
#include<string.h>
#include<malloc.h>

/*02
�����ַ���
	�󳤶�		strlen
	��ֵ		strcpy
	ƴ��		strcat
	�Ƚ�		strcmp
	���Ӵ�		strstr
�����㷨��
	BF brute-force ���Ʒ�
		iָ�򸸴���һ���ַ���jָ���Ӵ���һ���ַ�
		idx=0��¼��ͬ�Ŀ�ʼ�±꣬����idxʵ��i���˵�ǰ��һ����һ���ַ�����λ��
		ѭ���Ƚ�iָ����ַ���jָ����ַ��Ƿ���ͬ
			��ͬ��i++��j++����������j=�Ӵ����ȣ�����idx���ɣ���ʱ��idx�����Ӵ��ڸ����е��±꣩
			��ͬ��idx++ , i=idx,j=0,
		�׶ˣ�
			idxÿ��ֻ��ǰ��һ���ַ���λ��
	KMP �㷨
		i����ԭ��ͨ��j����һ��k��ʵ�ֻ�ԭ
		j������i��j��ͬ���ַ�����
			�����j���������ɸ���ͬ�ģ�ҲҪ���ǵ�
			����һ��next���飬ר��Ҫ��һ������ȥ��next����
			next�������ã�
				next[j]=k
				j = next[j]
				k���ǲ���ͬ��ʱ��jҪ��ǰŲ�����ַ�����
*/

int BF(char* pStr1, char* pStr2) {
	//����
	if (NULL == pStr1 || NULL == pStr2)return -1;
	//iָ�򸸴���һ���ַ���jָ���Ӵ���һ���ַ�
	int i = 0;
	int j = 0;
	//idx��¼��ͬ�Ŀ�ʼ�±�
	int idx = 0;
	//ѭ���Ƚ�
	while (1)
	{
		//�ȿ��ǽ���
		if ('\0' == pStr1[i] || '\0' == pStr2[j])break;
		//��ʼ�Ƚ�
		if (pStr1[i] == pStr2[j]) {
			i++;
			j++;
		}
		else {
			idx++;
			i = idx;
			j = 0;
		}
	}
	if ('\0' == pStr2[j]) {
		return idx;
	}
	return -1;
}

//����ƫ�Ʊ�ĺ���
void getNext(char* s, int* next, int size) {
	int j = 0;
	int k = -1;//��ͨ�������ǰ��һ��

	next[0] = k;
	while (j < size) {
		if (-1 == k || s[k] == s[j]) {
			if (s[++j] == s[++k]) {
				next[j] = k;
			}
			else {
				next[j] = k;
			}
		}
		else {
			k = next[k];
		}
	}
}

int KMP(char* pStr1, char* pStr2) {
	//����
	if (NULL == pStr1 || NULL == pStr2)return -1;
	//����next����
	int size1 = strlen(pStr1);
	int size2 = strlen(pStr2);
	int* pNext = malloc(sizeof(int) * size2);
	getNext(pStr2, pNext, size2);
	
#if 1
	//����
	printf("next���飺");
	for (int i = 0; i < size2; i++)
	{
		printf("%d ", pNext[i]);
	}
	printf("\n");
#endif
	int i = 0;
	int j = 0;
	while (i<size1&&j<size2)
	{
		if (pStr1[i] == pStr2[j]||-1==j) {
			i++;
			j++;
		}
		else {
			j = pNext[j];
		}
	}
	if ('\0' == pStr2[j]) {
		return (i-j);
	}

	return -1;
}

int main() {
	char str1[] = "abcdefghijk";
	char str2[] = "aaab";

	//int r = BF(str1, str2);
	int r = KMP(str1, str2);

	if (-1 == r) {
		printf("�Ҳ����ַ�����\n");
	}
	else {
		printf("r:%d\n", r);
	}
	

	while (1);
	return 0;
}
