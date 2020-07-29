//
// Created by jdl on 2020/7/26.
//

#ifndef STUDY_COLLECT_H
#define STUDY_COLLECT_H

#include "mq.h"

namespace Collect{
    class CollectSvr{
        void Report(const KafKaMq& oMq);
        //省略set和get
    private:
        std::string m_strAppName;
        uint64_t m_ddwBegTime;
        uint64_t m_ddwEndTime;
    };
}

#endif //STUDY_COLLECT_H
