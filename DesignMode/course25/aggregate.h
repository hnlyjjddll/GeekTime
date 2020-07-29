//
// Created by jdl on 2020/7/26.
//

#ifndef STUDY_AGGRAGATE_H
#define STUDY_AGGRAGATE_H

namespace Aggregate{
    class Aggregate{
    public:
        Aggregate(std::vector<std::string>& vecData):m_vecData(vecData) {}
        //省略set和get方法
        void Count(std::string& strOutput);
    private:
        uint64_t m_ddwMax;
        uint64_t m_ddwMin;
        float m_fAvg;
        std::vector<std::string> m_vecData;
    };
}

#endif //STUDY_AGGRAGATE_H
