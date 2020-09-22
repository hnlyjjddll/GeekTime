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
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if(s.empty() || wordDict.empty()){
            return result;
        }

        set<string> wordSet;
        minLength = INT_MAX;
        maxLength = 0;
        for(const auto& word: wordDict){
            if(word.size() < minLength){
                minLength = word.size();
            }

            if(word.size() > maxLength){
                maxLength = word.size();
            }

            wordSet.insert(std::move(word));

            _dfsTraverse(wordSet,s,0,s.size()-1,"");
        }
        return result;
    }

private:
    void _dfsTraverse(const set<string>& wordSet, const string& s,int beg, int end, const string& value){
        if(mapSet.find(s.substr(beg,end-beg+1)) != mapSet.end()){
            return;
        }

        if(wordSet.find(s.substr(beg,end-beg+1)) != wordSet.end()){
            string tmp = (value==""?"":value + " ") + s.substr(beg,end-beg+1);
            if(existSet.find(tmp) != existSet.end()){
                return;
            }
            existSet[tmp] = true;
            result.emplace_back(tmp);
            //return;
        }

        int max = end-minLength+1 > beg+maxLength-1 ? beg+maxLength-1 : end-minLength+1;
        for(int i=beg+minLength-1;i<=max;++i){
            if(wordSet.find(s.substr(beg,i-beg+1)) != wordSet.end()){
                string tmp  =  (value==""?"":value+" ") + s.substr(beg,i-beg+1);
                _dfsTraverse(wordSet,s,i+1,end,tmp);
            }
        }
    }
private:
    int minLength;
    int maxLength;
    unordered_map<string,bool> mapSet;
    map<string,bool> existSet;
    vector<string> result;
};

int main(void){
    /*Solution s;
    vector<string> wordSet{"aaaa","aa","a"};
    vector<string> result = s.wordBreak("aaaaaaa",wordSet);
    for(const auto& val: result){
        cout<<val<<endl;
    }*/

    vector<string> src{"aaaa aaaa","aa aa aaaa","aa aa aa aa","aa aaaa aa",
    "a a a a aaaa","a a a a a a aa","a a a a a a a a","a a a a a aa a",
    "a a a a aa aa","a a a a aa a a","a a a aa a aa","a a a aa a a a",
    "a a a aa aa a","a a a aaaa a","a a aa aaaa","a a aa a a aa","a a aa a a a a",
    "a a aa a aa a","a a aa aa aa","a a aa aa a a","a a aaaa aa",
    "a a aaaa a a","a aa a aaaa","a aa a a a aa","a aa a a a a a",
    "a aa a a aa a","a aa a aa aa","a aa a aa a a","a aa aa a aa",
    "a aa aa a a a","a aa aa aa a","a aa aaaa a","a aaaa a aa",
    "a aaaa a a a","a aaaa aa a","aa a a aaaa","aa a a a a aa",
    "aa a a a a a a","aa a a a aa a","aa a a aa aa","aa a a aa a a",
    "aa a aa a aa","aa a aa a a a","aa a aa aa a","aa a aaaa a"};

    set<string> setSrc;
    for(const auto& str: src){
        if(setSrc.find(str) != setSrc.end()){
            cout<<str<<" repeated"<<endl;
        }

        setSrc.insert(str);
    }
    cout<<"src size: " << setSrc.size()<<endl;

    vector<string> dest{
        "a a a a a a a a","aa a a a a a a","a aa a a a a a","a a aa a a a a",
        "aa aa a a a a","aaaa a a a a","a a a aa a a a","aa a aa a a a",
        "a aa aa a a a","a aaaa a a a","a a a a aa a a","aa a a aa a a",
        "a aa a aa a a","a a aa aa a a","aa aa aa a a","aaaa aa a a",
        "a a aaaa a a","aa aaaa a a","a a a a a aa a","aa a a a aa a",
        "a aa a a aa a","a a aa a aa a","aa aa a aa a","aaaa a aa a",
        "a a a aa aa a","aa a aa aa a","a aa aa aa a","a aaaa aa a",
        "a a a aaaa a","aa a aaaa a","a aa aaaa a","a a a a a a aa",
        "aa a a a a aa","a aa a a a aa","a a aa a a aa","aa aa a a aa",
        "aaaa a a aa","a a a aa a aa","aa a aa a aa","a aa aa a aa",
        "a aaaa a aa","a a a a aa aa","aa a a aa aa","a aa a aa aa","a a aa aa aa",
        "aa aa aa aa","aaaa aa aa","a a aaaa aa","aa aaaa aa","a a a a aaaa",
        "aa a a aaaa","a aa a aaaa","a a aa aaaa","aa aa aaaa","aaaa aaaa"
    };

    cout<<"dest size: "<<dest.size()<<endl;
    for(const auto& str:dest){
        if(setSrc.find(str) == setSrc.end()){
            cout<<str<<" not locate dest"<<endl;
        }
    }

    return 0;
}