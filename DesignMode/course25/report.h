//
// Created by jdl on 2020/7/26.
//

#ifndef STUDY_REPORT_H
#define STUDY_REPORT_H

namespace Report{
    class ReportSvr{
        void ReportSvr();
        //省略set和get
    private:
        uint64_t m_ddwBegTime;
        uint64_t m_ddwEndTime;
    };
}

#endif //STUDY_REPORT_H
