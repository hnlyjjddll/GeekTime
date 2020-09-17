#pragma once

#include <string>
#include <set>
#include <vector>

class AbstractIdGenerator {
public:
  AbstractIdGenerator(std::set<uint32_t> setBusiIds) {
    m_setBusiIds = setBusiIds;
  }

  virtual ~AbstractIdGenerator() {}

  virtual int32_t GenerateId(const uint32_t dwBusiId, std::string &strId) = 0;

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
 *
 * 缺陷：1 位数太长，字符串类型表示达到36字节长度 2 作为主键在db中存储不合适，影响索引性能（还是因为太长了）3 uuid是无序了，作为mysql主键时性能就大打折扣
*/
class UuidIdGenerator : public AbstractIdGenerator {
public:
  UuidIdGenerator(std::set<uint32_t> setBusiIds) : AbstractIdGenerator(setBusiIds) {}

  virtual ~UuidIdGenerator() {}

  int32_t GenerateId(const uint32_t dwBusiId, std::string &strId) override;

};

/*
 * 依赖机器时钟准确性，时钟回拨可能会导致id返祖。
 * 解决方法：zk存储节点启动时的初始时钟，获取其他节点上报的时钟进行校验
 * */
class SnowFlakeIdGenerator : public AbstractIdGenerator {
public:
  SnowFlakeIdGenerator(std::set<uint32_t> setBusiIds):
  AbstractIdGenerator(setBusiIds),
  m_dwInnerSeqId(0),
  m_ddwLastMsTimeStamp(0){}

  virtual ~SnowFlakeIdGenerator() {}

  int32_t GenerateId(const uint32_t dwBusiId, std::string &strId) override;

private:
  /*
   * 时间戳：从1970年1月1日00时00分00秒至今所经过的毫秒数（秒数，钠秒数。。。），因此时间戳是一个相对时间概念。
   * */
  uint64_t _GetCurrentMsTimeStamp() const;
  uint64_t _Wait2NextMsTimeStamp() const;
private:
  uint32_t m_dwInnerSeqId; //12位表示毫秒内序列号
  uint64_t m_ddwLastMsTimeStamp;//上一个毫秒时间戳
};