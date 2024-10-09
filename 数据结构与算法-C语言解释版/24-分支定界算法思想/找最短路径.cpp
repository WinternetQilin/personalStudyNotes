#include<iostream>
#include<limits>//numeric_limits ����
#include<vector>
#include<queue>

using namespace std;

//�ڵ���
class Node
{
public:
	int index;		//���
	int weight;		//Ȩ��

	//����
	Node(int index = 0,int weight = 0):index(index),weight(weight){}
	//��������
	Node(const Node& n):index(n.index),weight(n.weight){}

	//���� < �����
	friend bool operator<(const Node& one, const Node& two) {
		return one.weight > two.weight;
	}

};

//·����
class Path
{
public:
	int index;		//���
	int weight;		//Ȩ��

	Path():index(0),weight(numeric_limits<int>::max()){}

};

//���·����
class shortPath {
public:
	vector<vector<int>> graph;	//ͼ
	int nodeCnt;	//�ڵ�ͳ��
	const int start;	//��ʼ
	const int end;		//����
	//�洢���·��������
	vector<int> pathIdx;
	int shortPathValue;	//���·��ֵ
public:
	shortPath(const vector<vector<int>>& g,
		int end):start(-1),end(end),
		nodeCnt(g.size()),graph(g){}

	//��ӡ
	void printPath() {
		cout << "���·��ֵ:" << shortPathValue << endl;
		cout << "·��:";
		copy(pathIdx.rbegin(), pathIdx.rend(),
			ostream_iterator<int>(cout, " "));
		cout << endl;
	}
	void getShortPath() {
		//��ʼ��·��������С
		vector<Path> myPath(nodeCnt);

		//���ȶ���
		priority_queue<Node, vector<Node>> minHeap;//��С��

		//��ڷŵ�������
		minHeap.push(Node(0, 0));

		while (true)
		{
			//��ȡ����ͷ������Ӷ����Ƴ�
			Node top = minHeap.top();
			minHeap.pop();

			//����ҵ����յ㣬ѭ������
			if (end == top.index)break;

			//��֦ ���ʵķŽ����������ʵĲ�Ҫ
			for (int i = 0; i < nodeCnt; i++)
			{
				if (graph[top.index][i] != start &&
					top.weight + graph[top.index][i] < myPath[i].weight) {

					minHeap.push(
						Node(i, top.weight + graph[top.index][i])
					);
					myPath[i].index = top.index;
					myPath[i].weight = top.weight + graph[top.index][i];
				}
			}

			//�ѿ��ˣ�ҲҪ����
			if (minHeap.empty())break;

		}
		shortPathValue = myPath[end].weight;

		//��·��
		int index = end;
		pathIdx.push_back(index);
		                                          
		while (true)//���յ㷴��ȥ�����
		{
			index = myPath[index].index;
			pathIdx.push_back(index);
			if (0 == index)break;//�ҵ���㣬����
		}
	}
};

int main() {
	//׼��ͼ
	const int size = 11;

	vector<vector<int>> graph(size);

	//���ڴ�
	for (int i = 0; i < size; i++) {
		graph[i].resize(size);
	}
	//��ʼ��
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			graph[i][j] = -1;
		}
	}

	graph[0][1] = 2;
	graph[0][2] = 3;
	graph[0][3] = 4;

	graph[1][2] = 3;
	graph[1][4] = 7;
	graph[1][5] = 2;

	graph[2][5] = 9;
	graph[2][6] = 2;


	graph[3][6] = 2;

	graph[4][7] = 3;
	graph[4][8] = 3;

	graph[5][6] = 1;
	graph[5][8] = 3;

	graph[6][8] = 5;
	graph[6][9] = 1;

	graph[7][10] = 3;

	graph[8][10] = 2;

	graph[9][10] = 2;
	graph[9][8] = 2;

	shortPath sPath(graph, 10);

	sPath.getShortPath();

	sPath.printPath();

	while (1);
	return 0;
}
