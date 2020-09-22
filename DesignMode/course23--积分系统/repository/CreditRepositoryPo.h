//
// Created by jdl on 2020/7/22.
//

#ifndef STUDY_CREDITREPOSITORYPO_H
#define STUDY_CREDITREPOSITORYPO_H

#include <string>

namespace CreditRepositoryPo{
    class CreditRepositoryPo{
        class CreditDetailPo{
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
    };
}

#endif //STUDY_CREDITREPOSITORYPO_H
