#include <iostream>
#include <string>

using namespace std;

const int content = 200; // 假设总内存大小
int job_number = 0; // 当前作业数量

class MyLinkedList {
public:
	struct LinkedNode {
		string name;
		int start;
		int length;
		LinkedNode* next;

		LinkedNode(string name, int start, int length)
			: name(name), start(start), length(length), next(nullptr) {
		}

		LinkedNode(LinkedNode const& node)
			: name(node.name), start(node.start), length(node.length), next(nullptr) {
		}
	};

	LinkedNode* dummy_head;

	MyLinkedList() {
		dummy_head = new LinkedNode("dummy_head", 0, 0);
	}

	void disp() {
		cout << "作业名\t起始地址\t所占内存" << endl;
		LinkedNode* tmp = dummy_head->next;
		int begin = 0;
		while (true) {
			if (tmp == nullptr) {
				if (begin != content)
					cout << "空闲区\t" << begin << "\t\t" << content - begin << endl;
				break;
			}
			if (begin == 0) {
				if (dummy_head->next->start != 0)
					cout << "空闲区\t" << 0 << "\t\t" << dummy_head->next->start - begin << endl;
				else
					cout << tmp->name << "\t\t" << tmp->start << "\t\t" << tmp->length << endl;
			}
			else {
				if (tmp->start == begin) {
					cout << tmp->name << "\t\t" << tmp->start << "\t\t" << tmp->length << endl;
				}
				else if (tmp->start > begin) {
					cout << "空闲区\t" << begin << "\t\t" << tmp->start - begin << endl;
					begin = tmp->start;
					continue;
				}
			}
			begin = tmp->start + tmp->length;
			tmp = tmp->next;
		}
	}

	bool queue(string name, int length) {
		LinkedNode tmp(name, 0, length);
		// Implement queue mechanism if necessary
		return false;
	}
} main_link;

// 分配算法
bool insert_when_empty(MyLinkedList::LinkedNode& new_comer) {
	if (content >= new_comer.length) {
		new_comer.start = 0;
		main_link.dummy_head->next = new MyLinkedList::LinkedNode(new_comer);
		job_number++;
		cout << "在地址为 0 处插入成功！" << endl;
		return true;
	}
	else {
		cout << "资源不足，插入失败。" << endl;
		return false;
	}
}

bool Al_first(MyLinkedList::LinkedNode new_comer) {
	if (job_number == 0) {
		return insert_when_empty(new_comer);
	}

	MyLinkedList::LinkedNode* tmp1 = main_link.dummy_head->next;
	MyLinkedList::LinkedNode* tmp2 = tmp1->next;

	for (; tmp2 != nullptr; tmp1 = tmp1->next, tmp2 = tmp2->next) {
		int sub = tmp2->start - (tmp1->start + tmp1->length);
		if (sub >= new_comer.length) {
			new_comer.next = tmp1->next;
			tmp1->next = new MyLinkedList::LinkedNode(new_comer);
			new_comer.start = tmp1->start + tmp1->length;
			job_number++;
			cout << "在地址为 " << new_comer.start << " 处插入成功" << endl;
			return true;
		}
	}

	if (content - (tmp1->start + tmp1->length) >= new_comer.length) {
		new_comer.start = tmp1->start + tmp1->length;
		tmp1->next = new MyLinkedList::LinkedNode(new_comer);
		job_number++;
		cout << "在地址为 " << new_comer.start << " 处插入成功" << endl;
		return true;
	}

	cout << "资源不足，插入失败。" << endl;
	return false;
}

bool Al_best(MyLinkedList::LinkedNode new_comer) {
	//链表为空，相当于空闲区在前面
	if (job_number == 0) {
		return insert_when_empty(new_comer);
	}
	//链表不为空
	MyLinkedList::LinkedNode* tmp1 = main_link.dummy_head, * tmp2 = nullptr;  //双指针
	int flag = 0;
	int record;
	int tmp;
	//找符合条件最小空闲区的起始地址
	while (tmp1->next) {
		if (flag == 0) {      //第一个作业前面的空闲区（0也记录）
			record = tmp1->next->start;
			tmp2 = tmp1;
			flag = 1;
		}
		else {      //第一个作业之后（前面肯定有作业）
			tmp = tmp1->next->start - tmp1->start - tmp1->length;
			if (record == 0 && tmp >= new_comer.length) {       //第一次有足够容量，直接存入
				record = tmp;
				tmp2 = tmp1;
				flag = 2;
			}
			else if (tmp >= new_comer.length && tmp < record) {     //第一次后，有比其更小的空间，且资源满足，则更新
				record = tmp;
				tmp2 = tmp1;
				flag = 3;
			}
		}
		tmp1 = tmp1->next;
	}
	tmp = content - tmp1->start - tmp1->length;
	//1.资源满足情况a：最后一段空闲区
	if (tmp >= new_comer.length && record > tmp) {
		new_comer.next = tmp1->next;
		tmp1->next = &new_comer;
		new_comer.start = tmp1->start + tmp1->length;
		job_number++;
		cout << "在地址为 " << new_comer.start << " 处插入成功" << endl;
		return true;
	}
	if (record != 0) {
		//2.资源满足情况b：不是最后一段空闲区
		new_comer.next = tmp2->next;
		tmp2->next = &new_comer;
		new_comer.start = tmp2->start + tmp2->length;
		job_number++;
		cout << "在地址为 " << new_comer.start << " 处插入成功" << endl;
		return true;
	}
	else {
		//3.资源不足
		cout << "资源不足，插入失败。" << endl;
		return false;
	}
}

