//
// Created by jdl on 2020/7/16.
//

#include "AuthToken.h"
#include <chrono>
#include <iostream>

using namespace std;

uint64_t AuthToken::EXPIRE_INTERVAL = 300*1000;

bool AuthToken::IsExpired() const{
    auto curTime = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    uint64_t ddwCurrentTime = curTime.time_since_epoch().count();
    cout<<ddwCurrentTime<<" "<<m_ddwCreateTime<<endl;
    return ddwCurrentTime >= m_ddwCreateTime
            &&  ddwCurrentTime < m_ddwCreateTime + EXPIRE_INTERVAL;
}

bool AuthToken::Match(const AuthToken& oAuthToken){
    return oAuthToken.m_strToken == m_strToken;
}

AuthToken AuthToken::GenerateToken(const std::string& strUrl,const std::string& strAppsecret) {
    //省略sha过程
    std::string strToken = strUrl + strAppsecret + "others";
    auto curTime = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
    uint64_t ddwCurrentTime = curTime.time_since_epoch().count();

    return AuthToken(strToken,m_strAppid,ddwCurrentTime);
}

