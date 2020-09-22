//
// Created by jdl on 2020/7/22.
//

#ifndef STUDY_CREDITDO_H
#define STUDY_CREDITDO_H

#include <string>

namespace CreditDo{
    class CreditDetailDo{
    public:
        //省略各个字段的set和get方法
        uint64_t GetCreditValue() const {return m_ddwCreditValue;}
    private:
        uint64_t m_ddwObtainTime;
        uint64_t m_ddwUseTime;
        uint64_t m_ddwCreditValue;
        uint32_t m_dwSource;
        std::string m_strDescription;
        std::string m_strEventId;
    };

    class CreditListDo{
        //省略set和get
    private:
        std::vector<CreditDetailDo> m_vecCreditDetailList;
    };

    class CreditQueryFilter{
    public:
        //省略set和get
    private:
        uint64_t m_ddwObtainTimeBegin;
        uint64_t m_ddwObtainTimeEnd;
        uint32_t m_dwPageId;
        uint32_t m_dwPageSize;
        uint32_t m_dwSource;
        bool m_bAvailableUse;
    };
}

#endif //STUDY_CREDITDO_H
