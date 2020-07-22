//
// Created by jdl on 2020/7/22.
// 积分流水数据层服务
//

#ifndef STUDY_CREDITLOGRESPOSITORY_H
#define STUDY_CREDITLOGRESPOSITORY_H

#include <string>
#include "CreditRepositoryPo.h"

namespace CreditLogRepository{
    class CreditLogRepository{
        CreditLogRepository(const Repository::AbstractRepositoryAccess& oAbstractRepositoryAccess):m_oRepository(oAbstractRepositoryAccess){} //依赖注入
        int32_t SaveCreditLog(const std::string& strUin, const CreditRepositoryPo::CreditRepositoryPo& oCreditRepositoryPo);
        int32_t GetCreditLog(const std::string& strUin, uint64_t& ddwCreditValue){}
    private:
        //抽象存储层，统一公共接口
        Repository::AbstractRepositoryAccess m_oRepository;
    };
}

#endif //STUDY_CREDITLOGRESPOSITORY_H
