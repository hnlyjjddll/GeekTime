//
// Created by jdl on 2020/7/17.
//

#ifndef STUDY_APIREQUEST_H
#define STUDY_APIREQUEST_H

#include <string>

struct BaseApiRequestBody{
    BaseApiRequestBody(
        const std::string& strAppid,
        const std::string& strToken,
        const uint64_t ddwCreateTime):
        m_strAppid(strAppid),
        m_strToken(strToken),
        m_ddwCreateTime(ddwCreateTime) {}
    BaseApiRequestBody(const BaseApiRequestBody& rhs){
        if(&rhs != this){
            this->m_ddwCreateTime = rhs.m_ddwCreateTime;
            this->m_strAppid = rhs.m_strAppid;
            this->m_strToken = rhs.m_strToken;
        }
    }

    const std::string& GetAppid() const {return m_strAppid;}
    const std::string& GetToken() const {return m_strToken;}
    const uint64_t GetCreateTime() const {return m_ddwCreateTime;}

private:
    std::string m_strAppid;
    std::string m_strToken;
    uint64_t m_ddwCreateTime;
};

struct UrlApiRequestBody: public BaseApiRequestBody{
    UrlApiRequestBody(
        const std::string strUrl,
        const std::string& strAppid,
        const std::string& strToken,
        const uint64_t ddwCreateTime):
            BaseApiRequestBody(strAppid,strToken,ddwCreateTime),
            m_strUrl(strUrl) {}
    UrlApiRequestBody(const UrlApiRequestBody& rhs):BaseApiRequestBody(rhs){
        if(&rhs != this){
            this->m_strUrl = rhs.m_strUrl;
        }
    }

    const std::string& GetUrl() const {return m_strUrl;}
private:
    std::string m_strUrl;
};

struct RpcApiRequestBody: public BaseApiRequestBody{
    //RPC request
};

class AbstractApiRequest{
public:
    virtual const std::string& GetAppid() const = 0;
    virtual const std::string& GetToken() const  = 0;
    virtual const uint64_t GetCreateTime() const = 0;
};

class UrlApiRequest:public AbstractApiRequest{
public:
    UrlApiRequest(const UrlApiRequestBody& oUrlRequestBody):
    m_oUrlRequestBody(oUrlRequestBody) {}

    const std::string GenerateFullUrl() const;
    virtual const std::string& GetAppid() const override {return m_oUrlRequestBody.GetAppid();}
    virtual const std::string& GetToken() const override {return m_oUrlRequestBody.GetToken();};
    virtual const uint64_t GetCreateTime() const override {return m_oUrlRequestBody.GetCreateTime();}
    const std::string& GetUrl() const {return m_oUrlRequestBody.GetUrl();}
private:
    UrlApiRequestBody m_oUrlRequestBody;
};

#endif //STUDY_APIREQUEST_H
