//
// Created by jdl on 2020/7/22.
//

#include "CreditRepository.h"

int32_t CreditRepositorySvr::AddCredit(const std::string& strUin, const uint32_t dwCreditValue){
    std::string strResp;
    return m_oRepository.Read("req",strResp);
}

