#include "lc3vm/vm.hpp"
#include <iostream>
//#include <SDL.h> //use this later for displaying screen and maybe input

using namespace lc3vm;

int main(){
vm test{};
int i=test.load_program("bin/2048.obj");
if(i==0){
  std::cout << "PROGRAM LOAD SUCCESS"<<std::endl;
 }
std::cout << "RUNNING..."<<std::endl;
int j=test.run(mode::normal);
if(j<0){
  std::cout << "VM ERROR"<<std::endl;
  return 0;
 }
std::cout << "RUN SUCCESS" <<std::endl;
return 0;
}
