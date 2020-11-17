#include <list>
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <cstdlib>

using namespace std;

int packet(const vector<int>& s,int limit){
    vector<bool> result(limit+1,0);
    result[0] = true;
    for(int i=0;i<s.size();++i){
        for(int j=limit-s[i];j>=0;--j){
            if(result[j]){
                result[j+s[i]] = true;
            }
        }
    }

    for(int i=limit;i>=1;--i){
        if(result[i]){
            return limit-i;
        }
    }
    return 0;
}

int MaximumCopy(
    const std::vector<size_t> &s, 
    size_t C, 
    size_t &start_index, 
    size_t &end_index){
    
    if(s.empty()){
        return -1;
    }

    int j = 0;
    int maxSize = -1;
    int curSize = 0;
    for(int i=0;i<s.size();++i){
        if(curSize+s[i] <= C){
            curSize += s[i];
        }else if(curSize+s[i] > C){
            while(j<=i && curSize+s[i]>C){
                curSize = curSize-s[j++];
            }

            if(j > i){
                curSize = 0;
            }else{
                curSize += s[i];
            }
        }

        if(curSize == C){
            start_index = j;
            end_index = i;
            return 0;
        }

        if(curSize > maxSize){
            start_index = j;
            end_index = i;
            maxSize = curSize;
        }
    }

    return C-maxSize;

}

int main(void){
    vector<size_t> ivec{1,2,3,5,4};
    size_t start;
    size_t end;
    int ret = MaximumCopy(ivec,7,start,end);

    cout<<"start="<<start<<"end="<<end<<endl;
    cout<<"ret="<<ret<<endl;

    /*int a = 10;
    srand(time(0));
    while(a--){
        cout<<rand()%10<<endl;
    }*/
    return 0;
}
