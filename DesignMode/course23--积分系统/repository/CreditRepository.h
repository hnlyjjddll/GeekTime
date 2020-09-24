//
// Created by jdl on 2020/7/22.
//积分数据层服务
//

#ifndef STUDY_CREDITRESPOSITORY_H
#define STUDY_CREDITRESPOSITORY_H

#include <string>
#include "Repository.h"

namespace CreditRepository{
    class CreditRepositorySvr{
    public:
        CreditRepositorySvr(const Repository::AbstractRepositoryAccess& oAbstractRepositoryAccess):m_oRepository(oAbstractRepositoryAccess){} //依赖注入
        int32_t AddCredit(const std::string& strUin, const uint32_t dwCreditValue);
        int32_t SubCredit(const std::string& strUin, const uint32_t dwCreditValue){}
        int32_t GetCredit(const std::string& strUin, uint64_t& ddwCreditValue){}
    private:
        //抽象存储层，统一公共接口
        Repository::AbstractRepositoryAccess m_oRepository;
    };
}
#endif //STUDY_CREDITRESPOSITORY_H
