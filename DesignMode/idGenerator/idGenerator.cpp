#include <iostream>
#include <memory>
#include <uuid/uuid.h>
#include <chrono>
#include "idGenerator.h"

using namespace std;

int32_t UuidIdGenerator::GenerateId(uint32_t dwBusiId, std::string &strId) {
  int32_t iRet = 0;
  if (!IsValidBusiId(dwBusiId)) {
    cout << "busi id: " << dwBusiId << " is invalid" << endl;
    return -1;
  }

  uuid_t binUuid;//二进制数组
  uuid_generate(binUuid);//生成的uuid是16字节，可以认为是全球唯一的
  char strUuid[37];
  uuid_unparse_lower(binUuid, strUuid);//二进制的uuid将转换为37字节长度的string，其中最后一个字符是‘\0’
  strId.assign(string{std::begin(strUuid), std::end(strUuid)});

  return iRet;
}

int32_t SnowFlakeIdGenerator::GenerateId(uint32_t dwBusiId, std::string &strId) {
  int32_t iRet = 0;

  uint64_t ddwCurrentMsTime = _GetCurrentMsTimeStamp();
  cout<<"current ms timestamp: "<<ddwCurrentMsTime<<endl;

  uint64_t ddwId = 0;
  uint32_t dwMachineId = 123&0x3ff; //10bit表示机器号

  if(ddwCurrentMsTime == m_ddwLastMsTimeStamp){//同一毫秒内分配
    m_dwInnerSeqId = (m_dwInnerSeqId + 1) & 0xfff;
    if(m_dwInnerSeqId == 0){//毫秒内重复了
      //阻塞到下一个毫秒时间戳
      ddwCurrentMsTime = _Wait2NextMsTimeStamp();
    }
  }else if(ddwCurrentMsTime > m_ddwLastMsTimeStamp){
    m_dwInnerSeqId = 0;
  }else{
    cout<<"时间戳返祖了"<<endl;
    return -1;
  }

  ddwId = (ddwCurrentMsTime << 22) | (dwMachineId<<12) | m_dwInnerSeqId;
  m_ddwLastMsTimeStamp = ddwCurrentMsTime;
  strId.assign(to_string(ddwId));

  return iRet;
}

uint64_t SnowFlakeIdGenerator::_GetCurrentMsTimeStamp() const {
  auto tMesc = chrono::time_point_cast<chrono::milliseconds>(chrono::system_clock::now());
  return tMesc.time_since_epoch().count();
}

uint64_t SnowFlakeIdGenerator::_Wait2NextMsTimeStamp() const {
  uint64_t ddwCurrentMsTime;
  do{
    ddwCurrentMsTime = _GetCurrentMsTimeStamp();
  }while(ddwCurrentMsTime == m_ddwLastMsTimeStamp);

  return ddwCurrentMsTime;
}

int main(void) {
  shared_ptr<AbstractIdGenerator> poIdGenerator = make_shared<UuidIdGenerator>(set<uint32_t>{1, 2, 3, 4});
  string strId;
  int32_t iRet = poIdGenerator->GenerateId(1, strId);
  if (iRet != 0) {
    cout << "GenerateId error. iRet: " << iRet << endl;
    return iRet;
  }

  cout << "strId: " << strId << endl;

  poIdGenerator = make_shared<SnowFlakeIdGenerator>(set<uint32_t>{1, 2, 3, 4});
  iRet = poIdGenerator->GenerateId(1, strId);
  if (iRet != 0) {
    cout << "GenerateId error. iRet: " << iRet << endl;
    return iRet;
  }

  cout << "strId: " << strId << endl;
  return 0;
}