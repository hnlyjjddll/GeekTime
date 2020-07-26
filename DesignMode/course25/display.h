//
// Created by jdl on 2020/7/26.
//

#ifndef STUDY_DISPLAY_H
#define STUDY_DISPLAY_H

namespace Display{

    class StatisticFilter{
    public:
        //省略set和get方法
    private:
        uint32_t m_dwPageSize;
        uint32_t m_dwPageId;
        uint64_t m_ddwBegTime;
        uint64_t m_ddwEndTime
    };

    class AbstractDisplayFormat{
    public:
        virtual void Format(const std::vector<std::string>& strSourc, std::string& strOutput);
    };

    class JsonDisplayFormat:public AbstractDisplayFormat{
    public:
        virtual void Format(const std::vector<std::string>& strSourc, std::string& strOutput) override ;
    };

    class HtmlDisplayFormat:public AbstractDisplayFormat{
    public:
        virtual void Format(const std::vector<std::string>& strSourc, std::string& strOutput) override ;
    };

    class TextDisplayFormat:public AbstractDisplayFormat{
    public:
        virtual void Format(const std::vector<std::string>& strSourc, std::string& strOutput) override ;
    };

    class AbstractDisplay{
    public:
        virtual void Display(const std::shared_ptr<AbstractStorage> poStorage, const std::shared_ptr<AbstractDisplayFormat> poFormat);
    };

    class ConsoleDisplay:public AbstractDisplay{
    public:
        ConsoleDisplay(const uint32 dwTimeInterval):m_dwTimeInterval(dwTimeInterval){}
        virtual void Display(const std::shared_ptr<AbstractStorage> poStorage, const std::shared_ptr<AbstractDisplayFormat> poFormat) override;
    private:
        uint32_t m_dwTimeInterval;
    };

    class WebCfg{
    public:
        //省略set和get方法
    private:
        std::string m_strUrl;
        uint64_t m_ddwBeginTime;
    };
   class WebDisplay:public AbstractDisplay{
   public:
       WebDisplay(const WebCfg& oWebCfg):m_oWebCfg(oWebCfg){}
       virtual void Display(const std::shared_ptr<AbstractStorage> poStorage, const std::shared_ptr<AbstractDisplayFormat> poFormat) override;
   private:
       WebCfg m_oWebCfg;
   };
}

#endif //STUDY_DISPLAY_H
