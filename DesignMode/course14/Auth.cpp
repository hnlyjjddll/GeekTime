//
// Created by djangojiang on 2020/7/18.
//

#include "Auth.h"
#include "AuthToken.h"

int32_t Auth::AuthRequest(const AbstractApiRequest& oApiRequest){
    const auto& strAppid = oApiRequest.GetAppid();
    const auto& strToken = oApiRequest.GetToken();
    const auto& ddwCreateTime = oApiRequest.GetCreateTime();

    AuthToken authToken("",strAppid,ddwCreateTime);

    //校验请求是否在有效时间内
    if(!authToken.IsExpired()){
        //请求无效
        return -1;
    }

    if(!authToken.Match(strToken)){
        //Token 不匹配
        return -2;
    }

    return 0;
}


