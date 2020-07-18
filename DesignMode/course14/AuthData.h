//
// Created by djangojiang on 2020/7/18.
//

#ifndef STUDY_AUTHDATA_H
#define STUDY_AUTHDATA_H

#include <string>

class AbstractAuthData{
public:
    virtual const std::string GetAppsecretByAppid(const std::string& strAppid) const = 0;
};

class MysqlAuthData: public AbstractAuthData{
public:
    virtual const std::string GetAppsecretByAppid(const std::string& strAppid)  const override;
};


#endif //STUDY_AUTHDATA_H
