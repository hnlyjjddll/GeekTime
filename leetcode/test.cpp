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

int main() {
    vector<int> ivec{4,2,3,1};
    ListNode* head = makeLink(ivec);
    Solution s;
    s.sortList(head);
    return 0;
}