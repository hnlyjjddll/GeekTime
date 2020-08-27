#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };

//堆排序(升序-大顶堆  降序-小顶堆)
//堆是一个完全二叉树，非常适合用数组来存储
class Heap{
public:
    Heap(const vector<int>& nums):m_vecHeap(nums){
        _buildHeap(m_vecHeap,0,nums.size()-1);
    }

    int addAndGetNode(int val){
        int result = m_vecHeap[0];
        m_vecHeap[0] = val;
        _adjustHeap(m_vecHeap,0,m_vecHeap.size()-1);
        return result;
    }

    void sort(vector<int>& result) {
        for(int i = m_vecHeap.size()-1;i>=0;--i){
            _adjustHeap(m_vecHeap,0,i);
            result.push_back(m_vecHeap[0]);
            swap(m_vecHeap[0],m_vecHeap[i]);
        }
    }

private:
    //自顶向下构建小顶堆
    void _buildHeap(vector<int>& nums,int low,int high){
        if(low>=high){
            return;
        }

        int noLeef = (high-1)/2; //第一个非叶节点对应下标
        for(int i=noLeef;i>=0;--i){
            while(2*i+1<=high){//非叶子节点
                int left = 2*i+1,right=2*i+2,min=left;

                if(right<=high && nums[right]<nums[left]){
                    min = right;
                }

                if(nums[i]<=nums[min]){//已经是小顶堆
                    break;
                }

                swap(nums[i],nums[min]);
                i = min;
            }
        }
    }

    //自顶向下调整小顶堆
    void _adjustHeap(vector<int>& nums,int low,int high){
        if(low>=high){
            return;
        } 

        int i = low;
        while(2*i+1<=high){
            int left = 2*i+1,right=2*i+2,min = left;
            if(right<=high && nums[right]<nums[left]){
                min = right;
            }

            if(nums[i] <= nums[min]){//已经是小顶堆
                break;
            }

            swap(nums[i],nums[min]);
            i = min;
        }
    }

private:
    vector<int> m_vecHeap;
};

int GetMin(vector<ListNode*> vecListSet){
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

int main(void){
    ListNode* pOne = new ListNode(1);
    pOne->next = new ListNode(2);
    pOne->next->next = new ListNode(3);

    ListNode* pTwo = new ListNode(4);
    pTwo->next = new ListNode(5);
    pTwo->next->next = new ListNode(6);
    pTwo->next->next->next = new ListNode(7);

    ListNode* pThree = new ListNode(2);
    pThree->next = new ListNode(6);

    vector<ListNode*> vecListSet{pOne,pTwo};

    vector<int> iVec;
    for(int i=0;i<vecListSet.size();++i){
        if(vecListSet[i]){
            iVec.push_back(vecListSet[i]->val);
            auto pTmp = vecListSet[i];
            vecListSet[i] = vecListSet[i]->next;
            delete pTmp;
        }
    }

    Heap* pHeap = new Heap(iVec);

    while(true){
        int pos = GetMin(vecListSet);
        if(pos == -1){
            break;
        }
        
        if(vecListSet[pos]){
            auto pTmp = vecListSet[pos];
            vecListSet[pos] = vecListSet[pos]->next;
            int result =  pHeap->addAndGetNode(pTmp->val); 
            delete pTmp;
            cout<<"add pos["<<pos<<"]="<<pTmp->val<<endl<<" result: "<<result<<endl;
        }
    }

    vector<int> iiVec;
    pHeap->sort(iiVec);
    for( auto& item: iiVec){
        cout<<item<<" ";
    }

    cout<<endl;

    return 0;
}