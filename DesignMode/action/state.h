//
// Created by jdl on 2020/8/5.
//

#ifndef STUDY_STATE_H
#define STUDY_STATE_H

#include <string>

class MarioStateMachine;
class SmallState;
class BigState;
class FireState;
class FlyState;

class IState{
public:
    virtual const std::string GetName(){}
    virtual void EatMushroom(MarioStateMachine& oStateMachine){}
    virtual void EatIce(MarioStateMachine& oStateMachine){}
    virtual void GetCape(MarioStateMachine& oStateMachine){}
    virtual void MeetMonster(MarioStateMachine& oStateMachine){}
};

class SmallState:public IState{
public:
    const std::string GetName() override ;
    static SmallState& GetInstance();
    void EatMushroom(MarioStateMachine& oStateMachine) override ;

    void EatIce(MarioStateMachine& oStateMachine) override;

    void MeetMonster(MarioStateMachine& oStateMachine) override;
private:
    SmallState(){}
private:
    static SmallState* m_poState;
};


class BigState:public IState{
public:
    const std::string GetName()override ;
    static BigState& GetInstance();

    void EatIce(MarioStateMachine& oStateMachine) override;

    void MeetMonster(MarioStateMachine& oStateMachine) override;
private:
    BigState(){}
private:
    static BigState* m_poState;
};

class FireState:public IState{
public:
    const std::string GetName()override ;
    static FireState& GetInstance();
    void GetCape(MarioStateMachine& oStateMachine) override ;

    void MeetMonster(MarioStateMachine& oStateMachine) override;
private:
    FireState(){}
private:
    static FireState* m_poState;
};

class FlyState:public IState{
public:
    const std::string GetName()override ;
    static FlyState& GetInstance();

    void MeetMonster(MarioStateMachine& oStateMachine) override;
private:
    FlyState(){}
private:
    static FlyState* m_poState;
};

class MarioStateMachine{
public:
    MarioStateMachine();
    IState* GetCurrentState(){
        return m_poState;
    }
    uint32_t GetScore()const{
        return m_dwScore;
    }
    void SetState(IState* poState){
        m_poState = poState;
    }

    void SetScore(uint32_t dwScore){
        m_dwScore = dwScore;
    }
    const std::string GetName();

    void EatMushroom();

    void EatIce();
    void GetCape();
    void MeetMonster();
private:
    IState* m_poState;
    uint32_t m_dwScore;
};


#endif //STUDY_STATE_H
