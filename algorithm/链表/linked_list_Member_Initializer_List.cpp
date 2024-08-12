
#include <iostream>
using namespace std;
 struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr){};
};
 struct ListNode2
{
    int val;
    ListNode2 *next;
};
int main(int argc, char const *argv[])
{
   ListNode* head=new ListNode(5);
   ListNode2* head2=new ListNode2;
   head2->val=9;
   return 0;
}
