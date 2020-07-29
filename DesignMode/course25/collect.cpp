//
// Created by jdl on 2020/7/26.
//

#include "collect.h"

void Collect::CollectSvr::Report(){
    //抛MQ
    std::string strData;
    oMq.Product("",stdData);
}
