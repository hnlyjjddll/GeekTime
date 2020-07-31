//
// Created by jdl on 2020/7/30.
//

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Car{
public:
    virtual void drive(){cout<<"drive car"<<endl;}
};

class BusCar:public Car{
public:
    void drive() override{cout<<"buscar"<<endl;}
};

class BycycleCar:public Car{
public:
    void drive() override {cout<<"bycyclecar"<<endl;}
};

class CreateCarFactory{
public:
    const static std::map<int,Car*> mapCar;
    static Car* CreateCar(int type) {
        if(mapCar.find(type) == mapCar.end()){
            return nullptr;
        }

        return mapCar.at(type);
    }
};

const map<int,Car*> CreateCarFactory::mapCar = {
        {1,new BusCar()},
        {2,new BycycleCar()}
};


int main(void){
    Car* car = CreateCarFactory::CreateCar(1);
    car->drive();
    Car* car2 = CreateCarFactory::CreateCar(2);
    car2->drive();
    return 0;
}