//
// Created by jdl on 2020/8/15.
//

#pragma once

#include <string>
#include <map>

using namespace std;

enum TIME_UNIT{
  UINT_MINUTE = 0;
  UNIT_SECOND = 1;
  UNIT_MICRO_SECOND = 2;
};

class FreqLimitConfigItem{
  FreqLimitConfigItem(const string& strCaller,const string& strIfName,uint32_t dwLimit,TIME_UNIT eUnit=UNIT_SECOND):
  m_strCaller(strCaller),
  m_strIfName(strIfName),
  m_dwLimit(dwLimit),
  m_eTimeUnit(eUnit){}

  //omit getter
private:
  const std::string m_strCaller;
  const std::string m_strIfName;
  const TIME_UNIT m_eTimeUnit;
  const uint32_t m_dwLimit;
};

class AbstractFreqLimitConfig{
public:
  virtual int32_t ReadConfigByFile(const string& strFilePath, const string& strFileName)=0;
  const map<string,FreqLimitConfigItem>& GetConfigMap() {return m_mapConfigItem;}
private:
  map<string,FreqLimitConfigItem> m_mapConfigItem;
};

class JsonFreqLimitConfig:public AbstractFreqLimitConfig{
public:
  int32_t ReadConfigByFile(const string& strFilePath, const string& strFileName) override ;
};


class XmlFreqLimitConfig:public AbstractFreqLimitConfig{
public:
  int32_t ReadConfigByFile(const string& strFilePath, const string& strFileName) override ;
};