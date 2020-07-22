//
// Created by jdl on 2020/7/22.
//

#include "CreditLogRepository.h"

int32_t CreditLogRepository::SaveCreditLog(const std::string& strUin, const CreditRepositoryPo::CreditRepositoryPo& oCreditRepositoryPo){
    return m_oRepository.Read("req",strResp);
}