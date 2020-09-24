//
// Created by jdl on 2020/7/22.
// 积分规则领域服务
//

#ifndef STUDY_CREDITCHANGERULESVR_H
#define STUDY_CREDITCHANGERULESVR_H

namespace CreditChangeRule{
    class CreditChangeRuleSvr{
    public:
        int32_t GetCreditAfterPay(const uint32_t dwRuleId, const float fPayAmount, uint64_t& ddwCreditValue); //支付后根据订单金额兑换积分
        int32_t GetCreditAfterLogging(const uint32_t dwRuleId, uint64_t& ddwCreditValue){} //签到后领取积分
        int32_t ConsumeCreditAfterChangeCoupon(const uint32_t dwRuleId, const float fCouponValue, uint64& ddwCreditValue){} //兑换代金券消耗积分
    private:
        float m_fCreditChangeMoneyRatio; //积分兑换现金比例
        float m_fPayAmountChangeCreditRatio; //支付金额兑换积分比例
        uint32_t m_dwCreditValuePerLog; //每日签到获取积分值
        uint32_t m_dwRuleId; //规则id
        uint32_t m_dwRuleType; //规则type
    };
}

#endif //STUDY_CREDITCHANGERULESVR_H
