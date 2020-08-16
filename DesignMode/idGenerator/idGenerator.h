#pragma once

#include <string>
#include <set>
#include <vector>

class AbstractIdGenerator{
public:
    AbstractIdGenerator(std::set<uint32_t> setBusiIds){
        m_setBusiIds = setBusiIds;
    }
    virtual ~AbstractIdGenerator(){}
    virtual int32_t GenerateId(const uint32_t dwBusiId, std::string& strId) = 0;
protected:
    bool IsValidBusiId(uint32_t dwBusiId) const {
        return m_setBusiIds.find(dwBusiId) != m_setBusiIds.end();
    }
private:
    std::set<uint32_t> m_setBusiIds;
};

/*
* UUID：通用唯一标识符
* 100ns可以生成一个(60位时间值)，因此单机生成速率为10M/s
* 算法详解可参考 https://blog.csdn.net/singebogo/article/details/77834904
*/
class UuidIdGenerator:public AbstractIdGenerator{
public:
    UuidIdGenerator(std::set<uint32_t> setBusiIds):AbstractIdGenerator(setBusiIds){}
    virtual ~UuidIdGenerator(){}
    int32_t GenerateId(const uint32_t dwBusiId, std::string& strId) override;

};

class SnowFlakeIdGenerator: public AbstractIdGenerator{
public:
    SnowFlakeIdGenerator(std::set<uint32_t> setBusiIds):AbstractIdGenerator(setBusiIds){}
    virtual ~SnowFlakeIdGenerator(){}
    int32_t GenerateId(const uint32_t dwBusiId, std::string& strId) override;
};