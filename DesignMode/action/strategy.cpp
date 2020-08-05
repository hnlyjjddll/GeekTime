//
// Created by jdl on 2020/8/2.
//


#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;

class IFavor{
public:
    virtual void CalculateFavor() = 0;
};

class CouponFavor:public IFavor{
public:
    virtual void CalculateFavor()override  {cout<<"coupon"<<endl;}
};

class MemberFavor:public IFavor{
    public:
    virtual void CalculateFavor() override{
        cout<<"member"<<endl;
    }
};


class FavorFactory{
public:
    static shared_ptr<IFavor> CreateFavor(const std::string& strKey){
        if(mapFavor.find(strKey) == mapFavor.end()){
            return nullptr;
        }

        return mapFavor.at(strKey);
    }
private:
    static map<string,shared_ptr<IFavor>> mapFavor;
};

map<string,shared_ptr<IFavor>> FavorFactory::mapFavor = {
        {"coupon",make_shared<CouponFavor>()},
        {"member",make_shared<MemberFavor>()}
};

int main(void){
    auto poFavor = FavorFactory::CreateFavor("coupon");
    poFavor->CalculateFavor();
    return 0;
}