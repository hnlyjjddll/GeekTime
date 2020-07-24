//
// Created by jdl on 2020/7/22.
//

#ifndef STUDY_REPOSITORY_H
#define STUDY_REPOSITORY_H

#include <string>

namespace Repository{
    class AbstractRepositoryAccess{
    public:
        virtual int32_t Read(const std::string& m_strReq, std::string& m_strResp) {}
        virtual int32_t Write(const std::string& m_strReq, std::string& m_strResp){}
    };

    class MysqlRepositoryAccess: public AbstractRepositoryAccess {
    public:
        int32_t Read(const std::string& m_strReq, std::string& m_strResp) override;
        int32_t Write(const std::string& m_strReq, std::string& m_strResp) override;
    };
}

#endif //STUDY_REPOSITORY_H
