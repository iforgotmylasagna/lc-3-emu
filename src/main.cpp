#include "lc3vm/lc3vm.hpp"
#include <iostream>
//#include <SDL.h> //use this later for displaying screen and maybe input

using namespace lc3vm;

int main(){
vm test{};
int i=test.load_program("bin/2048.obj");
if(i==0){
  std::cout << "PROGRAM LOAD SUCCESS"<<std::endl;
 }
//test.print_memory(0x3000,0x30FF);
std::cout << "RUNNING..."<<std::endl;
test.run(mode::normal);

/*
vm::memory a{};
vm::registor b{};

std::cout << a[0];
std::cout << b[reg::r0];
*/

//	std::cout << "HELLO" << std::endl;
}
