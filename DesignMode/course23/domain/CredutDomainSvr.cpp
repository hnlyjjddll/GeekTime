//
// Created by jdl on 2020/7/22.
//
#include "CreditDomainSvr.h"
#include "CreditRepository.h"
#include "CreditLogRepository.h"

int32_t CreditDomainSvr::AddCreditByUser(const std::string& strUin, const CreditDo::CreditDetailDo& oCreditDetailDo, uint64_t& ddwCreditId){
    //事务开始

    //写交易流水
    CreditRepositoryPo::CreditRepositoryPo oCreditRepositoryPo;
    int32_t iRet = CreditLogRepository::SaveCreditLog(strUin,oCreditRepositoryPo);

    //更新积分值
    iRet =  CreditRepository::AddCredit(strUin, oCreditDetailDo.GetCreditValue());

    //事务结束

    return 0;
}