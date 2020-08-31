#include <vector>
#include <iostream>
#include <map>

using namespace std;

class Solution {
public:
    //回溯+剪枝
    int dwMinPath = INT32_MAX;
    map<pair<int,int>,int> mapSet;
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()==0 || triangle[0].size()==0){
            return 0;
        }

        _findMinimum(triangle,0,0,0);
        return dwMinPath;
    }

private:
    void _findMinimum(const vector<vector<int>>& triangle,int x,int y,int curPath){
        if(x>=triangle.size()){
            if(curPath < dwMinPath){
                cout<<"triangle["<<x-1<<"]["<<y<<"] update minPath="<<curPath<<endl;
                dwMinPath = curPath;
            }
            return;
        }

        //剪枝
        if(mapSet.find(make_pair(x,y))!=mapSet.end() 
            &&curPath+triangle[x][y] >= mapSet[make_pair(x,y)]){

            //cout<<"triangle["<<x<<"]["<<y<<"] = "<<triangle[x][y]<<" and curPath="<<curPath+triangle[x][y]<< " is longer than path="<<mapSet[make_pair(x,y)]<<endl;
            return;
        }else{
            //cout<<"triangle["<<x<<"]["<<y<<"] = "<<triangle[x][y]<<" and curPath="<<curPath+triangle[x][y]<< " is shorter than path="<<mapSet[make_pair(x,y)]<<endl;
            mapSet[make_pair(x,y)] = curPath+triangle[x][y];
        }

        curPath += triangle[x][y];
        cout<<"triangle["<<x<<"]["<<y<<"]"<<endl;

        //枚举
        _findMinimum(triangle,x+1,y,curPath); //往左下走
        _findMinimum(triangle,x+1,y+1,curPath);//往右下走
    }
};

int main(void){
    vector<vector<int>> triangle{
        {2},
        {3,4},
        {6,5,7},
        {4,1,8,3}
    };

    cout<<Solution().minimumTotal(triangle)<<endl;
    return 0;
}




