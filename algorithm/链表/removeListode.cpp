#include<iostream>
using namespace std;
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

    ListNode* removeElements(ListNode* head, int val_) {
        // 删除头结点：
        while (head!=nullptr && head->val==val_)
        {
           ListNode* tmp=head;
           head=head->next;
           delete tmp;
        }
        
        // 删除非头结点
        ListNode* result=head;
        while (head != nullptr && head->next!=nullptr ){
            if (head->next->val==val_)
            {
                cout<<"准备执行删除操作"<<head->next->val <<endl;
                ListNode* tmp=head->next;// 这个操作用来删除指针，释放内存，真是太妙了！
                head->next=head->next->next; 
                delete tmp;// 释放内存
            }
            else
            {
                head = head->next;
            }		
	    }
        return result;
    }

int main(int argc, char const *argv[])
{
  	int num;
	cin >> num;
	//初始化一个空表
	ListNode* head = new ListNode(num);
	ListNode* p = head;
	
	//利用尾插法创建一个链表
	while (cin >> num){
        cout<<"想要退出输入,请输入9\n";
        if(num==9) break;	
		ListNode* q = new ListNode(num);
		p->next = q; 
		p = q;
	}
    
    ListNode* m = head;
	while (m != nullptr){
		cout << m->val << endl;
		m = m->next;
	}
    m = head;//m和head指针是一样的，一起指向某个node
    
    cout<<"进入到removeElements()函数中\n";
    cout<<"请输入要删除的结点的数量值\n";
    int b;
    cin>>b;
    m=removeElements(m,b);
    cout<<"删除特定数值后的打印\n";
    	while (m != nullptr){
		cout << m->val << endl;
		m = m->next;
	}
    return 0;
}
