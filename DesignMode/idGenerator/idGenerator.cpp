#include <iostream>
#include <memory>
#include <uuid/uuid.h>
#include "idGenerator.h"

using namespace std;

int32_t UuidIdGenerator::GenerateId(uint32_t dwBusiId, std::string& strId){
    int32_t iRet = 0;
    if(!IsValidBusiId(dwBusiId)){
        cout<<"busi id: "<<dwBusiId<<" is invalid"<<endl;
        return -1;
    }

    uuid_t binUuid;//二进制数组
    uuid_generate(binUuid);//生成的uuid是16字节，可以认为是全球唯一的
    char strUuid[37];
    uuid_unparse_lower(binUuid,strUuid);//二进制的uuid将转换为37字节长度的string，其中最后一个字符是‘\0’
    strId.assign(string{std::begin(strUuid), std::end(strUuid)});

    return iRet;
}

int32_t SnowFlakeIdGenerator::GenerateId(uint32_t dwBusiId, std::string& strId){
    int32_t iRet = 0;

    return iRet;
}

int main(void){
    shared_ptr<AbstractIdGenerator> poIdGenerator = make_shared<UuidIdGenerator>(set<uint32_t>{1,2,3,4});
    string strId;
    int32_t iRet = poIdGenerator->GenerateId(1,strId);
    if(iRet != 0){
        cout<<"GenerateId error. iRet: "<<iRet<<endl;
        return iRet;
    }

    cout<<"strId: "<<strId<<endl;
    return 0;
}