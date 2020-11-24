//
// Created by jdl on 2020/11/6.
//

#include <cstdlib>
#include <iostream>
#include <unistd.h>  //sleep
#include <pthread.h> //pthread_xxx

using namespace std;

void *thread_func(void *p)
{
  cout<<"in pthread: "<<endl<<rand()%100<<endl;
  return NULL;
}

void fun(){
  cout<<"int fun: "<<endl<<rand()%100<<endl;
}

int main(void){
  int a = 10;
  srand(time(0));
  while(--a){
    cout<<rand()%100<<endl;
  }

  fun();

  pthread_t t1;
  pthread_create(&t1, 0, thread_func, (void *)1);

  return 0;
}
