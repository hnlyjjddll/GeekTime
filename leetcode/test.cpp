#include <list>
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        if(s.empty()){
            return result;
        }

        vector<string> curPartition;
        _dfsTraverse(s,0,s.size()-1,curPartition);
        return result;
    }
private:
    void _dfsTraverse(const string& s, int beg,int end,vector<string>& curPartition){
        if(beg > end){
            return;
        }

        if(beg == end){
            curPartition.push_back(s.substr(beg,1));
            result.push_back(curPartition);
        }

        for(int i=beg; i<end; ++i){
            if(_isReverseString(s,beg,i)){
                if(_isReverseString(s,beg+1,end)){
                    curPartition.push_back(s.substr(beg,i-beg+1));
                    curPartition.push_back(s.substr(beg+1,end-beg));
                    
                    result.push_back(curPartition);
                    curPartition.pop_back();
                }
                _dfsTraverse(s,i+1,end,curPartition);
            }
        }
    }

    bool _isReverseString(string s,int beg,int end){
        while(beg<=end){
            if(s[beg] != s[end]){
                return false;
            }
            ++beg;
            --end;
        }

        return true;
    }
private:
    vector<vector<string>> result;
};

int main(void){
    Solution s;
    vector<vector<string>> result;
    result = s.partition("aab");

    for(const auto& item: result){
        for(const auto& str: item){
            cout<<str<<" ";
        }
        cout<<endl;
    }

    return 0;
}