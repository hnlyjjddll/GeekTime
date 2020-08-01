//
// Created by jdl on 2020/8/1.
//

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Video{
public:
    virtual void play(){}
};

class ShortVideo:public Video{
public:
    void play() override {
        cout<<"douyin"<<endl;
    }
};

class Reporter:public Video{
public:
    Reporter(shared_ptr<Video> poVideo):m_poVideo(poVideo){}
    void play()override{
        cout<<"begin"<<endl;
        m_poVideo->play();
        cout<<"report"<<endl;
    }
private:
    shared_ptr<Video> m_poVideo;
};

int main(void){
    auto poReport = make_shared<Reporter>(make_shared<ShortVideo>());
    poReport->play();
    return 0;
}