#include<stdio.h>
#include<malloc.h>

//������ͨ
#define NO 0xFFFFFF

#define MAX 100
/*
̰�ģ�̰�����㷨˼�룺
	���������ɳ�С�����⣬Ȼ�����
	ÿһС����ѡ��ǰ������õ�ѡ����˷�������ͼ�õ��������Ž�
	������ѧ����A��Ѱ·
		ȱ�ݣ�
			1.����һ���ܵõ��������Ž�
			2.ÿһ�����Ǿֲ�����
	��Ҫ���ʲô���⣺
		1.���·������
			�Ͻ�˹����(Dijkstra)�㷨������㵽�յ�����·��
				ͨ������ѡ���������Ķ��������������·��Ȩֵ�����ۣ���ֱ���������ж���
		2.��С����������
			��³˹����(Kruskal)�㷨��ͼ�ṹ ת���ɶ�����������Ȩ����С�����
				1 �����еı߰���Ȩ�ش�С����
				2 ��С����������ӵ���С��������
					ע�ⲻ�ܲ����ػ�����·��
					���������ػ���������������
				3 �������еı߶���ӵ������У���ʱ������ͽ������ͼ��Ӧ����С������
		3.��������
*/

//ͼ�ṹ
struct graph {
	int verNum;//��������
	int edgeNum;//������
	char vertex[MAX];//�涥���
	int edge[MAX][MAX];//��ߵ�
};

void Dijkstra(struct graph* g, int in, int dist[MAX]) {
	//1 �ҵ���ǰ��ڵ����������·��

	//��ǳɹ���ȡ��·��(0=û��ȡ��1=�ɹ���ȡ)
	int flag[MAX] = { 0 };
	for (int i = 0; i < g->verNum; i++)
	{
		flag[i] = 0;
		//�������ڵ�ÿ�������ֵ
		dist[i] = g->edge[in][i];
	}

	//2 ���䶥��
	flag[in] = 1;//��ڱ��
	dist[in] = 0;


	int min = NO;
	int minIdx;

	for (int i = 1; i < g->verNum; i++) {
		min = NO;
		for (int j = 1; j < g->verNum; j++) {
			if (0 == flag[j] && dist[j] < min) {
				min = dist[j];
				minIdx = j;
			}
		}
		
		flag[minIdx] = 1;
		for (int j = 1; j < g->verNum; j++) {
			if (0 == flag[j] && (g->edge[minIdx][j])<dist[j]) {
				dist[j] = min + g->edge[minIdx][j];
			}
		}

	}
	for (int i = 1; i < g->verNum; i++) {
		printf("���·��(%c,%c)=%d\n",
			g->vertex[in],
			g->vertex[i],
			dist[i]);
	}
}

//��
struct edge {
	int beg;
	int end;
	int value;//Ȩ��
};

void travel(struct edge* a, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d->%d  %d\n",
			a[i].beg, a[i].end, a[i].value);
	}
}

void Kruskal(struct graph* g) {
	//1 �����еı߶��ҳ���
	struct edge* pEdges = malloc(g->edgeNum * sizeof(struct edge));
	
	int k = 0;
	for (int i = 0; i < g->verNum; i++) {
		for (int j = 0; j < i; j++)//��Ϊ������ͼ����ά�����жԳƣ�����ֻ�ñ���һ�������
		{
			if (NO != g->edge[i][j]) {
				pEdges[k].beg = g->vertex[i] - '0';
				pEdges[k].end = g->vertex[j] - '0';
				pEdges[k].value = g->edge[i][j];
				k++;
			}
		}
	}
	//travel(pEdges, k);
	//2  ������
	int minV;
	struct edge temp;

	//��������
	for (int i = 0; i < k; i++)
	{
		minV = i;//�����һ����С
		for (int j = i; j < k; j++) {
			if (pEdges[j].value < pEdges[minV].value)
				minV = j;
		}

		//pEdges[i] �� pEdges[minV]  ����
		temp.beg = pEdges[minV].beg;
		temp.end = pEdges[minV].end;
		temp.value = pEdges[minV].value;


		pEdges[minV].beg = pEdges[i].beg;
		pEdges[minV].end = pEdges[i].end;
		pEdges[minV].value = pEdges[i].value;


		pEdges[i].beg = temp.beg;
		pEdges[i].end = temp.end;
		pEdges[i].value = temp.value;
	}
	//travel(pEdges, k);

	//3 ѭ����ӵ���С�������У���������ػ����Ͳ����
	struct edge* minTree = malloc(g->edgeNum * sizeof(struct edge));

	//ÿ����������һ�����ֵ
	int flag[MAX] = { 0 };
	for (int i = 0; i < g->verNum; i++) {
		flag[i] = i;
	}

	int beg, end;
	int num = 0;
	int elem;
	for (int i = 0; i < g->edgeNum; i++)
	{
		//�ҵ���ǰ�ߵ��������� ��Ӧ  flag�����±�
		beg = pEdges[i].beg - 1;
		end = pEdges[i].end - 1;
		printf("beg:%d,end:%d\n", beg, end);

		//�������λ�ô��� ���Ҷ���ı��ֵ��ͬ  �Ͳ��������·
		if (flag[beg] != flag[end]) {
			//��ӵ���С��������
			minTree[num].beg = pEdges[i].beg;
			minTree[num].end = pEdges[i].end;
			minTree[num].value = pEdges[i].value;

			num++;//����

			elem = flag[end];

			//���¼ӵ���С�������еĶ����Ǹĳ�һ����
			for (int k = 0; k < g->verNum; k++) {
				if (flag[k] == elem)
					flag[k] = flag[beg];
			}

			printf("flag:");
			for (int j = 0; j < g->verNum; j++) {
				printf("%d ", flag[j]);
			}
			printf("\n");

			//���ѡ��ıߵ������Ͷ��������1������
			if (num == g->verNum - 1) break;
		}
	}
	printf("��С������:");
	travel(minTree, num);
}



int main() {
	//Dijkstra
	struct graph g1 =
	{
		5,7,"ABCDE",
		{
			{ 0, 10, NO, 30, 100 },
			{ NO, 0, 50, NO, NO },
			{ NO, NO, 0, NO, 10 },
			{ NO, NO, 20, 0, 60 },
			{ NO, NO, NO, NO, 0 },
		}
	};
	//��� ���������е��±�
	//int in = 0;

	//���� ���·��
	//int dist[MAX] = { 0 };

	//Dijkstra(&g1, in, dist);
	//printf("path:");
	//for (int i = 0; i < 10; i++)
		//printf("%d ", dist[i]);
	//printf("\n");

	//Kruskal
	struct graph g2 = {
		7, 9, "1234567",
		{
			{ 0, 6, NO, NO, NO, 1, NO },
			{ 6, 0, 4, NO, NO, NO, 3 },
			{ NO, 4, 0, 2, NO, NO, NO },
			{ NO, NO, 2, 0, 6, NO, 5 },
			{ NO, NO, NO, 6, 0, 8, 7 },
			{ 1, NO, NO, NO, 8, 0, NO },
			{ NO, 3, NO, 5, 7, NO, 0 }
		}
	};

	Kruskal(&g2);

	while (1);
	return 0;
}
