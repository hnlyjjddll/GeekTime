//
// Created by jdl on 2020/7/22.
//

#ifndef STUDY_CREDITAPPLICATION_H
#define STUDY_CREDITAPPLICATION_H

#include <string>
#include "CreditVo.h"

namespace CreditApplication{
    class CreditApplicationSvr{
    public:
        //对外呈现的接口应该秉持单一职责，高内聚，低耦合原则。因此这里尽量将接口拆细。不同的调用方只需要关注自己需要关注的接口
        int32_t ReceiveCreditAfterTrade(const std::string& strUin, const std::string& strTradeId, const float fTradeAmount, uint64_t& ddwCreditId);
        int32_t GetAllCreditList(const std::string& strUin, CreditVo::CreditListVo& oCreditListVo){}
        int32_t GetAvailableCreditList(const std::string& strUin, CreditVo::CreditListVo& oListVo){}
        int32_t GetCreditDetail(const std::string& strUin, const uint64_t ddwCreditId, CreditVo::CreditDetailVo& oCreditDetailVo){}
    };
}

#endif //STUDY_CREDITAPPLICATION_H
