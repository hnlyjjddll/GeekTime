//
// Created by jdl on 2020/7/22.
//

#include "Trade.h"
#include "CreditApplication.h"

int32_t Trade::Pay(){
    //核心逻辑...
    //抛MQ，领取积分
    uint64_t ddwCreditId;
    int32_t iRet = CreditApplication::ReceiveCreditAfterTrade("uin","trade_id",111,ddwCreditId);
}