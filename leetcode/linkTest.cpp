#include <list>
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>

using namespace std;

struct ListNode {
       int val;
       ListNode *next;
       ListNode() : val(0), next(nullptr) {}
       ListNode(int x) : val(x), next(nullptr) {}
       ListNode(int x, ListNode *next) : val(x), next(next) {}
   };

class Solution {
public:
  ListNode* sortList(ListNode* head) {
    if(!head){
      return nullptr;
    }

    _mergeSort(head,nullptr);
    return head;
  }

private:
  ListNode* _getMid(ListNode* head,ListNode* tail){
    ListNode* pNode = head, *ppNode = head;
    while(ppNode != tail && ppNode){
      if(!ppNode->next || ppNode->next == tail){
        break;
      }

      ppNode = ppNode->next->next;
      pNode = pNode->next;
    }

    return pNode;
  }

  void _merge(ListNode* head,ListNode* mid, ListNode* tail){
    ListNode* pBeg = head,*pEnd = mid,*preBeg=nullptr,*preEnd=mid;
    while(pBeg!=mid && pEnd!=tail){
      if(pBeg->val<=pEnd->val){
        preBeg = pBeg;
        pBeg = pBeg->next;
      }else{
        preEnd->next = pEnd->next;
        pEnd->next = pBeg;

        if(preBeg){
          preBeg->next = pEnd;
        }

        preBeg = pEnd;
        pEnd = preEnd->next;
      }
    }
  }

  void _mergeSort(ListNode* head,ListNode* tail){
    if(head == tail || !head || head->next==tail){
      return;
    }

    auto mid = _getMid(head,tail);
    _mergeSort(head,mid);
    _mergeSort(mid,tail);
    _merge(head,mid,tail);
  }
};


ListNode* makeLinkList(const vector<int>& ivec,ListNode*& p){
  if(ivec.empty()){
    return nullptr;
  }
  ListNode* head = new ListNode(ivec[0]);
  p = head;
  for(int i=1;i<ivec.size();++i){
    p->next = new ListNode(ivec[i]);
    p = p->next;
  }

  return head;
}

void printLink(ListNode* head){
  while(head){
    cout<<head->val<<" ";
    head = head->next;
  }
  cout<<endl;
}

int main(void){
  vector<int> ivec{4,2,3,1};
  ListNode* tail;
  auto head = makeLinkList(ivec,tail);
  //printLink(head);
  Solution s;
  //s._setCmp(head,tail);

  auto sortHead = s.sortList(head);
  printLink(head);
  return 0;
}