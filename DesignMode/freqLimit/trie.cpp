#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void Split2Vector(const std::string& strSource, const std::string& strDelita, vector<string>& vecTarget){
    string str("");
    for(int i=0; i<strSource.size(); ++i){
        if(string(1,strSource[i]) == strDelita && !str.empty()){
            vecTarget.push_back(str);
            str = "";
        }else{
            if(string(1,strSource[i]) != strDelita){
                str += strSource[i];
            }
        }
    }

    if(!str.empty()){
        vecTarget.push_back(str);
    }

    cout<<"strSourceString: "<<strSource<<endl;
    for(const auto& strNode: vecTarget){
        cout<<strNode<<endl;
    }
}

class TrieNode{
    public:
        TrieNode(const std::string& strVal,const uint32_t dwFreqLimitCnt):
        m_strVal(strVal),
        m_dwFreqLimitCnt(dwFreqLimitCnt),
        m_bIsComplete(false){m_poMapNode.clear();}
        const std::string& GetValue(){return m_strVal;}
        uint32_t GetFreqLimitCnt() {return m_dwFreqLimitCnt;}
        void SetNode(const string& str, shared_ptr<TrieNode> poNode){
            m_poMapNode[str] = poNode;
        }
        shared_ptr<TrieNode> GetNode(const string str){
            if(m_poMapNode.find(str) != m_poMapNode.end()){
                return m_poMapNode.at(str);
            }

            return nullptr;
        }
        void SetCompleteFlag(bool bFlag){m_bIsComplete = bFlag;}
        bool IsComplete(){return m_bIsComplete;}
    private:
        const std::string m_strVal;
        const uint32_t m_dwFreqLimitCnt;
        map<string,shared_ptr<TrieNode>> m_poMapNode;
        bool m_bIsComplete;
};

class Trie{
    public:
        Trie(){
            m_poRootNode = make_shared<TrieNode>("/",0);
        }
        void AddNode(const std::string& strKey, const uint32_t dwFreqLimitCnt){
            vector<string> vecNode;
            Split2Vector(strKey,"/",vecNode);

            auto poNode = m_poRootNode;
            auto iter = vecNode.begin();
            for(; iter!=vecNode.end(); ++iter){
                auto poTmp = poNode->GetNode(*iter); //寻找匹配
                if(!poTmp){//未找到节点
                    vector<string> vecTmp;
                    std::copy(iter,vecNode.end(),vecTmp.begin());
                    Insert(poTmp,vecTmp,dwFreqLimitCnt);
                    return;
                }

                poNode = poTmp;
            }

            if(!poNode->IsComplete()){
                poNode->SetCompleteFlag(true);
            }
        }

        void Insert(shared_ptr<TrieNode> poBeg, const vector<string>& vecInsertNode,const uint32_t dwFreqLimitCnt){
            auto poNode = poBeg;
            for(int i=0; i<vecInsertNode.size();++i){
                if(i == vecInsertNode.size()-1){//最后一个节点
                    poNode->SetNode(vecInsertNode[i],make_shared<TrieNode>(vecInsertNode[i], dwFreqLimitCnt));
                    poNode->GetNode(vecInsertNode[i])->SetCompleteFlag(true);
                }else{
                    poNode->SetNode(vecInsertNode[i],make_shared<TrieNode>(vecInsertNode[i],0));
                }
            }
        }

        shared_ptr<TrieNode> Find(const string& strKey, bool& bIsFind){
            vector<string> vecNode;
            Split2Vector(strKey,"/",vecNode);
            auto poNode = m_poRootNode;
            for(const auto& strNode: vecNode){
                auto poTmp = poNode->GetNode(strNode); //寻找匹配
                if(!poTmp){//未找到节点
                    bIsFind = false;
                    return poNode; //返回上一层节点
                }

                poNode = poTmp;
            }

            if(!poNode->IsComplete()){
                cout<<"not complete: "<<poNode->GetValue()<<endl;
                bIsFind = false;
                return poNode;
            }

            bIsFind = true;
            return poNode;
        }

    private:
        shared_ptr<TrieNode> m_poRootNode;
};

int main(void){
    Trie oTrie;
    oTrie.AddNode("/china/hunan/hengyang/leiyang/zheqiao/miaoxia",1000);
    bool bIsFind;
    auto poNode = oTrie.Find("/china",bIsFind);
    if(poNode){
        if(bIsFind){
            cout<<"find. the last node value is: "<<poNode->GetValue()<<" freqlimit: "<<poNode->GetFreqLimitCnt()<<endl;
        }else{
            cout<<"not find. the before node value is: "<<poNode->GetValue()<<endl;
        }
    }
    return 0;
}

