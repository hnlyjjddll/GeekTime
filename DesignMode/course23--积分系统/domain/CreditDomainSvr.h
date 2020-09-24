//
// Created by jdl on 2020/7/22.
// 积分领域服务
//

#ifndef STUDY_CREDITDOMAINSVR_H
#define STUDY_CREDITDOMAINSVR_H

#include <string>
#include "CreditDo.h"
#include "CreditRepository.h"
#include "CreditLogRepository.h"

namespace CreditDomain{
    class CreditDomainSvr{
    public:
        CreditDomainSvr(const CreditRepository& oCreditRepository, const CreditLogRepository& oCreditLogRepository)
            :m_oCreditRepository(oCreditRepository),
             m_oCreditLogRepository(oCreditLogRepository){}
        int32_t GetUserCreditDetailById(const std::string& strUin, const uint64_t dwUid, CreditDo::CreditDetailDo& oCreditDetailDo){}
        int32_t GetUserCreditListByFilter(const std::string& strUin, const CreditDo::CreditQueryFilter& oCreditQueryFilter, CreditDo::CreditListDo& oCreditListDo){}
        int32_t AddCreditByUser(const std::string& strUin, const CreditDo::CreditDetailDo& oCreditDetailDo, uint64_t& ddwCreditId);
        int32_t SubCreditByUser(const std::string& strUin, const CreditDo::CreditDetailDo& oCreditDetailDo, uint64_t& ddwCreditId){}
    private:
        CreditRepository::CreditRepository m_oCreditRepository;
        CreditLogRepository::CreditLogRepository m_oCreditLogRepository;
        uint64_t m_ddwCreditId; //积分id
        uint64_t m_ddwObtainTime;//积分领取时间
        uint64_t m_ddwUseTime; //积分使用时间
        uint64_t m_ddwCreditValue; //积分值
        uint32_t m_dwSource; //积分领取或消耗渠道，0-支付 1-签到有礼 2-活动
        std::string m_strUin;
        std::string m_strDescription; //积分描述
        std::string m_strEventId; //外部事件id，例如订单id，活动id
    };
}

#endif //STUDY_CREDITDOMAINSVR_H
