//
// Created by jdl on 2020/8/15.
//

#pragma once

#include "freqLimitRule.h"

class AbstractFreqLimitAlg{
public:
  AbstractFreqLimitAlg(shared_ptr<AbstractFreqLimitRule> poFreqLimitRule):
  m_poFreqLimitRule(poFreqLimitRule){}
  virtual bool NeedFreqLimit(const string& strIfName, const string& strCaller) = 0;

protected:
  shared_ptr<AbstractFreqLimitRule> m_poFreqLimitRule;

};

//令牌桶限流算法
class TokenFreqLimitAlg:public AbstractFreqLimitAlg{
  TokenFreqLimitAlg(shared_ptr<AbstractFreqLimitRule> poFreqLimitRule):
  AbstractFreqLimitAlg(poFreqLimitRule){}

  bool NeedFreqLimit(const string& strIfName, const string& strCaller) override {
    return true;
  }
};

class TimeSlideNode{
public:
  TimeSlideNode():m_ddwUsedTime(0){}
  bool CanUse() const{
    if(time(0)-m_ddwUsedTime>5){
      return true;
    }

    return false;
  }

  void Use(){
    m_ddwUsedTime = time(0);
  }
private:
  uint64_t m_ddwUsedTime;
};

class TimeSlideArray{
public:
  TimeSlideArray(uint32_t dwSize){
    m_vecTimeSlide.resize(dwSize);
    m_dwCurPos = 0;
  }

  int32_t GetAvailableNode(){
    if(m_vecTimeSlide[m_dwCurPos].CanUse()){
      m_vecTimeSlide[m_dwCurPos].Use();
      uint32_t dwTmp = m_dwCurPos;
      m_dwCurPos = (m_dwCurPos+1) % m_vecTimeSlide.size();
      return dwTmp;
    }

    return -1;
  }
private:
  vector<TimeSlideNode> m_vecTimeSlide;
  uint32_t m_dwCurPos;
};

class TimeSlideFreqLimitAlg: public AbstractFreqLimitAlg{
public:
  TimeSlideFreqLimit(shared_ptr<AbstractFreqLimitRule> poFreqLimitRule):
  AbstractFreqLimitAlg(poFreqLimitRule){}

  bool NeedFreqLimit(const string& strIfName, const string& strCaller) override {
    uint32_t dwFreqLimitCnt = 0;
    if((dwFreqLimitCnt=m_poFreqLimitRule->GetFreqLimt(strCaller,strIfName)) == 0){
      cout<<"not config freq limit"<<endl;
      return false; //未配置限流
    }

    /*auto& poTimeSlideArray = m_mapTimeSlideWindow.at(strIfName+strCaller);
    int32_t iRet = poTimeSlideArray->GetAvailableNode();
    if(iRet >= 0){
      cout<<"pos: "<<iRet<<endl;
      return false;
    }*/

    return true;
  }

private:
  map<string,shared_ptr<TimeSlideArray>> m_mapTimeSlideWindow;
};
