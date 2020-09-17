//
// Created by jdl on 2020/8/19.
//
#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

int main(void){
  map<int,int> mapSet{
          {1,1},
          {10,77},
          {3,89},
          {2,100}
  };

  unordered_map<int,int> unorderedMapSet{
          {1,1},
          {10,77},
          {3,89},
          {2,100}
  };

  cout<<"begin traverse map: "<<endl;
  for(const auto& item: mapSet){
    cout<<item.first<<","<<item.second<<endl;
  }

  cout<<"begin traverse unordered map: "<<endl;
  for(const auto& item: unorderedMapSet){
    cout<<item.first<<","<<item.second<<endl;
  }
  return 0;
}