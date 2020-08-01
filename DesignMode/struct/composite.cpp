//
// Created by jdl on 2020/8/1.
//

#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class HumanResource{
public:
    HumanResource(uint32_t id):m_oId(id),m_fSalary(0){}
    HumanResource(uint32_t id,float fSalary):m_oId(id),m_fSalary(fSalary){}
    virtual float CalculateSalary() = 0;
    virtual uint32_t GetEmployeeNum() const = 0;

protected:
    uint32_t m_oId;
    float m_fSalary;
};

class Department:public HumanResource{
public:
    Department(uint32_t dwId):HumanResource(dwId){}
    float CalculateSalary() override{
        float fSalary = 0.0;
        for(const auto& poSubDepartment: m_poSubDepartmentList){
            fSalary += poSubDepartment->CalculateSalary();
        }

        return fSalary;
    }

    uint32_t GetEmployeeNum()const override {
        uint32_t dwNum = 0;
        for(const auto& poSubDepartment: m_poSubDepartmentList){
            dwNum += poSubDepartment->GetEmployeeNum();
        }
        return dwNum;
    }

    void AddSubDepartment(shared_ptr<HumanResource> poSubDepartment){
        m_poSubDepartmentList.push_back(poSubDepartment);
    }
private:
    std::vector<shared_ptr<HumanResource>> m_poSubDepartmentList;
};

class Employee:public HumanResource{
public:
    Employee(uint32_t dwId, float fSalary):HumanResource(dwId,fSalary){}
    float CalculateSalary() override{
        return m_fSalary;
    }

    uint32_t GetEmployeeNum()const override{
        return 1;
    }

};

int main(void){
    auto poRootDepartment = make_shared<Department>(1);

    auto poVideoDepartment = make_shared<Department>(10);
    auto poVideoEmployee = make_shared<Employee>(100,133.33);
    poVideoDepartment->AddSubDepartment(poVideoEmployee);

    auto poPayDepartment = make_shared<Department>(20);
    auto poPayEmployee = make_shared<Employee>(200,13300.33);
    poPayDepartment->AddSubDepartment(poPayEmployee);

    poRootDepartment->AddSubDepartment(poVideoDepartment);
    poRootDepartment->AddSubDepartment(poPayDepartment);

    cout<<poRootDepartment->GetEmployeeNum()<<endl<<poRootDepartment->CalculateSalary()<<endl;
    return 0;
}