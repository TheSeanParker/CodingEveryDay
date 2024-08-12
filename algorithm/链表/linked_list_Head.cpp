#include <iostream>
#include<vector>

    // 创建头节点head，并且将当前结点p指向头结点（p=head）
    // 创建下一个结点q，当前结点p的下一结点为q（p->next=q）
    // 结点p后移一位（p = p->next）
using namespace std;
struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x) :val(x), next(nullptr){}
};

int main(){
	int num;
	cin >> num;
	// 初始化一个空表
	ListNode* head = new ListNode(num);
	ListNode* p = head;
	
	//利用头插法创建一个链表

	while (cin >> num){
        if(num==9) break;	
		ListNode* q = new ListNode(num);
		q->next=p; 
		p = q;
	}
    // 最后还差一个头节点的空指针，其实这个在构造函数里，已经有体现出来了
	// 遍历这个链表，并输出每个结点的元素
	ListNode* m = p;
	while (m != nullptr){
		cout << m->val << endl;
		m = m->next;
	}
	return 0;

}
