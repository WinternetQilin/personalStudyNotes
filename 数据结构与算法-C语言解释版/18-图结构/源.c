#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define VERTEXS 7
#define EDGES 8

/*
* 07
* 
ͼ��
	�� ���� �� �� ���
	���㣺�����ݣ��������ṹ�������������еĽڵ�һ��
	�ߣ���������֮��Ĺ�ϵ
ͼ�ķ��ࣺ
	����ͼ�����з��򣨵�����ͨ��
	����ͼ����û�з���˫����ͨ��
	��ͼ��������ֵ����������ͨ��ϵ���������������ֵҲ������ Ȩ��
�������ͼ���кܶ��ַ�ʽ
	�ٽӾ������� ��ά����

	�ٽӱ�����
ͼ�ı�����
	������ȱ�����Deap First Search(DFS)
					�����Ѱ·�㷨˼����
					һ·����һ���ڵ㣬�Ҳ����ͻ�·��
	������ȱ�����Breadth First Search(BFS)
					�͹��Ѱ·�㷨˼��һ��
					�Ȱ����ڵĶ����꣬������������һ�����ڵ�
*/

//�� �ٽӾ��� ���� ͼ

//ͼ������
struct Graph
{
	//�������
	int vertexs;
	//�ߵ�����
	int edges;
	//ָ�룬ָ�� �洢����� ָ��
	char* pVertex;
	//ָ�룬ָ�� �洢�ߵ� ����ָ��
	int** pEdge;
};

//����ͼ����
struct Graph* createGraph() {
	struct Graph* pNew = malloc(sizeof(struct Graph));
	if (NULL == pNew)return NULL;
	//�ÿ�
	memset(pNew, 0, sizeof(struct Graph));
	//���س�ȥ
	return pNew;
}

//��ʼ��ͼ����
void initGraph(struct Graph* g, char* buff,int map[VERTEXS][VERTEXS]) {
	if (NULL == g || NULL == buff)return;

	//1.���ڴ�
	g->vertexs = VERTEXS;
	g->edges = EDGES;

	g->pVertex = malloc(sizeof(char) * g->vertexs);		//һά��������еĶ���
	memcpy(g->pVertex, buff, sizeof(char) * g->vertexs);//2.��ֵ
	g->pEdge = malloc(g->vertexs * sizeof(int*));		//��̬�ڴ�������ά����
	for (int i = 0; i < g->vertexs; i++)
	{
		g->pEdge[i]=malloc(g->vertexs * sizeof(int));
		memcpy(g->pEdge[i], map[i], g->vertexs * sizeof(int));//2.��ֵ
	}
}

//��ʾͼ����
void showGraph(struct Graph* g) {
	//˫��ѭ����ӡ��Ҫ��һ�ж�һ��������ʾ��������
	for (int i = 0; i < g->vertexs+1; i++)
	{
		for (int j = 0; j < g->vertexs + 1; j++)
		{
			if (0 == i && 0 == j) {
				printf("  ");
			}
			else if (0 == i) {//��1�д�ӡ��������
				printf("%c ", g->pVertex[j-1]);
			}
			else if (0 == j) {//��1�д�ӡ��������
				printf("%c ", g->pVertex[i-1]);
			}
			else {//�м䲿��
				printf("%d ", g->pEdge[i - 1][j - 1]);
			}
		}
		printf("\n");
	}
}

//��gָ���ͼ���ҵ�����v�������е��±� �Ҳ�������-1
int _getIdx(struct Graph* g, char v) {
	if (NULL == g) return -1;
	for (int i = 0; i < g->vertexs; i++) {
		if (v == g->pVertex[i]) return i;
	}
	return -1;
}

//��ĳ������ĵ�һ�����ڶ��㣬�ҵ��˷������±꣬û�ҵ�����-1��������������û���ҹ�
int _findFirstVertex(struct Graph* g, int begIdx, bool isFind[VERTEXS]) {
	for (int i = 0; i < g->vertexs; i++)
	{
		if (isFind[i])continue;//�Ѿ��ҹ��˵�����

		if (1 == g->pEdge[begIdx][i])return i;
	}
	return -1;
}
//��ĳ������ĵڶ������ڶ��㣬�ҵ��˷������±꣬û�ҵ�����-1��������������û���ҹ�
int _findNextVertex(struct Graph* g, int begIdx, bool isFind[VERTEXS]) {
	//�ѵ�ǰ������������һ����ʼ��
	for (int i = begIdx+1; i < g->vertexs; i++)
	{
		if (isFind[i])continue;//�Ѿ��ҹ��˵�����

		if (1 == g->pEdge[begIdx][i])return i;
	}
	return -1;
}

//�����������
void DFS(struct Graph* g, char beg, bool isFind[VERTEXS]) {
	//��beg����ĵ�һ�����ڵĶ���x,Ȼ����x�ĵ�һ�����ڶ���y

	//��ǰλ��
	int curIdx = _getIdx(g, beg);
	//��¼��ǰλ���Ѿ��ҹ���
	isFind[curIdx] = true;

	//��һ�������±�
	int nextIdx = _findFirstVertex(g, curIdx, isFind);

	//һ·����һ��
	while (true)
	{
		if (-1 == nextIdx)break;
		//���û�ҹ��ģ��ҹ��ľͲ��ظ�����ˣ�
		if (false == isFind[nextIdx]) {
			printf("%c", g->pVertex[nextIdx]);
			//���ݹ�
			DFS(g, g->pVertex[nextIdx], isFind);
		}
		nextIdx = _findNextVertex(g, curIdx, isFind);
	}
}
//�����������
void BFS(struct Graph* g, char beg, bool isFind[VERTEXS]) {
	//��Ҫһ������
	int queue[VERTEXS] = { 0 };
	int queueNum = 0;//����Ԫ�ظ���

	//��һ�����
	queue[queueNum++] = _getIdx(g, beg);
	//��Ӿ�Ҫ����߹�
	isFind[_getIdx(g, beg)] = true;

	int headIdx;
	int idx;
	while (queueNum)
	{
		//��һ������
		headIdx = queue[0];
		queueNum--;
		for (int i = 0; i < queueNum; i++)
		{
			queue[i] = queue[i + 1];
		}

		//��һ�����ڵĶ���ŵ�������
		idx = _findFirstVertex(g, headIdx, isFind);
		while (true)
		{
			if (-1 == idx)break;
			if (false == isFind[idx]) {
				isFind[idx] = true;
				printf("%c ", g->pVertex[idx]);
				queue[queueNum++] = idx;//���
			}
			idx = _findNextVertex(g, headIdx, isFind);
		}
	}
}

int main() {

	struct Graph* g = NULL;
	//һ����������еĶ���
	char buff[7] = "ABCDEFG";
	//��ά����涥����ϵ
	int map[VERTEXS][VERTEXS] = {
		{ 0, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	};
	g = createGraph();
	initGraph(g, buff, map);
	showGraph(g);

	bool isFind[VERTEXS] = { 0 };

	printf("A ");
	//DFS(g, 'A', isFind);
	BFS(g, 'A', isFind);
	printf("\n");
	return 0;
}
