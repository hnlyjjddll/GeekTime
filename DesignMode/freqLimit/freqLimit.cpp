//
// Created by jdl on 2020/8/11.
//

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <memory>
#include <unistd.h>

using namespace std;

class FreqLimitConfig{
public:
    static const FreqLimitConfig& GetInstance(){
        return m_sFreqLimitCfg;
    }

    uint32_t GetFreqLimit(const string& strKey) const {
        if(m_mapFreqLimit.find(strKey) != m_mapFreqLimit.end()){
            return m_mapFreqLimit.at(strKey);
        }
        return 0;
    }

    const map<string,uint32_t>& GetFreqLimit() const{
       return m_mapFreqLimit;
    }
private:
    FreqLimitConfig(){
        m_mapFreqLimit.insert({"test",3});
    }
private:
    static FreqLimitConfig m_sFreqLimitCfg;
    map<string,uint32_t> m_mapFreqLimit;
};

FreqLimitConfig FreqLimitConfig::m_sFreqLimitCfg;


class IFreqLimit{
public:
    virtual bool NeedFreqLimit(const string& strKey, const string& strScene) = 0;
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

class TimeSlideFreqLimit: public IFreqLimit{
public:
    TimeSlideFreqLimit(){
        const auto& mapCfg = FreqLimitConfig::GetInstance().GetFreqLimit();
        for(const auto& oPair: mapCfg){
            m_mapTimeSlideWindow[oPair.first] = make_shared<TimeSlideArray>(oPair.second);
        }
    }

    bool NeedFreqLimit(const string& strKey, const string& strScene) override {
        if(m_mapTimeSlideWindow.find(strKey) == m_mapTimeSlideWindow.end()){
            cout<<"not config freq limit"<<endl;
            return false; //未配置限流
        }

        auto& poTimeSlideArray = m_mapTimeSlideWindow.at(strKey);
        int32_t iRet = poTimeSlideArray->GetAvailableNode();
        if(iRet >= 0){
            cout<<"pos: "<<iRet<<endl;
            return false;
        }

        return true;
    }

private:
    map<string,shared_ptr<TimeSlideArray>> m_mapTimeSlideWindow;
};

int main(void){
    auto poFreqLimit = new TimeSlideFreqLimit;
    for(int i=0;i<5;++i){
        if(poFreqLimit->NeedFreqLimit("test","1")){
            cout<<"i[" << i << "] need do freq limit"<<endl;
            sleep(10);
        }
    }


    return 0;
}