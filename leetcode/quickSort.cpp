#include <iostream>
#include <vector>

using namespace std;

class AbstractSort{
public:
    virtual void sort(vector<int>& nums)=0;
};

//快速排序
class QuickSort:public AbstractSort{
public:
    void sort(vector<int>& nums) override {
        _quickSort(nums,0,nums.size()-1);
    }

private:
    int _partition(vector<int>& nums,int low,int high){
        int guard;
        int mid = low + ((high-low)>>1);
        //三数取中
        if(nums[low]>nums[mid]){
            if(nums[mid]>nums[high]){
                guard = mid;
            }else{
                guard = nums[low]>nums[high]?high:low;
            }
        }else{
            if(nums[low]>nums[high]){
                guard = low;
            }else{
                guard = nums[mid]>nums[high]?high:mid;
            }
        }

        swap(nums[guard],nums[high]);

        int i=low;
        for(int j=low; j<=high-1;++j){
            if(nums[j]<=nums[high]){
                swap(nums[i],nums[j]);
                ++i;
            }
        }
        swap(nums[i],nums[high]);
        return i;
    }

    void _quickSort(vector<int>& nums,int low,int high){
        while(low>=high){
            return;
        }

        int pivot = _partition(nums,low,high);
        _quickSort(nums,low,pivot-1);
        _quickSort(nums,pivot+1,high);
    }
}; 

//归并排序
class MergeSort:public AbstractSort{
public:
    void sort(vector<int>& nums) override{
        _mergeSort(nums,0,nums.size()-1);
    }

private:
    void _mergeSort(vector<int>& nums, int low, int high){
        while(low>=high){
            return;
        }

        int mid = low + ((high-low)>>1);
        _mergeSort(nums,low,mid);
        _mergeSort(nums,mid+1,high);
        _merge(nums,low,mid,high);
    }

    void _merge(vector<int>& nums, int low,int mid,int high){
        int i=low,j=mid+1,k=low;

        vector<int> iVec(nums);
        while(i<=mid && j<=high){
            if(iVec[i]<=iVec[j]){
                nums[k++] = iVec[i++];
            }else{
                nums[k++] = iVec[j++];
            }
        }

        if(i>mid){
            while(j<=high){
                nums[k++] = iVec[j++];
            }
        }

        if(j>high){
            while(i<=mid){
                nums[k++] = iVec[i++];
            }
        }
    }
};

//堆排序(升序-大顶堆  降序-小顶堆)
//堆是一个完全二叉树，非常适合用数组来存储
class HeapSort:public AbstractSort{
public:
    void sort(vector<int>& nums) override{
        _buildHeap(nums,0,nums.size()-1);
        for(int i = nums.size()-1;i>=0;--i){
            _adjustHeap(nums,0,i);
            swap(nums[0],nums[i]);
        }
    }

private:
    //自顶向下构建堆
    void _buildHeap(vector<int>& nums,int low,int high){
        if(low>=high){
            return;
        }

        int noLeef = (high-1)/2; //第一个非叶节点对应下标
        for(int i=noLeef;i>=0;--i){
            while(2*i+1<=high){//非叶子节点
                int left = 2*i+1,right=2*i+2,max=left;

                if(right<=high && nums[right]>nums[left]){
                    max = right;
                }

                if(nums[i]>=nums[max]){//已经是大顶堆
                    break;
                }

                swap(nums[i],nums[max]);
                i = max;
            }
        }
    }

    //自顶向下调整堆
    void _adjustHeap(vector<int>& nums,int low,int high){
        if(low>=high){
            return;
        }

        int i = low;
        while(2*i+1<=high){
            int left = 2*i+1,right=2*i+2,max = left;
            if(right<=high && nums[right]>nums[left]){
                max = right;
            }

            if(nums[i] >= nums[max]){//已经是大顶堆
                break;
            }

            swap(nums[i],nums[max]);
            i = max;
        }
    }
};


int main(void){
    vector<int> iVec{9,1,3,90,5,2};
    AbstractSort* pSort = new HeapSort;
    pSort->sort(iVec);
    for(auto item: iVec){
        cout<<item<<endl;
    }

    return 0;
}