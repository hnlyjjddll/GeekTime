//
// Created by jdl on 2020/7/22.
//

#include "CreditApplication.h"
#include "CreditChangeRuleSvr.h"
#include "CreditDomainSvr.h"
#include "CreditDo.h"

int32_t CreditApplicationSvr::ReceiveCreditAfterTrade(
        const std::string& strUin,
        const std::string& strTradeId,
        const float fTradeAmount,
        uint64_t& ddwCreditId){

    //访问积分兑换系统获取 交易金额兑换的积分值
    //RuleId: 系统分配（可以实现为读取系统配置）
    uint32_t dwRuleId = 123;
    uint64_t ddwCreditValue; //兑换的积分值
    int32_t iRet = CreditChangeRule::GetCreditAfterPay(123, fTradeAmount,ddwCreditValue);

    //更新积分系统
    CreditDo::CreditDetailDo oCreditDetailDo;
    //fill CreditDetailDo
    uint64_t ddwCreditId;
    iRet = CreditDomain::AddCreditByUser(strUin, oCreditDetailDo,ddwCreditId);

    return iRet;
}


