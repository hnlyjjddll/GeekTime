//
// Created by jdl on 2020/8/1.
//

#include <iostream>
#include <string>
#include <memory>
#include <map>

using namespace std;

class MsgSender{
public:
    virtual void SendMsg(const std::string& strMsg) {cout<<"send "<<strMsg<<endl;}
};

class EmailSender:public MsgSender{
public:
    void SendMsg(const std::string& strMsg) override {
        cout<<"email send "<<strMsg<<endl;
    }
};

class PhoneSender:public MsgSender{
public:
    void SendMsg(const std::string& strMsg) override {
        cout<<"phone send "<<strMsg<<endl;
    }
};

class Notify{
public:
    Notify(shared_ptr<MsgSender> poSender):m_poSender(poSender){}
    void SendNotify(const std::string& strMsg){
        m_poSender->SendMsg(strMsg);
    }
private:
    shared_ptr<MsgSender> m_poSender;
};

class UrgencyNotify:public Notify{
public:
    UrgencyNotify(shared_ptr<MsgSender> poSender):Notify(poSender){}
    void DoNotify(){
        SendNotify("urgency");
    }
};
class NormalNotify:public Notify{
public:
    NormalNotify(shared_ptr<MsgSender> poSender):Notify(poSender){}
    void DoNotify(){
        SendNotify("normal");
    }
};

class MsgSenderFactory{
public:
    static shared_ptr<MsgSender> CreateMsgSender(const std::string& strSender){
        if(mapMsgSender.find(strSender) == mapMsgSender.end()){
            return make_shared<EmailSender>();
        }else{
            return mapMsgSender.at(strSender);
        }
    }
private:
    static map<string,shared_ptr<MsgSender>> mapMsgSender;
};

map<string,shared_ptr<MsgSender>> MsgSenderFactory::mapMsgSender = {
        {"email",make_shared<EmailSender>()},
        {"phone",make_shared<PhoneSender>()}
};

int main(void){
    auto poMsgSender = MsgSenderFactory::CreateMsgSender("email");
    NormalNotify oNotify(poMsgSender);
    oNotify.DoNotify();
    return 0;
}
