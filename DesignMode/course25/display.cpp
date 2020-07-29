//
// Created by jdl on 2020/7/26.
//

#include "display.h"
#include "aggregate.h"

void ConsoleDisplay::Display(const std::shared_ptr<AbstractStorage> poStorage, const std::shared_ptr<AbstractDisplayFormat> poFormat){

    while(1){
        //根据过滤条件，读取db数据
        //Warning:这里数据读取格式必须统一，即读取的过滤条件，返回数据格式
        //一次性取太长时间区间的数据，可能会导致拉取太多的数据到内存中，有可能会撑爆内存
        std::vector<std::string> vecData;
        vecData = poStorage->Read();

        //聚合数据
        Aggregate::Aggregate oAggregate(vecData);
        std::string strOutput;
        oAggregate.Count(strOutput);

        //格式化返回数据
        poFormat->Format("",strOutput);

        //推送结果
        std::cout<<strOutput<<std::endl;

        sleep(m_dwTimeInterval);
    }
}

void WebDisplay::Display(const std::shared_ptr<AbstractStorage> poStorage, const std::shared_ptr<AbstractDisplayFormat> poFormat){

    while(1){
        if(time() == 1){ //推送时间到
            //根据过滤条件，读取db数据
            //Warning:这里数据读取格式必须统一，即读取的过滤条件，返回数据格式
            //根据过滤条件，读取db数据
            //Warning:这里数据读取格式必须统一，即读取的过滤条件，返回数据格式
            std::vector<std::string> vecData;
            vecData = poStorage->Read();

            //聚合数据
            Aggregate::Aggregate oAggregate(vecData);
            std::string strOutput;
            oAggregate.Count(strOutput);

            //格式化返回数据
            poFormat->Format("",strOutput);

            //推送结果
            //http调用
        }
    }
}
