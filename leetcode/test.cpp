#include <list>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& arr, int target) {
        int low = 0,high=arr.size()-1;
        while(low<=high){
            int mid = low + ((high-low)>>1);
            if(arr[mid]==target || arr[0] == target){
                if(arr[0] == target){
                    return 0;
                }
                
                if(arr[mid-1]!=target){
                    return mid;
                }

                high = mid - 1;
                
            }else if(arr[low]<=arr[mid] && arr[low] != arr[mid]){//左半边是升序
                cout<<"left order"<<endl;
                if(target>=arr[low] && target < arr[mid]){
                    cout<<"left left"<<endl;
                    high = mid - 1;
                }else{
                    cout<<"left right"<<endl;
                    low = mid + 1;
                }
            }else{//右半边是升序
                cout<<"right order"<<endl;
                if(target>arr[mid] && target<=arr[high]){
                    cout<<"right right"<<endl;
                    low = mid + 1;
                }else{
                    cout<<"right left"<<endl;
                    high = mid - 1;
                }
            }
        }

        return -1;
    }
};


int main(void){
    vector<int> iVec{2,1,2,2,2};
    Solution s;
    cout<<s.search(iVec,1)<<endl;
    return 0;
}