bool Al_worst(MyLinkedList::LinkedNode new_comer) {
	//链表为空，相当于空闲区在前面
	if (job_number == 0) {
		return insert_when_empty(new_comer);
	}
	//链表不为空
	MyLinkedList::LinkedNode* tmp1 = main_link.dummy_head, * tmp2 = nullptr;  //双指针
	int flag = 0;
	int record;
	int tmp;
	//找符合条件最大空闲区的起始地址
	while (tmp1->next) {
		if (flag == 0) {      //第一个作业前面的空闲区（0也记录）
			record = tmp1->next->start;
			tmp2 = tmp1;
			flag = 1;
		}
		else {      //第一个作业之后（前面肯定有作业）
			tmp = tmp1->next->start - tmp1->start - tmp1->length;
			if (record == 0 && tmp >= new_comer.length) {       //第一次有足够容量，直接存入
				record = tmp;
				tmp2 = tmp1;
				flag = 2;
			}
			else if (tmp >= new_comer.length && tmp > record) {     //第一次后，有比其更大的空间，且资源满足，则更新
				record = tmp;
				tmp2 = tmp1;
				flag = 3;
			}
		}
		tmp1 = tmp1->next;
	}
	tmp = content - tmp1->start - tmp1->length;
	//1.资源满足情况a：最后一段空闲区
	if (tmp >= new_comer.length && record < tmp) {
		new_comer.next = tmp1->next;
		tmp1->next = &new_comer;
		new_comer.start = tmp1->start + tmp1->length;
		job_number++;
		cout << "在地址为 " << new_comer.start << " 处插入成功" << endl;
		return true;
	}
	if (record != 0) {
		//2.资源满足情况b：不是最后一段空闲区
		new_comer.next = tmp2->next;
		tmp2->next = &new_comer;
		new_comer.start = tmp2->start + tmp2->length;
		job_number++;
		cout << "在地址为 " << new_comer.start << " 处插入成功" << endl;
		return true;
	}
	else {
		//3.资源不足
		cout << "资源不足，插入失败。" << endl;
		return false;
	}
}

// 实现最佳适应和最坏适应算法类似
//回收算法
bool garbage_recycle() {
	string name;
	cout << "请输入要回收的作业名：";
	cin >> name;
	MyLinkedList::LinkedNode* tmp1 = main_link.dummy_head;
	MyLinkedList::LinkedNode* tmp2 = tmp1->next;

	while (tmp2 != nullptr && tmp2->name != name) {
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}

	if (tmp2 == nullptr) {
		cout << "未找到作业: " << name << endl;
		return false;
	}
	else {
		tmp1->next = tmp2->next;
		delete tmp2;
		job_number--;
		cout << "作业 " << name << " 已成功回收。" << endl;
		return true;
	}
}

MyLinkedList::LinkedNode create_node() {
	string name;
	int length;
	cout << "请输入作业名：";
	cin >> name;
	cout << "请输入作业所需资源：";
	cin >> length;
	return MyLinkedList::LinkedNode(name, 0, length);
}

// 提供服务菜单
void menu() {
	printf("1.最先适应算法.");
	printf("\n2.最佳适应算法.");
	printf("\n3.最坏适应算法.");
	printf("\n4.回收内存算法.");
	printf("\n5.结束程序请按5.\n");

	while (true) {
		int m;
		cin >> m;

		switch (m) {
		case 1:
			Al_first(create_node());
			break;
		case 2:
			Al_best(create_node());
			break;
		case 3:
			Al_worst(create_node());
			break;
		case 4:
			garbage_recycle();
			break;
		case 5:
			cout << "程序成功终止！";
			return;
		default:
			printf("输入错误!,请重新输入\n");
		}
		main_link.disp();
	}
}

// 主函数
int main() {
	menu();
	return 0;
}
