//
// Created by jdl on 2020/7/22.
//

#ifndef STUDY_CREDITVO_H
#define STUDY_CREDITVO_H

#include <string>

namespace CreditVo{
    class CreditVo{
        class CreditDetailVo{
        public:
            //省略各个字段的set和get方法
        private:
            uint64_t m_ddwObtainTime;
            uint64_t m_ddwUseTime;
            uint64_t m_ddwCreditValue;
            uint32_t m_dwSource;
            std::string m_strDescription;
            std::string m_strEventId;
        };

        class CreditListVo{
            //省略set和get
        private:
            std::vector<CreditDetailVo> m_vecCreditDetailList;
        };
    };
}

#endif //STUDY_CREDITVO_H