//
// Created by jdl on 2020/8/15.
//

#pragma once

#include <memory>
#include "freqLimitConfig.h"

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

  /*cout<<"strSourceString: "<<strSource<<endl;
  for(const auto& strNode: vecTarget){
      cout<<strNode<<endl;
  }*/
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
  shared_ptr<TrieNode> GetNode(const string& str){
    if(m_poMapNode.find(str) != m_poMapNode.end()){
      return m_poMapNode.at(str);
    }

    return nullptr;
  }
  void SetCompleteFlag(bool bFlag){m_bIsComplete = bFlag;}
  void SetFreqLimitCnt(uint32_t dwCnt){m_dwFreqLimitCnt = dwCnt;}
  bool IsComplete(){return m_bIsComplete;}

  void Print(){
    cout<<m_strVal<<endl;
    for(const auto& oPair: m_poMapNode){
      oPair.second->Print();
    }
  }
private:
  const std::string m_strVal;
  uint32_t m_dwFreqLimitCnt;
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
        cout<<"not find node"<<endl;
        vector<string> vecTmp(iter,vecNode.end());
        /*for(const auto& strNode: vecTmp){
            cout<<strNode<<endl;
        }*/
        _Insert(poNode,vecTmp,dwFreqLimitCnt);
        return;
      }

      poNode = poTmp;
    }

    if(!poNode->IsComplete()){
      poNode->SetCompleteFlag(true);
      poNode->SetFreqLimitCnt(dwFreqLimitCnt);
    }
  }

  shared_ptr<TrieNode> Find(const string& strKey, bool& bIsFind){
    cout<<"begin find"<<endl;
    vector<string> vecNode;
    Split2Vector(strKey,"/",vecNode);
    auto poNode = m_poRootNode;
    for(const auto& strNode: vecNode){
      auto poTmp = poNode->GetNode(strNode); //寻找匹配
      if(!poTmp){//未找到节点
        bIsFind = false;
        cout<<"not find. the before node value is: "<<poNode->GetValue()<<endl;
        return poNode; //返回上一层节点
      }

      poNode = poTmp;
    }

    if(!poNode->IsComplete()){
      cout<<"find but not complete: "<<poNode->GetValue()<<endl;
      bIsFind = false;
      return poNode;
    }

    bIsFind = true;
    cout<<"find. the last node value is: "<<poNode->GetValue()<<" freqlimit: "<<poNode->GetFreqLimitCnt()<<endl;
    return poNode;
  }

  void Print(){
    cout<<"begin print"<<endl;
    m_poRootNode->Print();
  }

private:
  void _Insert(shared_ptr<TrieNode> poBeg, const vector<string>& vecInsertNode,const uint32_t dwFreqLimitCnt){
    cout<<"begin insert"<<endl;
    auto poNode = poBeg;
    for(int i=0; i<vecInsertNode.size();++i){
      if(i == vecInsertNode.size()-1){//最后一个节点
        cout<<"insert last node: "<<vecInsertNode[i]<<endl;
        poNode->SetNode(vecInsertNode[i],make_shared<TrieNode>(vecInsertNode[i], dwFreqLimitCnt));
        poNode->GetNode(vecInsertNode[i])->SetCompleteFlag(true);
      }else{
        cout<<"insert node: "<<vecInsertNode[i]<<endl;
        poNode->SetNode(vecInsertNode[i],make_shared<TrieNode>(vecInsertNode[i],0));
        poNode = poNode->GetNode(vecInsertNode[i]); //移到下一层
      }
    }
  }
private:
  shared_ptr<TrieNode> m_poRootNode;
};

class AbstractFreqLimitRule{
public:
  virtual void ConvertConfig2Rule(shared_ptr<AbstractFreqLimitConfig> poCfg) = 0;
  virtual uint32_t GetFreqLimt(const string& strCaller, const string& strIfName) = 0;
};

class TrieFreqLimitRule: public AbstractFreqLimitRule{
public:
  TrieFreqLimitRule(shared_ptr<Trie> poTrieRule):m_poTrieRule(poTrieRule){}
  void ConvertConfig2Rule(shared_ptr<AbstractFreqLimitConfig> poCfg) overrid {
    const auto& mapConfig = poCfg->GetConfigMap();
    for(const auto& oConfigItem: mapConfig){
      string strKey = "/"+oConfigItem.second.GetIfName()+"/"+oConfigItem.GetCaller();
      m_oTrieRule->AddNode(strKey, oConfigItem.second.GetLimit());
    }
  }
  uint32_t GetFreqLimt(const string& strCaller, const string& strIfName){
    string strKey = "/"+oConfigItem.second.GetIfName()+"/"+oConfigItem.GetCaller();
    bool bIsFind = false;
    auto poNode = m_oTrieRule->Find(strKey,bIsFind);
    if(poNode && bIsFind){
      return poNode->GetFreqLimitCnt();
    }

    cout<<"not set freq limit"<<endl;
    return 0;
  }
private:
  shared_ptr<Trie> m_poTrieRule;
};

class MapFreqLimitRule:AbstractFreqLimitRule{
public:
  //...
};