#pragma

#include <string>
#include <stdint.h>
#include "AuthData.h"

struct AuthToken{
public:
    AuthToken(
            const std::string& strUrl,
            const std::string& strAppid,
            const uint64_t ddwCreateTime):
            m_strUrl(strUrl),
            m_strAppid(strAppid),
            m_ddwCreateTime(ddwCreateTime) {}

    bool IsExpired() const;
    bool Match(const std::string& strToken);
private:
    std::string _GenerateToken(const AbstractAuthData& oAuthData);
private:
    static uint64_t EXPIRE_INTERVAL;  //精确到毫秒

    std::string m_strUrl;
    std::string m_strAppid;
    uint64_t m_ddwCreateTime;
};