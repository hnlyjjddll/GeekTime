//
// Created by jdl on 2020/7/22.
//

#include "CreditChangeRuleSvr.h"

int32_t CreditChangeRuleSvr::GetCreditAfterPay(const uint32_t dwRuleId, const float fPayAmount, uint64_t& ddwCreditValue){
    ddwCreditValue = fPayAmount * m_fPayAmountChangeCreditRatio;
    return 0;
}