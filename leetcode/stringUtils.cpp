//
// Created by jdl on 2020/11/17.
//

#include <map>
#include <set>
#include <vector>
#include <list>
#include <iostream>
#include <cstring>

using namespace std;

template<class T>
int StrSplit(const string& strSrc,const string& strDelimiter,T& result){
  if(strSrc.empty()) return -1;

  result.clear();

  int iSize = strSrc.size();
  int i = iSize-1;
  auto iter = result.begin();
  while(i >= 0){
    int iPos = strSrc.rfind(strDelimiter,i);
    if(iPos == string::npos){
      break;
    }

    if(iPos == i){
      //末尾分隔符特殊处理
      i = iPos - 1;
      continue;
    }

    int iBeg = iPos + strDelimiter.size();
    int iSubStringSize = i - iBeg + 1;
    iter = result.insert(iter,strSrc.substr(iBeg,iSubStringSize));
    i = iPos - 1;
  }

  if(i >= 0){
    result.insert(iter,strSrc.substr(0,i+1));
  }

  return 0;
}

bool StartWith(const std::string& strSrc,const std::string& strStartStr){
  if(strStartStr.empty()){
    return true;
  }

  auto pSrc = strSrc.c_str();
  auto pStart = strStartStr.c_str();
  printf("pStart=%s size=%d\n",pStart,strlen(pStart));
  if(!pStart){
    return true;
  }

  if(!pSrc){
    return false;
  }

  return strncmp(pSrc,pStart,strlen(pStart)) == 0;
}


int main(void){
  std::string strSrc= "123";
  std::string strStartStr("\0");
  strStartStr.append("123");
  cout<<strSrc.size()<<" "<<strStartStr.size()<<endl;
  if(strSrc == strStartStr){
    cout<<"equal"<<endl;
  }else{
    cout<<"not equal"<<endl;
  }

  cout<<StartWith(strSrc,strStartStr)<<endl;
  return 0;
}