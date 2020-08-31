#include <vector>
#include <iostream>
#include <map>

using namespace std;

class Solution {
public:
    int cnt;
    int totalNQueens(int n) {
        if(n<=0){
            return 0;
        }

        vector<int> vecSet(n,-1);
        _play(vecSet,0);
        return cnt;
    }

private:
    //摆第n层
    void _play(vector<int>& pa, int n){
        int column = pa.size();
        //cout<<"column="<<column<<endl;
        if(n==column){//找到一种摆法
            ++cnt;
            cout<<"place succ. cnt="<<cnt<<endl;
            return;
        }
        for(int i=0;i<column;++i){//依次尝试在第n层的任意一列摆放棋子
            if(_can(pa,n,i)){//摆放成功，继续摆下一层
                cout<<"succ placed. row="<<n<<" column="<<i<<endl;
                pa[n] = i;
                _play(pa,n+1);
                pa[n] = -1;
            }
        }
    }

    bool _can(const vector<int>& pa, int row, int column){
        if(row==2&&column==0){
            for(int i=0;i<row;++i){
                cout<<"###pa["<<i<<"]="<<pa[i]<<endl;
            }
        }
        int leftup = column-1,rightup=column+1;
        for(int i=row-1;i>=0;--i){
            if(pa[i] == column){//同一列已经有摆放棋子了    
                cout<<"1"<<" pa["<<i<<"] = "<<pa[i]<<" column="<<column<<endl;
                return false;
            }

            if(leftup>=0){//考察左上角元素
                if(pa[i] == leftup){
                    cout<<"2"<<" pa["<<i<<"] = "<<pa[i]<<" leftup="<<leftup<<endl;
                    return false;
                }
            }

            if(rightup<pa.size()){
                if(pa[i] == rightup){
                    cout<<"3"<<" pa["<<i<<"] = "<<pa[i]<<" rightup="<<rightup<<endl;
                    return false;
                }
            }

            --leftup;
            ++rightup;
        }
        return true;
    }
};

int main(void){
    cout<<Solution().totalNQueens(4)<<endl;
    return 0;
}