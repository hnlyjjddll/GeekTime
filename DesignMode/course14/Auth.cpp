//
// Created by djangojiang on 2020/7/18.
//

#include "Auth.h"
#include "AuthToken.h"
#include "AuthData.h"

int32_t Auth::AuthRequest(const AbstractApiRequest& oApiRequest){
    const auto& strAppid = oApiRequest.GetAppid();
    const auto& strToken = oApiRequest.GetToken();
    const auto& ddwCreateTime = oApiRequest.GetCreateTime();

    AuthToken oClientToken(strToken,strAppid,ddwCreateTime);

    //校验请求是否在有效时间内
    if(!oClientToken.IsExpired()){
        //请求无效
        return -1;
    }

    std::string strAppSecret = MysqlAuthData().GetAppsecretByAppid(strAppid);

    auto oServerToken = oClientToken.GenerateToken("",strAppSecret);

    if(!oServerToken.Match(oClientToken)){
        //Token 不匹配
        return -2;
    }

    return 0;
}


