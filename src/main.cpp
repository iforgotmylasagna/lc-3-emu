#include "lc3vm/vm.hpp"
#include <iostream>
#include <string>
//#include <SDL.h> //use this later for displaying screen and maybe input
using namespace lc3vm;

void runvm(const std::string& path){
vm test{};
int i=test.load_program(path);
if(i==0){
  std::cout << "PROGRAM LOAD SUCCESS"<<std::endl;
 }
std::cout << "RUNNING..."<<std::endl;
int j=test.run(mode::normal);
if(j<0){
  std::cout << "VM ERROR"<<std::endl;
 }
std::cout << "RUN SUCCESS" <<std::endl;
}



int main(){
runvm("bin/2048.obj");
return 0;
}
