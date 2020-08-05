//
// Created by jdl on 2020/8/4.
//

#include <iostream>
#include <string>
#include "state.h"
using namespace std;

SmallState* SmallState::m_poState = nullptr;
BigState* BigState::m_poState = nullptr;
FireState* FireState::m_poState = nullptr;
FlyState* FlyState::m_poState = nullptr;

const std::string SmallState::GetName(){
    return "small";
}

SmallState& SmallState::GetInstance(){
    if(!m_poState){
        m_poState = new SmallState;
    }

    return *m_poState;
}

void SmallState::EatMushroom(MarioStateMachine& oStateMachine)  {
    oStateMachine.SetState(&BigState::GetInstance());
    oStateMachine.SetScore(oStateMachine.GetScore()+100);
}

void SmallState::EatIce(MarioStateMachine& oStateMachine) {
    oStateMachine.SetState(&FireState::GetInstance());
    oStateMachine.SetScore(oStateMachine.GetScore()+100);
}

void SmallState::MeetMonster(MarioStateMachine& oStateMachine) {
    oStateMachine.SetState(&SmallState::GetInstance());
    oStateMachine.SetScore(oStateMachine.GetScore()-300);
}


const std::string BigState::GetName(){
    return "big";
}

BigState& BigState::GetInstance(){
    if(!m_poState){
        m_poState = new BigState;
    }

    return *m_poState;
}

void BigState::EatIce(MarioStateMachine& oStateMachine) {
    oStateMachine.SetState(&FireState::GetInstance());
    oStateMachine.SetScore(oStateMachine.GetScore()+200);
}

void BigState::MeetMonster(MarioStateMachine& oStateMachine) {
    oStateMachine.SetState(&SmallState::GetInstance());
    oStateMachine.SetScore(oStateMachine.GetScore()-300);
}



const std::string FireState::GetName(){
    return "fire";
}
FireState& FireState::GetInstance(){
    if(!m_poState){
        m_poState = new FireState;
    }

    return *m_poState;
}
void FireState::GetCape(MarioStateMachine& oStateMachine)  {
    oStateMachine.SetState(&FlyState::GetInstance());
    oStateMachine.SetScore(oStateMachine.GetScore()+300);
}

void FireState::MeetMonster(MarioStateMachine& oStateMachine) {
    oStateMachine.SetState(&SmallState::GetInstance());
    oStateMachine.SetScore(oStateMachine.GetScore()-300);
}

const std::string FlyState::GetName(){
    return "fly";
}

FlyState& FlyState::GetInstance(){
    if(!m_poState){
        m_poState = new FlyState;
    }

    return *m_poState;
}

void FlyState::MeetMonster(MarioStateMachine& oStateMachine) {
    oStateMachine.SetState(&SmallState::GetInstance());
    oStateMachine.SetScore(oStateMachine.GetScore()-300);
}

MarioStateMachine::MarioStateMachine():m_dwScore(0){
    m_poState = &SmallState::GetInstance();
}

const std::string MarioStateMachine::GetName(){
    return m_poState->GetName();
}

void MarioStateMachine::EatMushroom(){
    m_poState->EatMushroom(*this);
}

void MarioStateMachine::EatIce(){
    m_poState->EatIce(*this);
}
void MarioStateMachine::GetCape(){
    m_poState->GetCape(*this);
}
void MarioStateMachine::MeetMonster(){
    m_poState->MeetMonster(*this);
}


int main(void){
    MarioStateMachine oStateMachine;
    cout<<oStateMachine.GetName()<<" "<<oStateMachine.GetScore()<<endl;

    oStateMachine.EatMushroom();
    cout<<oStateMachine.GetName()<<" "<<oStateMachine.GetScore()<<endl;

    oStateMachine.EatIce();
    cout<<oStateMachine.GetName()<<" "<<oStateMachine.GetScore()<<endl;

    oStateMachine.GetCape();
    cout<<oStateMachine.GetName()<<" "<<oStateMachine.GetScore()<<endl;

    oStateMachine.MeetMonster();
    cout<<oStateMachine.GetName()<<" "<<oStateMachine.GetScore()<<endl;

    return 0;
}
