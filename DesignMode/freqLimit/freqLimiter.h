//
// Created by jdl on 2020/8/15.
//

#pragma once

#include "freqLimitConfig.h"
#include "freqLimitRule.h"
#include "freqLimitAlg.h"

class FreqLimiter{
public:
  static const FreqLimiter& GetInstance() {
    return s_freqLimiter;
  }

  bool NeedFreqLimit(const string& strIfName, const string& strCaller){
    return m_poAlg->NeedFreqLimit(strIfName,strCaller);
  }
private:
  FreqLimiter(){
    //读取配置
    shared_ptr<AbstractFreqLimitConfig> poCfg = make_shared<JsonFreqLimitConfig>();//可以从配置读取
    poCfg->ReadConfigByFile("/root","json");
    //将配置转换为规则
    shared_ptr<Trie> poTrie = make_shared<Trie>();
    shared_ptr<AbstractFreqLimitRule> poRule = make_shared<TrieFreqLimitRule>(poTrie);
    poRule->ConvertConfig2Rule(poCfg);
    //创建算法
    m_poAlg = make_shared<TokenFreqLimitAlg>(poRule);
  }

private:
  static FreqLimiter s_freqLimiter;
  shared_ptr<AbstractFreqLimitAlg> m_poAlg;
};

FreqLimiter FreqLimiter::s_freqLimiter;

int main(void){
  FreqLimiter::GetInstance().NeedFreqLimit();
  return 0;
}