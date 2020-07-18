#pragma

#include <string>
#include <stdint.h>

struct AuthToken{
public:
    AuthToken(
            const std::string& strToken,
            const std::string& strAppid,
            const uint64_t ddwCreateTime):
            m_strToken(strToken),
            m_strAppid(strAppid),
            m_ddwCreateTime(ddwCreateTime) {}

    bool IsExpired() const;
    bool Match(const AuthToken& oAuthToken);
    AuthToken GenerateToken(const std::string& strUrl,const std::string& strAppsecret);
private:
    static uint64_t EXPIRE_INTERVAL;  //精确到毫秒

    std::string m_strAppid;
    std::string m_strToken;
    uint64_t m_ddwCreateTime;
};