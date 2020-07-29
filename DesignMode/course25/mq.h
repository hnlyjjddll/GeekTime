//
// Created by jdl on 2020/7/26.
//

#ifndef STUDY_MQ_H
#define STUDY_MQ_H

class KafkaCfg{
public:
    //省略set和get
private:
    std::string m_oKafkaServerAddr;
};

class KafkaMq{
public:
    void Product(const std::string& strTopic, const std::string& strData){}
private:
    KafkaCfg m_oKafkaCfg;
};

#endif //STUDY_MQ_H
