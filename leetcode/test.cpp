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

struct HeapNode{
    int val;
    int pos;
    HeapNode(int v,int p):val(v),pos(p){}
};

class Heap{
public:
    Heap(const vector<HeapNode>& nums):m_vecHeap(nums){
        _buildHeap(m_vecHeap,0,nums.size()-1);
    }

    /*int addAndGetNode(int val){
        int result = m_vecHeap[0];
        m_vecHeap[0] = val;
        _adjustHeap(m_vecHeap,0,m_vecHeap.size()-1);
        return result;
    }*/

    HeapNode getNode() const {
        return m_vecHeap[0];
    }

    void putNode(const HeapNode& node){
        m_vecHeap[0] = node;
        _adjustHeap(m_vecHeap,0,m_vecHeap.size()-1);
    }

    void sort(ListNode* pCur){
        for(int i = m_vecHeap.size()-1;i>=0;--i){
            _adjustHeap(m_vecHeap,0,i);
            pCur->next = new ListNode(m_vecHeap[0].val);
            pCur = pCur->next;
            swap(m_vecHeap[0],m_vecHeap[i]);
        }
    }

private:
    //自顶向下构建小顶堆
    void _buildHeap(vector<HeapNode>& nums,int low,int high){
        if(low>=high){
            return;
        }

        int noLeef = (high-1)/2; //第一个非叶节点对应下标
        for(int i=noLeef;i>=0;--i){
            while(2*i+1<=high){//非叶子节点
                int left = 2*i+1,right=2*i+2,min=left;

                if(right<=high && nums[right].val<nums[left].val){
                    min = right;
                }

                if(nums[i].val<=nums[min].val){//已经是小顶堆
                    break;
                }

                swap(nums[i],nums[min]);
                i = min;
            }
        }
    }

    //自顶向下调整小顶堆
    void _adjustHeap(vector<HeapNode>& nums,int low,int high){
        if(low>=high){
            return;
        } 

        int i = low;
        while(2*i+1<=high){
            int left = 2*i+1,right=2*i+2,min = left;
            if(right<=high && nums[right].val<nums[left].val){
                min = right;
            }

            if(nums[i].val <= nums[min].val){//已经是小顶堆
                break;
            }

            swap(nums[i],nums[min]);
            i = min;
        }
    }

private:
    vector<HeapNode> m_vecHeap;
};


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& vecListSet) {

        if(vecListSet.empty()){
            return nullptr;
        }

        vector<HeapNode> iVec;
        for(int i=0;i<vecListSet.size();++i){
            if(vecListSet[i]){
                iVec.push_back(HeapNode(vecListSet[i]->val,i));
            }
        }

        Heap* pHeap = new Heap(iVec);
        ListNode* pResult=new ListNode,*pCur=pResult;
        while(!iVec.empty()){
            HeapNode result = pHeap->getNode();
            pCur->next = vecListSet[result.pos];
            pCur = pCur->next;
            vecListSet[result.pos] = vecListSet[result.pos]->next;
            int pos = -1;
            if(!vecListSet[result.pos]){
                pos = _GetMin(vecListSet);
                if(pos == -1){
                    break;
                }
            }
            pHeap->putNode(HeapNode(vecListSet[pos]->val,pos));
        }

        pHeap->sort(pCur);
        return pResult->next;
    }
private:
    int _GetMin(vector<ListNode*> vecListSet){
        int pos = -1,val=INT32_MAX;
        for(int i=0;i<vecListSet.size();++i){
            if(vecListSet[i]){
                if(vecListSet[i]->val<val){
                    pos = i;
                    val = vecListSet[i]->val;
                }
            }
        }

        return pos;
    }
};


ListNode* makeLink(const vector<int>& ivec){
    if(ivec.empty()){
        return nullptr;
    }
    ListNode* head = new ListNode(ivec[0]);
    ListNode* p = head;
    for(int i=1;i<ivec.size();++i){
       p->next = new ListNode(ivec[i]);
       p = p->next;
    }
    
    return head;
}

class Test{
    public:
        Test(int a){
            cout<<"construct Test"<<endl;
        }

        Test(const Test& rhs){
            cout<<"copy construct Test"<<endl;
        }

        Test(const Test&& rhs){
            cout<<"rvalue copy construct Test"<<endl;
        }
};

void DeleteRepeatedSpace(std::string& str){
    if(str.size()<=1){
        return;
    }

    int j=1;
    for(int i=1;i<str.size();++i){
        if(str[i] != ' ' || str[j-1]!=' '){
            str[j++] = str[i];
        }
    }

    str.resize(j);
}

struct LinkNode{
    int val;
    LinkNode* next;
    LinkNode(int v):val(v),next(nullptr){}
};

void remove(char *s, char x){
    if(!s){
        return;
    }

    char* p = s;
    int i = 0;
    while(*p!='\0'){
        if(*p != x){
            *(s+i) = *p;
            ++i; 
        }

        ++p;
    }

    *(s+i) = '\0';
}


int main() {
    char ca[] = "12345";
    remove(ca,'2');
    cout<<string(ca)<<endl;

    vector<int*> ivec;
    ivec.resize(10,new int(1));
    //ListNode* head = makeLink(ivec);
    //Solution s;
    //s.mergeKLists(head);
    return 0;
}

