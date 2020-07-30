//
// Created by jdl on 2020/7/26.
//

#ifndef STUDY_STORAGE_H
#define STUDY_STORAGE_H

namespace Storage{
    class AbstractStorage{
    public:
        //需要统一读写格式，包括入参和返回数据格式
        virtual int32_t Write();
        virtual int32_t Read(); //一次性取太长时间区间的数据，可能会导致拉取太多的数据到内存中，有可能会撑爆内存
    };

    class RedisStorage: public AbstractStorage{
    public:
        virtual int32_t Write() override ;
        virtual int32_t Read() override ;
    };

    class StorageSvr{
    public:
        StorageSvr(const std::shared_ptr<AbstractStorage> poStorage):m_poStorage(poStorage) {}
        //消费订阅上报数据,存入存储
        void Consume();
    private:
        std::shared_ptr<AbstractStorage> m_poStorage;
    };
}

#endif //STUDY_STORAGE_H