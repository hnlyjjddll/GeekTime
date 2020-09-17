//
// Created by jdl on 2020/8/24.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int search(vector<int>& arr, int target) {
    int low = 0,high=arr.size()-1;

    while(low<=high){
      //对数据进行预处理，处理后同一数据不会落在不同分区
      //相同数据位于一个分区头，另一个分区的尾部
      while(low<high && arr[high] == arr[low]){
        --high;
      }

      int mid = low + ((high-low)>>1);
      //相同数据位于mid的两侧
      if(high > mid){
        int temp = arr[mid+1];
        while(mid>low && arr[mid] == temp){
          --mid;
        }
      }

      cout<<"mid[ "<<mid<<"]="<<arr[mid]<<endl;

      if(arr[mid] == target){
        if(mid == 0 || arr[mid-1] != target){
          return mid;
        }

        high = mid - 1;
      }else if(arr[low]<=arr[mid]){//左半边是升序
        if(target>=arr[low] && target < arr[mid]){
          high = mid - 1;
        }else{
          low = mid + 1;
        }
      }else{//右半边是升序
        if(target>arr[mid] && target<=arr[high]){
          low = mid + 1;
        }else{
          high = mid - 1;
        }
      }
    }

    return -1;
  }
};

int main(void){
  vector<int> iVec{21, 21, -21, -20, -17, -8, -6, -2, -2, -1, 0, 2, 3, 4, 4, 6, 11, 13, 14, 16, 17, 18, 20};
  Solution s;
  cout<<s.search(iVec,4)<<endl;
  return 0;
}
