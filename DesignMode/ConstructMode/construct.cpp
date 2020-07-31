//
// Created by jdl on 2020/7/31.
//

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class ServerConfig{
public:
    class ServerConfigBuild;
    const std::string& GetServerName() {
        return m_strServerName;
    }
    int32_t GetMaxNum(){
        return m_dwMaxNum;
    }
    int32_t GetMinNum(){
        return m_dwMinNum;
    }
private:
    ServerConfig(const ServerConfigBuild& oBuild):m_strServerName(oBuild.m_strServerName),m_dwMaxNum(oBuild.m_dwMaxNum),m_dwMinNum(oBuild.m_dwMinNum){}
private:
    std::string m_strServerName;
    int32_t m_dwMaxNum;
    int32_t m_dwMinNum;
public:
    class ServerConfigBuild{
    public:
        friend class ServerConfig;
        ServerConfigBuild(const std::string& strServerName):m_strServerName(strServerName){
            m_dwMaxNum = 8;
            m_dwMinNum = 0;
        }
        void SetMaxNum(int32_t dwMaxNum){m_dwMaxNum = dwMaxNum;}
        void SetMinNum(int32_t dwMinNum){m_dwMinNum = dwMinNum;}
        std::shared_ptr<ServerConfig> Build(){
            if(m_dwMinNum>m_dwMaxNum) return nullptr;

            return  make_shared<ServerConfig>(ServerConfig(*this));
        }

    private:
        std::string m_strServerName;
        int32_t m_dwMaxNum;
        int32_t m_dwMinNum;
    };
};

int main(void){
    ServerConfig::ServerConfigBuild oBuildCfg("123");
    oBuildCfg.SetMaxNum(8);
    oBuildCfg.SetMinNum(9);

    auto poCfg = oBuildCfg.Build();
    if(!poCfg){
        cout<<"build fail"<<endl;
        return -1;
    }

    cout<<poCfg->GetServerName()<<endl;

    return 0;
}
